//
// Created by Matthias Ghering on 26-5-2017.
//

#ifndef SIMULATIONS_PROJ1_MIDPOINTSOLVER_H
#define SIMULATIONS_PROJ1_MIDPOINTSOLVER_H

#include "Solver.h"

class MidPointSolver : public Solver {
public:
    MidPointSolver();
    void simulation_step(std::vector<Particle *> pVector, std::vector<Force *> fVector, std::vector<Constraint *> cVector, float dt) override;
    void simulation_step(ParticleSystem* p, float dt) override;
};


#endif //SIMULATIONS_PROJ1_MIDPOINTSOLVER_H