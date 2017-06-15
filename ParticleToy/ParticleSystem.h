#ifndef SIMULATION_1_PARTICLESYSTEM_H
#define SIMULATION_1_PARTICLESYSTEM_H

#include <vector>
#include "Particle.h"
#include "forces/Force.h"
#include "constraints/ConstraintSolver.h"
#include "Eigen/Dense"

using namespace Eigen;

class ParticleSystem {

public:
    ParticleSystem();

    Vector3f v;//test


    std::vector<Particle*> particles;
    std::vector<Force*> forces;
    std::vector<Constraint*> constraints;

    float time;

    void drawParticles();
    void drawForces();
    void drawConstraints();
};


#endif //SIMULATION_1_PARTICLESYSTEM_H
