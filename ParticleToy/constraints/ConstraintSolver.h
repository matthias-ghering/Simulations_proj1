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
    void init(std::vector<Particle *> particles);
    void reset();

    std::vector<Vec2f> q;
    std::vector<Vec2f> qdot;
    std::vector<Vec2f> qddot;
    std::vector<Vec2f> W;
    std::vector<Vec2f> Q;
};

#endif //SIMULATION_1_CONSTRAINTSOLVER_H
