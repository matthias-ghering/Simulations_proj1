#include "ParticleSystem.h"

ParticleSystem::ParticleSystem() {
    this->time = 0;
    Eigen::Vector3f b(1.0f,1.0f,1.0f);
}

void ParticleSystem::drawParticles() {
    int size = this->particles.size();

    for (int i = 0; i < size; i++) {
        this->particles[i]->draw();
    }
}

void ParticleSystem::drawForces() {
    int size = this->forces.size();

    for (int i = 0; i < size; i++) {
        this->forces[i]->draw();
    }
}

void ParticleSystem::drawConstraints() {
    int size = this->constraints.size();

    for (int i = 0; i < size; i++) {
        this->constraints[i]->draw();
    }
}
