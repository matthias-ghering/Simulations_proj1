#include "SceneBuilder.h"

ParticleSystem* createEmptyScene() {
    return new ParticleSystem();
}


ParticleSystem* createBoxScene() {
    ParticleSystem* particleSystem = new ParticleSystem();
    particleSystem->particles.push_back(new Particle(Vec3f(0.0,0.0,0.0)));
    particleSystem->particles.push_back(new Particle(Vec3f(0.5,0.5,0.5)));
    particleSystem->particles.push_back(new Particle(Vec3f(0.5,0.0,0.0)));
    particleSystem->particles.push_back(new Particle(Vec3f(0.0,0.5,0.0)));
    particleSystem->particles.push_back(new Particle(Vec3f(0.0,0.0,0.5)));
    particleSystem->particles.push_back(new Particle(Vec3f(0.5,0.5,0.0)));
    particleSystem->particles.push_back(new Particle(Vec3f(0.0,0.5,0.5)));
    particleSystem->particles.push_back(new Particle(Vec3f(0.5,0.0,0.5)));
    return particleSystem;
}



ParticleSystem* createSimpleClothScene(){

    int x_=5;
    int y_=9;
    const Vec3f lower_left_corner(-0.4f, -0.8f, 0.0f);
    const float dist = 0.2;
    //spring variables
    const double ks_near = 5;
    const double kd_near = 1;
    const double ks_cross = 2;
    const double kd_cross = 1;

    ParticleSystem* particleSystem = new ParticleSystem();

    //cloth uses center as lower left corner
    for (int i = 0; i < x_; i++) {
        for (int j = 0; j < y_; j++) {
            //add particle
            particleSystem->particles.push_back(new Particle(lower_left_corner + Vec3f(dist*i,dist*j,0)));
            //add gravity
            particleSystem->forces.push_back(new GravityForce(particleSystem->particles[j+i*y_]));
            //add drag
            particleSystem->forces.push_back(new DampeningForce(particleSystem->particles[j+i*y_]));
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


    return particleSystem;

}