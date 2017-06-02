#include "ForwardEulerianSolver.h"

ForwardEulerianSolver::ForwardEulerianSolver():Solver(){}

void ForwardEulerianSolver::simulation_step(ParticleSystem *p, float dt) {
    std::vector<float> tmp1(this->getDim(p)), tmp2(this->getDim(p));

    this->derivEval(p, tmp1);
    this->scaleVector(tmp1, dt);
    this->getState(p, tmp2);
    this->addVectors(tmp1, tmp2, tmp2);
    this->setState(p, tmp2);
    p->time += dt;
}