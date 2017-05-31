//
// Created by woute on 31/05/2017.
//

#ifndef SIMULATION_1_PARTICLESYSTEM_H
#define SIMULATION_1_PARTICLESYSTEM_H


#include <vector>
#include "Particle.h"
#include "forces/Force.h"
#include "constraints/ConstraintSolver.h"

class ParticleSystem {

public:
    ParticleSystem();

    std::vector<Particle*> particles;
    std::vector<Force*> forces;
    std::vector<Constraint*> constraints;
    float time;

    void drawParticles();
    void drawForces();
    void drawConstraints();
};


#endif //SIMULATION_1_PARTICLESYSTEM_H
