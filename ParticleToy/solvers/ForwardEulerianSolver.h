#ifndef SIMULATIONS_PROJ1_FORWARDEULERIANSOLVER_H
#define SIMULATIONS_PROJ1_FORWARDEULERIANSOLVER_H

#include "Solver.h"

class ForwardEulerianSolver : public Solver {
public:
    ForwardEulerianSolver();
    void simulation_step(ParticleSystem* p, float dt) override;
};


#endif //SIMULATIONS_PROJ1_FORWARDEULERIANSOLVER_H
