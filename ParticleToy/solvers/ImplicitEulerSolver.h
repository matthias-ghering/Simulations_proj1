//
// Created by woute on 01/06/2017.
//

#ifndef SIMULATION_1_IMPLICITEULERSOLVER_H
#define SIMULATION_1_IMPLICITEULERSOLVER_H

#include "../ParticleSystem.h"
#include "Solver.h"

class ImplicitEulerSolver : public Solver {
public:
    ImplicitEulerSolver();

    virtual void simulation_step(std::vector<Particle *> pVector, std::vector<Force *> fVector, std::vector<Constraint *> cVector, float dt) override;
    virtual void simulation_step(ParticleSystem* p, float dt) override;
};


#endif //SIMULATION_1_IMPLICITEULERSOLVER_H
