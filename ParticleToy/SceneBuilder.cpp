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

ParticleSystem* createCurtainScene(){

    int x_=5;
    int y_=9;
    const Vec2f lower_left_corner(0.0, -0.8);
    const double dist = 0.2;
    //spring variables
    const double ks_near = 30;
    const double kd_near = 3;
    const double ks_cross = 1;
    const double kd_cross = 0.1;

    ParticleSystem* particleSystem = new ParticleSystem();

    //cloth uses center as lower left corner
    for (int i = 0; i < x_; i++) {
        for (int j = 0; j < y_; j++) {
            //add particle
            particleSystem->particles.push_back(new Particle(lower_left_corner + Vec2f(dist*i,dist*j)));
            //add gravity
            particleSystem->forces.push_back(new GravityForce(particleSystem->particles[j+i*y_]));
            particleSystem->forces.push_back(new WallForce(particleSystem->particles[j+i*y_], -0.5));
        }
    }

    //add vertical structural springs
    for (int i = 0; i < x_; i++) {
        for (int j = 0; j < y_-1; j++) {
            particleSystem->forces.push_back(new SpringForce(particleSystem->particles[j+i*y_],particleSystem->particles[(j+i*y_)+1], dist , ks_near, kd_near));
        }
    }

    //add horizontal structural springs
    for (int i = 0; i < x_-1; i++) {
        for (int j = 0; j < y_; j++) {
            particleSystem->forces.push_back(new SpringForce(particleSystem->particles[j+i*y_],particleSystem->particles[(j+i*y_)+y_], dist , ks_near, kd_near));
        }
    }

    //add shear springs
    for (int i = 0; i < x_-1; i++) {
        for (int j = 0; j < y_-1; j++) {
            particleSystem->forces.push_back(new SpringForce(particleSystem->particles[j+i*y_],particleSystem->particles[(j+i*y_)+y_+1], sqrt(pow(dist,2)*2) , ks_cross, kd_cross));
            particleSystem->forces.push_back(new SpringForce(particleSystem->particles[j+i*y_+1],particleSystem->particles[(j+i*y_)+y_], sqrt(pow(dist,2)*2) , ks_cross, kd_cross));
        }
    }

    particleSystem->constraints.push_back(new LineConstraint(particleSystem->particles[8], 0.8));
    particleSystem->constraints.push_back(new LineConstraint(particleSystem->particles[5*9-1], 0.8));
    particleSystem->forces.push_back(new StaticForce(particleSystem->particles[8],Vec2f(-0.2,0)));

    return particleSystem;

}
