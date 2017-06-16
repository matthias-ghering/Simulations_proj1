#ifndef SIMULATION_1_PARTICLESYSTEM_H
#define SIMULATION_1_PARTICLESYSTEM_H

#include <vector>
#include "Particle.h"
#include "forces/Force.h"


class ParticleSystem {

public:
    ParticleSystem();

    std::vector<Particle*> particles;
    std::vector<Force*> forces;

    float time;

    void drawParticles();
    void drawForces();

};


#endif //SIMULATION_1_PARTICLESYSTEM_H
