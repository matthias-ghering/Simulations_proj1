//
// Created by Matthias Ghering on 26-5-2017.
//

#include "MidPointSolver.h"
#include "EulerianSolver.h"

MidPointSolver::MidPointSolver() : Solver(){}

void MidPointSolver::simulation_step(std::vector<Particle *> pVector, std::vector<Force *> fVector, float dt) {
    //Eulerian step
    //EulerianSolver* eulerianSolver = new EulerianSolver();
    //eulerianSolver->simulation_step(std::vector<Particle *> pVector, std::vector<Force *> fVector, float dt)

    int fSize = fVector.size(), pSize = pVector.size();

    for(int i = 0; i < fSize; i++){
        fVector[i]->calc_Force();
    }

    for (int i = 0; i < pSize; i++) {
        pVector[i]->m_Position += dt * pVector[i]->m_Velocity;
        Vec2f a = pVector[i]->m_Force / pVector[i]->m_Mass;
        pVector[i]->m_Velocity = DAMP * pVector[i]->m_Velocity + a*dt;

        //Reset all the forces on particles
        pVector[i]->m_Force = Vec2f(0.0,0.0);
    }

    printf("pos: (%f, %f)\tvel: (%f, %f)\n",
           pVector[0]->m_Position[0], pVector[0]->m_Position[1], pVector[0]->m_Velocity[0], pVector[0]->m_Velocity[1]);
    //ConstraintForce* cf = new ConstraintForce();

}