#ifndef SIMULATION_PROJ1_SOLVER_H
#define SIMULATION_PROJ1_SOLVER_H
#include <gfx/vec2.h>
#include "Particle.h"
#include "Force.h"
#include "vector"

class Solver {

public:
    Solver();
    virtual void simulation_step(std::vector<Particle *> pVector, std::vector<Force *> fVector, float dt);

protected:
    float const DAMP = 0.98f;
};


#endif //SIMULATION_PROJ1_SOLVER_H