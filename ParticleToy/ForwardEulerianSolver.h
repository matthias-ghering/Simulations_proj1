//
// Created by Matthias Ghering on 26-5-2017.
//

#ifndef SIMULATIONS_PROJ1_FORWARDEULERIANSOLVER_H
#define SIMULATIONS_PROJ1_FORWARDEULERIANSOLVER_H

#include "Solver.h"

class ForwardEulerianSolver : public Solver {
public:
    ForwardEulerianSolver();
    void simulation_step(std::vector<Particle *> pVector, std::vector<Force *> fVector, std::vector<Constraint *> cVector, float dt) override;
    void simulation_step(ParticleSystem* p, float dt) override;
};


#endif //SIMULATIONS_PROJ1_FORWARDEULERIANSOLVER_H
