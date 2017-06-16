#include "ParticleSystem.h"

ParticleSystem::ParticleSystem() {
    this->time = 0;
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
