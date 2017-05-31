//
// Created by woute on 27/05/2017.
//

#ifndef SIMULATION_1_CONSTRAINTSOLVER_H
#define SIMULATION_1_CONSTRAINTSOLVER_H

#include <vector>
#include "../Particle.h"
#include "Constraint.h"
#include "../SparseMatrix.h"

class ConstraintSolver {
public:
    ConstraintSolver();
    // Apply constraint forces to given particles using given constraints, and stiffness and damping factors ks and kd
    void applyConstraints(std::vector<Particle *> particles, std::vector<Constraint *> constraints, float ks, float kd);

private:
    // Initialize vectors q, qdot, qdotdot and Q, and matrices W, C, Cdot, J, Jdot, JT
    void init(std::vector<Particle *> particles, std::vector<Constraint *> constraints);
    // Empty all vectors and matrices
    void reset();

    // Particle position vector
    std::vector<Vec2f> q;
    // Particle velocity vector
    std::vector<Vec2f> qdot;
    // Particle acceleration vector
    std::vector<Vec2f> qddot;

    // Particle inverse mass vector
    std::vector<float> W;
    // Particle force vector
    std::vector<Vec2f> Q;

    // Evaluated constraint vector
    SparseMatrix* C;
    // Evaluated constraint derivative vector
    SparseMatrix* Cdot;
    // Evaluated Jacobian matrix
    SparseMatrix* J;
    // Evaluated derivative Jacobian matrix
    SparseMatrix* Jdot;
    // Evaluated transpose Jacobian matrix
    SparseMatrix* JT;

};

#endif //SIMULATION_1_CONSTRAINTSOLVER_H
