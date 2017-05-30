//
// Created by Matthias Ghering on 26-5-2017.
//
#include <algorithm>
#include "forces/Force.h"
#include "EulerianVecSolver.h"
#include "constraints/ConstraintSolver.h"

/**
 * This Solver is currently replaced by the ForwardEulerianSolver that matches the formula's.
 * This Solver can later be refactored to a ImplicitEulerianSolver should that be necessary
 */
EulerianVecSolver::EulerianVecSolver():Solver(){}

void EulerianVecSolver::simulation_step(std::vector<Particle *> pVector, std::vector<Force *> fVector, std::vector<Constraint *> cVector,float dt) {
    int fSize = fVector.size(), pSize = pVector.size();
    initStateVectors(pVector);
    for(int i = 0; i < fSize; i++){
        fVector[i]->calc_Force();
    }

    ConstraintSolver solver = ConstraintSolver();
    solver.applyConstraints(pVector, cVector, 0.97, 0.98);
    Vec2f dtv = (dt,dt);
    std::transform (statePosition.begin(), statePosition.end(), stateVelocity.begin(), stateVelocity.begin(), std::plus<Vec2f>());

    for (int i = 0; i < pSize; i++) {

        Vec2f a = pVector[i]->m_Force / pVector[i]->m_Mass;
        pVector[i]->m_Velocity = DAMP * pVector[i]->m_Velocity + a*dt;
        //pVector[i]->m_Position += dt * pVector[i]->m_Velocity;

        //Reset all the forces on particles
        pVector[i]->m_Force = Vec2f(0.0,0.0);
    }

    printf("pos: (%f, %f)\tvel: (%f, %f)\n",
           pVector[0]->m_Position[0], pVector[0]->m_Position[1], pVector[0]->m_Velocity[0], pVector[0]->m_Velocity[1]);


}

void EulerianVecSolver::initStateVectors(std::vector<Particle *> pVector){
    int pSize = pVector.size();
    for(int i = 0; i < pSize; i++){
        stateVelocity.push_back(pVector[i]->m_Velocity);
        statePosition.push_back(pVector[i]->m_Position);
    }


}

