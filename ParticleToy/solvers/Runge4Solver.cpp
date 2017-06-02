#include "Runge4Solver.h"

Runge4Solver::Runge4Solver():Solver(){}

void Runge4Solver::simulation_step2(ParticleSystem* p, float dt) {
    std::vector<Particle* > pVector = p->particles;
    std::vector<Force* > fVector = p->forces;
    std::vector<Constraint* > cVector = p->constraints;

    int fSize = fVector.size(), pSize = pVector.size();
    std::vector<Vec2f> k1, k2, k3, k4;                                      //For every particle there is a k1 to k4.
    std::vector<Vec2f> initpVector;                                         //tmp position vector

    for (int i = 0; i < pSize; i++) {
        initpVector.push_back(pVector[i]->m_Position);
    }

    for(int i = 0; i < fSize; i++){                                         //Accumulate forces.
        fVector[i]->calc_Force();
    }

    ConstraintSolver solver = ConstraintSolver();                           //Apply constraints.
    solver.applyConstraints(pVector, cVector, 0.97, 0.98);

    for (int i = 0; i < pSize; i++) {
        k1.push_back(pVector[i]->m_Velocity * dt);                                //Assign position change of k1.
        pVector[i]->m_Position = initpVector[i] + dt * pVector[i]->m_Velocity * 0.5;        //Update the position with half a step. (to k1 midpoint)
        Vec2f a = pVector[i]->m_Force / pVector[i]->m_Mass;                 //Update the legal acceleration using the corrected force. (At position x_n.)
        pVector[i]->m_Velocity = pVector[i]->m_Velocity + a*dt*0.5;         //0.5? Update the legal velocity with half a step. (velocity at k1 midpoint) (which is used for k2))
        pVector[i]->m_Force = Vec2f(0.0,0.0);                               //Reset all the forces on particles.
    }

    //repeat this step
    for(int i = 0; i < fSize; i++){
        fVector[i]->calc_Force();
    }

    solver.applyConstraints(pVector, cVector, 0.97, 0.98);

    for (int i = 0; i < pSize; i++) {
        k2.push_back(pVector[i]->m_Velocity * dt);                                        //Assign position change of k2 using the previously calculated velocity.
        pVector[i]->m_Position = initpVector[i] + dt * pVector[i]->m_Velocity * 0.5; //Update the position with half a step. (to k2 midpoint)
        Vec2f a = pVector[i]->m_Force / pVector[i]->m_Mass;                         //Calculate the acceleration at k1_midpoint
        pVector[i]->m_Velocity = pVector[i]->m_Velocity + a*dt*0.5;                 //0.5? Update the legal velocity with half a step. (velocity at k2 midpoint).
        pVector[i]->m_Force = Vec2f(0.0,0.0);                                       //Reset all the forces on particles
    }

//repeat this step
    for(int i = 0; i < fSize; i++){
        fVector[i]->calc_Force();
    }

    solver.applyConstraints(pVector, cVector, 0.97, 0.98);

    for (int i = 0; i < pSize; i++) {
        k3.push_back(pVector[i]->m_Velocity * dt);                                        //Assign position change of k3 using the previously calculated velocity.
        pVector[i]->m_Position = initpVector[i] + dt * pVector[i]->m_Velocity;      //Update the position with a full step. (to k3)
        Vec2f a = pVector[i]->m_Force / pVector[i]->m_Mass;                         //Calculate the acceleration at k2_midpoint.
        pVector[i]->m_Velocity = pVector[i]->m_Velocity + a*dt;                     //0.5? Update the legal velocity with a full step. (velocity at k3 midpoint).
        pVector[i]->m_Force = Vec2f(0.0,0.0);                                       //Reset all the forces on particles
    }

    //calc forces for acceleration needed for the velocity at the end of the step?

    for (int i = 0; i < pSize; i++) {
        k4.push_back(pVector[i]->m_Velocity * dt);                                                //Assign position change of k4 using the previously calculated velocity.
        pVector[i]->m_Position = initpVector[i] + k1[i]/6 + k2[i]/3 + k3[i]/3 + k4[i]/6;    //Calculate the new position using k1,k2,k3 and k4.
    }

}

void Runge4Solver::simulation_step(ParticleSystem* p, float dt) {
    std::vector<Particle* > pVector = p->particles;
    std::vector<Force* > fVector = p->forces;
    std::vector<Constraint* > cVector = p->constraints;

    unsigned dim = (this->getDim(p));
    std::vector<float> initpVector(dim), tmpfVector(dim),k1(dim), k2(dim), k3(dim), k4(dim), test(dim), midPt(dim);

    this->getState(p, initpVector);                 //Save starting point and velocities.

    this->derivEval(p, tmpfVector);                 //Calculate Forces and constraints and save force and velocity to tmp1.
    this->scaleVector(tmpfVector, dt*0.5f);         //Take 0.5dt step to midpoint of k1.
    this->addVectors(initpVector,tmpfVector ,midPt);//Save midpoint k1 to k1.
    this->setState(p, midPt);                       //Move ParticleSystem to mid point k1.
    this->scaleVector(tmpfVector, 2.0f, k1);        //Make complete step of k1 and save for later use.


    this->derivEval(p,tmpfVector);                  //Calculate Forces and constraints and save force and velocity at mid point.
    this->scaleVector(tmpfVector, dt*0.5f);         //Take 0.5dt step to midpoint of k2.
    this->addVectors(initpVector,tmpfVector ,midPt);//Save midpoint k2 to k2.
    this->setState(p, midPt);                       //Move ParticleSystem to mid point k2.
    this->scaleVector(tmpfVector, 2.0f, k2);        //Make complete step of k2 and save for later use.

    this->derivEval(p,k3);
    this->scaleVector(k3, dt);                      //Complete step to k3
    this->addVectors(initpVector,tmpfVector, midPt);
    this->setState(p, midPt);

    this->derivEval(p,k4);
    this->scaleVector(k4, dt);

    //Total computation:
    this->scaleVector(k1,1.0f/6.0f);
    this->scaleVector(k2,1.0f/3.0f);
    this->scaleVector(k3,1.0f/3.0f);
    this->scaleVector(k4,1.0f/6.0f);
    this->addVectors(initpVector,k1,initpVector);
    this->addVectors(initpVector,k2,initpVector);
    this->addVectors(initpVector,k3,initpVector);
    this->addVectors(initpVector,k4,initpVector);

    this->setState(p,initpVector);

}