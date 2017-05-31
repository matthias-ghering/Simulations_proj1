//
// Created by Matthias Ghering on 26-5-2017.
//

#include "MidPointSolver.h"
#include "constraints/ConstraintSolver.h"

MidPointSolver::MidPointSolver() : Solver(){}

void MidPointSolver::simulation_step(std::vector<Particle *> pVector, std::vector<Force *> fVector, std::vector<Constraint *> cVector, float dt) {

    int fSize = fVector.size(), pSize = pVector.size();
    std::vector<Vec2f> tmppVector;                        //tmp position vector
    std::vector<Vec2f> tmpvVector;                        //tmp velocity vector

    for (int i = 0; i < pSize; i++) {
        tmpvVector.push_back(pVector[i]->m_Velocity);
        tmppVector.push_back(pVector[i]->m_Position);
    }

    for(int i = 0; i < fSize; i++){
        fVector[i]->calc_Force();
    }

    ConstraintSolver solver = ConstraintSolver();
    solver.applyConstraints(pVector, cVector, 0.97, 0.98);

    for (int i = 0; i < pSize; i++) {
        pVector[i]->m_Position += dt* 0.5 * pVector[i]->m_Velocity;             //Apply the current velocity to calculate the midpoint position.
        Vec2f ma = pVector[i]->m_Force / pVector[i]->m_Mass;                    //Calculate the acceleration at x_init.
        pVector[i]->m_Velocity = pVector[i]->m_Velocity + ma*dt*0.5; //Update the legal velocity at midpoint. TODO: we should test and re-evaluate this 0.5
                                                                                //pVector now contains the midpoints position, velocity.
        pVector[i]->m_Force = Vec2f(0.0,0.0);                                   //Reset all the forces on particles.
    }

    for(int i = 0; i < fSize; i++){
        fVector[i]->calc_Force();                                               //Calculate the new forces on the midpoints.
    }

    solver.applyConstraints(pVector, cVector, 0.97, 0.98);                      //Apply the constraints on the midpoints.

    for (int i = 0; i < pSize; i++) {
        pVector[i]->m_Position = tmppVector[i] + dt * pVector[i]->m_Velocity;   //Initial position is used in combination with the midpoint velocity.
        Vec2f a = pVector[i]->m_Force / pVector[i]->m_Mass;                     //Calculate the acceleration at midpoint.
        pVector[i]->m_Velocity = tmpvVector[i] + a * dt;                        //Calculate the velocity at the end of the step using the acceleration of the midpoint.

        //Reset all the forces on particles
        pVector[i]->m_Force = Vec2f(0.0,0.0);
    }

    printf("pos: (%f, %f)\tvel: (%f, %f)\n",
          pVector[2]->m_Position[0], pVector[2]->m_Position[1], pVector[2]->m_Velocity[0], pVector[2]->m_Velocity[1]);

}

