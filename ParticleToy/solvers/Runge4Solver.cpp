#include "Runge4Solver.h"

Runge4Solver::Runge4Solver():Solver(){}

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