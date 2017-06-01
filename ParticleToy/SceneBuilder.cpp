//
// Created by woute on 01/06/2017.
//

#include "SceneBuilder.h"

ParticleSystem* createEmptyScene() {
    return new ParticleSystem();
}

ParticleSystem* createCircularWireScene() {
    const float dist = 0.2;
    const Vec2f center(0.0, 0.0);
    const Vec2f offset(dist, 0.0);
    ParticleSystem* particleSystem = new ParticleSystem();

    particleSystem->particles.push_back(new Particle(center + offset));
    particleSystem->particles.push_back(new Particle(center + offset + offset));
    particleSystem->particles.push_back(new Particle(center + offset + offset + offset));

    particleSystem->forces.push_back(new GravityForce(particleSystem->particles[0]));
    particleSystem->forces.push_back(new GravityForce(particleSystem->particles[1]));
    particleSystem->forces.push_back(new GravityForce(particleSystem->particles[2]));

    particleSystem->forces.push_back(new DampeningForce(particleSystem->particles[0]));
    particleSystem->forces.push_back(new DampeningForce(particleSystem->particles[1]));
    particleSystem->forces.push_back(new DampeningForce(particleSystem->particles[2]));

    particleSystem->constraints.push_back(new CircularWireConstraint(particleSystem->particles[0], center, dist));
    particleSystem->constraints.push_back(new RodConstraint(particleSystem->particles[0], particleSystem->particles[1], dist));
    particleSystem->constraints.push_back(new RodConstraint(particleSystem->particles[1], particleSystem->particles[2], dist));

    return particleSystem;
}
