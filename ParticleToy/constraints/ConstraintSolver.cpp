
#include "ConstraintSolver.h"

void ConstraintSolver::init(std::vector<Particle *> particles, std::vector<Constraint *> constraints) {
    for (int i = 0; i < particles.size(); i++) {

        // Set position vector
        this->q.push_back(particles[i]->m_Position);

        // Set velocity vector
        this->qdot.push_back(particles[i]->m_Velocity);

        // Set inverse weight vector
        float wweight = 1 / particles[i]->m_Mass;
        this->W.push_back(Vec2f(wweight, wweight));

        // Set force vector
        this->Q.push_back(particles[i]->m_Force);

        // Calculate pre-constraint velocity qdotdot
        this->qddot.push_back(
                Vec2f(this->W[i][0] * this->Q[i][0], this->W[i][1] * this->Q[i][1])
        );
    }
}

void ConstraintSolver::reset() {
    this->q.clear();
    this->qdot.clear();
    this->W.clear();
    this->Q.clear();
    this->qddot.clear();
}

void ConstraintSolver::applyConstraints(std::vector<Particle *> particles, std::vector<Constraint *> constraints) {
    this->init(particles, constraints);

    // Apply constraints


    this->reset();
}

