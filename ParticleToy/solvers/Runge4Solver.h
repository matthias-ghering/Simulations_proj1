//
// Created by Matthias Ghering on 26-5-2017.
//

#ifndef SIMULATIONS_PROJ1_RUNGE4SOLVER_H
#define SIMULATIONS_PROJ1_RUNGE4SOLVER_H

#include "Solver.h"

class Runge4Solver : public Solver {
public:
    Runge4Solver();
    void simulation_step(std::vector<Particle *> pVector, std::vector<Force *> fVector, std::vector<Constraint *> cVector, float dt) override;
    void simulation_step(ParticleSystem* p, float dt) override;
};


#endif //SIMULATIONS_PROJ1_RUNGE4SOLVER_H
