//
// Created by Matthias Ghering on 26-5-2017.
//

#include "MidPointSolver.h"
#include "constraints/ConstraintSolver.h"

MidPointSolver::MidPointSolver() : Solver(){}

void MidPointSolver::simulation_step(std::vector<Particle *> pVector, std::vector<Force *> fVector, std::vector<Constraint *> cVector, float dt) {
    //Eulerian step
    //EulerianSolver* eulerianSolver = new EulerianSolver();
    //eulerianSolver->simulation_step(std::vector<Particle *> pVector, std::vector<Force *> fVector, float dt)

    int fSize = fVector.size(), pSize = pVector.size();
    std::vector<Vec2f> tmppVector;                        //tmp position vector
    std::vector<Vec2f> tmpvVector;                        //tmp velocity vector
    //static std::vector<Force *> mfVector = fVector;

    for (int i = 0; i < pSize; i++) {                     //
        tmpvVector.push_back(pVector[i]->m_Velocity);
        tmppVector.push_back(pVector[i]->m_Position);
        //mpVector.push_back(pVector[i]->copy()); //TODO: need to make sure this does not cause memory leaks!
    }

    for(int i = 0; i < fSize; i++){
        pVector[i]->m_Force = Vec2f(0.0,0.0);
        fVector[i]->calc_Force();
    }

    ConstraintSolver solver = ConstraintSolver();
    solver.applyConstraints(pVector, cVector, 0.97, 0.98);

    for (int i = 0; i < pSize; i++) {
        pVector[i]->m_Position += dt* 0.5 * pVector[i]->m_Velocity;             //Apply the current legal velocity to calculate the midpoint position.
        Vec2f ma = pVector[i]->m_Force / pVector[i]->m_Mass;                    //Update the legal acceleration at midpoint.
        pVector[i]->m_Velocity = DAMP * pVector[i]->m_Velocity + ma*dt*0.5;     //Update the legal velocity at midpoint.
                                                                                //pVector now contains the midpoints position, velocity, acceleration and force.
        pVector[i]->m_Force = Vec2f(0.0,0.0);                                   //Reset all the forces on particles.
    }

    for(int i = 0; i < fSize; i++){
        fVector[i]->calc_Force();                                               //Calculate the new forces on the midpoints.
    }

    solver.applyConstraints(pVector, cVector, 0.97, 0.98);                      //Apply the constraints on the midpoints.

    for (int i = 0; i < pSize; i++) {
        pVector[i]->m_Position = tmppVector[i] + dt * pVector[i]->m_Velocity;   //Initial position is used in combination with the midpoint velocity
        Vec2f a = pVector[i]->m_Force / pVector[i]->m_Mass;                     //Calculate the acceleration at starting point? This should be the same as before?
        pVector[i]->m_Velocity = DAMP * pVector[i]->m_Velocity + a *dt;         //Calculate the velocity at the end of the step using the forces at initial position?

        //Reset all the forces on particles
        pVector[i]->m_Force = Vec2f(0.0,0.0);
    }
    /*(pVector[0]->m_Velocity[0] == mpVector[0]->m_Velocity[0]){
        printf("vel: (%f, %f)", pVector[0]->m_Velocity[0], mpVector[0]->m_Velocity[0]);
    }*/
    printf("pos: (%f, %f)\tvel: (%f, %f)\n",
          pVector[0]->m_Position[0], pVector[1]->m_Position[0], pVector[0]->m_Velocity[0], pVector[0]->m_Velocity[1]);
    //ConstraintForce* cf = new ConstraintForce();

    //clear all?
    /*for (int i = 0; i < pSize; i++) {
        delete mpVector[i]; //TODO: need to make sure this does stops memory leaks!
    }*/
}

