//
// Created by Matthias Ghering on 26-5-2017.
//
#include "forces/Force.h"
#include "ForwardEulerianSolver.h"
#include "constraints/ConstraintSolver.h"

ForwardEulerianSolver::ForwardEulerianSolver():Solver(){}

void ForwardEulerianSolver::simulation_step(std::vector<Particle *> pVector, std::vector<Force *> fVector, std::vector<Constraint *> cVector,float dt) {
    int fSize = fVector.size(), pSize = pVector.size();

    for(int i = 0; i < fSize; i++){
        fVector[i]->calc_Force();
    }

    ConstraintSolver solver = ConstraintSolver();
    solver.applyConstraints(pVector, cVector, 0.97, 0.98);

    for (int i = 0; i < pSize; i++) {
        pVector[i]->m_Position += dt * pVector[i]->m_Velocity;              //apply current legal velocity to create a new position
        Vec2f a = pVector[i]->m_Force / pVector[i]->m_Mass;                 //update the legal acceleration using the corrected force
        pVector[i]->m_Velocity = /*DAMP */ pVector[i]->m_Velocity + a*dt;      //update the legal velocity using the updated legal acceleration

        //Reset all the forces on particles
        pVector[i]->m_Force = Vec2f(0.0,0.0);
    }

    //This print statement slows down execution
    //printf("pos: (%f, %f)\tvel: (%f, %f)\n",
    //       pVector[0]->m_Position[0], pVector[0]->m_Position[1], pVector[0]->m_Velocity[0], pVector[0]->m_Velocity[1]);

}

void ForwardEulerianSolver::simulation_step(ParticleSystem *p, float dt) {
    std::vector<float> tmp1(this->getDim(p)), tmp2(this->getDim(p));
    this->derivEval(p, tmp1);
    this->scaleVector(tmp1, dt);
    this->getState(p, tmp2);
    this->addVectors(tmp1, tmp2, tmp2);
    this->setState(p, tmp2);
    p->time += dt;
}