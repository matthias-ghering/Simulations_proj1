//
// Created by woute on 27/05/2017.
//

#ifndef SIMULATION_1_CONSTRAINTSOLVER_H
#define SIMULATION_1_CONSTRAINTSOLVER_H

#include <vector>
#include "../Particle.h"
#include "Constraint.h"

class ConstraintSolver {
public:
    void applyConstraints(std::vector<Particle *> particles, std::vector<Constraint *> constraints);

private:
    void init(std::vector<Particle *> particles, std::vector<Constraint *> constraints);
    void reset();

    // Particle position vector
    std::vector<Vec2f> q;

    // Particle velocity vector
    std::vector<Vec2f> qdot;

    // Particle acceleration vector
    std::vector<Vec2f> qddot;

    // Particle inverse mass vector
    std::vector<Vec2f> W;

    // Particle force vector
    std::vector<Vec2f> Q;

};

#endif //SIMULATION_1_CONSTRAINTSOLVER_H
