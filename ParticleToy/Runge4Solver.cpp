//
// Created by Matthias Ghering on 26-5-2017.
//
#include "forces/Force.h"
#include "Runge4Solver.h"
#include "constraints/ConstraintSolver.h"

Runge4Solver::Runge4Solver():Solver(){}

void Runge4Solver::simulation_step(std::vector<Particle *> pVector, std::vector<Force *> fVector, std::vector<Constraint *> cVector,float dt) {
    int fSize = fVector.size(), pSize = pVector.size();
    std::vector<Vec2f> k1, k2, k3, k4;                                       //For every particle there is a k1 to k4.
    std::vector<Vec2f> tmppVector;                        //tmp position vector
    std::vector<Vec2f> tmpvVector;                        //tmp velocity vector TODO: do I need this?

    for (int i = 0; i < pSize; i++) {
        tmpvVector.push_back(pVector[i]->m_Velocity);
        tmppVector.push_back(pVector[i]->m_Position);
    }

    for(int i = 0; i < fSize; i++){                                         //Accumulate forces.
        fVector[i]->calc_Force();
    }

    ConstraintSolver solver = ConstraintSolver();                           //Apply constraints.
    solver.applyConstraints(pVector, cVector, 0.97, 0.98);

    for (int i = 0; i < pSize; i++) {
        k1[i] = pVector[i]->m_Velocity * dt;                                //Assign position change of k1.
        pVector[i]->m_Position += dt * pVector[i]->m_Velocity * 0.5;        //Update the position with half a step. (to calculate the velocity used in k3)
        Vec2f a = pVector[i]->m_Force / pVector[i]->m_Mass;                 //Update the legal acceleration using the corrected force. (At position x_n.)
        pVector[i]->m_Velocity = pVector[i]->m_Velocity + a*dt*0.5;         //Update the legal velocity with half a step. (for the velocity at position x_n + x_k1*0.5 (which is used for k2))
        pVector[i]->m_Force = Vec2f(0.0,0.0);                               //Reset all the forces on particles.
    }

    //repeat this step
    for(int i = 0; i < fSize; i++){
        fVector[i]->calc_Force();
    }

    solver.applyConstraints(pVector, cVector, 0.97, 0.98);

    for (int i = 0; i < pSize; i++) {
        k2[i] = pVector[i]->m_Velocity * dt;                                        //Assign position change of k2 using the previously calculated velocity.
        pVector[i]->m_Position = tmppVector[i] + dt * pVector[i]->m_Velocity * 0.5; //Update the position with half a step. (for k3)
        Vec2f a = pVector[i]->m_Force / pVector[i]->m_Mass;                         //Calculate the acceleration at
        pVector[i]->m_Velocity = pVector[i]->m_Velocity + a*dt*0.5;                 //Update the legal velocity using the updated legal acceleration.
        pVector[i]->m_Force = Vec2f(0.0,0.0);                                       //Reset all the forces on particles
    }




    //This print statement slows down execution
    printf("pos: (%f, %f)\tvel: (%f, %f)\n",
           pVector[0]->m_Position[0], pVector[0]->m_Position[1], pVector[0]->m_Velocity[0], pVector[0]->m_Velocity[1]);

}