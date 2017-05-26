//
// Created by Matthias Ghering on 26-5-2017.
//

#ifndef SIMULATIONS_PROJ1_EULERIANSOLVER_H
#define SIMULATIONS_PROJ1_EULERIANSOLVER_H

#include "Solver.h"

class EulerianSolver : public Solver {
public:
    EulerianSolver();
    void simulation_step(std::vector<Particle *> pVector, std::vector<Force *> fVector, float dt) override;
};


#endif //SIMULATIONS_PROJ1_EULERIANSOLVER_H
