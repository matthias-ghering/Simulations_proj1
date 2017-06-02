#include "../Particle.h"
#include "Solver.h"

Solver::Solver() {
    this->constraintSolver = new ConstraintSolver();
}

unsigned int Solver::getDim(ParticleSystem* p) {
    return p->particles.size() * 4;
}
/**
 * Returns the current state of the system (positions and velocities).
 * @param p the given ParticleSystem.
 * @param dst a vector of positions and velocities.
 */
void Solver::getState(ParticleSystem* p, std::vector<float>& dst) {
    for (int i = 0; i < p->particles.size(); i++) {
        dst[4 * i + 0] = p->particles[i]->m_Position[0];
        dst[4 * i + 1] = p->particles[i]->m_Position[1];
        dst[4 * i + 2] = p->particles[i]->m_Velocity[0];
        dst[4 * i + 3] = p->particles[i]->m_Velocity[1];
    }
}

void Solver::setState(ParticleSystem* p, std::vector<float>& src) {
    for (int i = 0; i < p->particles.size(); i++) {
        p->particles[i]->m_Position[0] = src[4 * i + 0];
        p->particles[i]->m_Position[1] = src[4 * i + 1];
        p->particles[i]->m_Velocity[0] = src[4 * i + 2];
        p->particles[i]->m_Velocity[1] = src[4 * i + 3];
    }
}
/**
 * derivEval uses the forces and the constraints to compute the accelloration which is returned together with the velocity.
 * @param p the given ParticleSystem.
 * @param dst a vector of velocities and accelerations.
 */
void Solver::derivEval(ParticleSystem* p, std::vector<float>& dst) {
    this->clearForces(p);
    this->computeForces(p);

    for (int i = 0; i < p->particles.size(); i++) {
        dst[4 * i + 0] = p->particles[i]->m_Velocity[0];
        dst[4 * i + 1] = p->particles[i]->m_Velocity[1];

        float mass = p->particles[i]->m_Mass;

        dst[4 * i + 2] = p->particles[i]->m_Force[0]/mass;
        dst[4 * i + 3] = p->particles[i]->m_Force[1]/mass;
    }
}

void Solver::clearForces(ParticleSystem* p) {
    for (int i = 0; i < p->particles.size(); i++) {
        p->particles[i]->m_Force = Vec2f(0.0f, 0.0f);
    }
}

void Solver::computeForces(ParticleSystem* p) {
    for (int i = 0; i < p->forces.size(); i++) {
        p->forces[i]->calc_Force();
    }

    this->constraintSolver->applyConstraints(p->particles, p->constraints, 0.97f, 0.98f);
}

void Solver::scaleVector(std::vector<float>& a, float dt) {
    for (int i = 0; i < a.size(); i++) {
        a[i] *= dt;
    }
}

void Solver::scaleVector(std::vector<float>& a, float dt, std::vector<float>& dst) {
    for (int i = 0; i < a.size(); i++) {
        dst[i] = a[i] * dt;
    }
}
/**
 * addVectors adds two vectors.
 * @param src1
 * @param src2
 * @param dst this vector is the result of the addition.
 */
void Solver::addVectors(std::vector<float>& src1, std::vector<float>& src2, std::vector<float>& dst) {
    for (int i = 0; i < src1.size(); i++) {
        dst[i] = src1[i] + src2[i];
    }
}
