#include "MidPointSolver.h"

MidPointSolver::MidPointSolver() : Solver(){}

void MidPointSolver::simulation_step(ParticleSystem* p, float dt) {
    std::vector<float> tmp1(this->getDim(p)), tmp2(this->getDim(p)), tmp3(this->getDim(p));

    this->getState(p, tmp2); //Save starting point to tmp2

    this->derivEval(p, tmp1); //Calculate Forces and save force and velocity to tmp1

    this->scaleVector(tmp1, dt*0.5f); //Take 0.5dt step to midpoint

    this->addVectors(tmp1, tmp2, tmp2); //add starting point to mid-point, save midpoint to tmp2

    this->getState(p, tmp3); //Save starting point to tmp3

    this->setState(p, tmp2); //Save midpoint to particle

    this->derivEval(p, tmp1); //Calculate Forces at midpoint and save force and velocity to tmp1

    this->scaleVector(tmp1, dt); //Take dt step from midpoint

    this->addVectors(tmp1, tmp3, tmp3); //add starting point to full midpoint method step step

    this->setState(p, tmp3); //Save step to particle

    p->time += dt;
}


