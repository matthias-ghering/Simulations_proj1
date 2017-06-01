#include "Cloth.h"
#include "../forces/SpringForce.h"
#include "../constraints/RodConstraint.h"
#include "../constraints/DotConstraint.h"
#include "../constraints/LineConstraint.h"
#include "../constraints/WallConstraint.h"
#include "../constraints/CircularWireConstraint.h"
#include "../forces/GravityForce.h"
#include "../Particle.h"

Cloth::Cloth(static ParticleSystem* particleSystem){
    //size of cloth
    int x_=2;
    int y_=2;
    const Vec2f lower_left_corner(-0.8, -0.8);
    const float dist = 0.2;
    //spring variables
    const float ks_near = 30;
    const float kd_near = 3;
    const float ks_cross = 10;
    const float kd_cross = 1;

    //cloth uses center as lower left corner
    for (int i = 0; i < x_; i++) {
        for (int j = 0; j < y_; j++) {
            //add particle
            particleSystem->particles.push_back(new Particle(lower_left_corner + Vec2f(dist*i,dist*j)));
            //add gravity
            particleSystem->forces.push_back(new GravityForce(particleSystem->particles[j+i*y_]));
        }
    }

    //add vertical structural springs
    for (int i = 0; i < x_; i++) {
        for (int j = 0; j < y_-1; j++) {
            particleSystem->forces.push_back(new SpringForce(particleSystem->particles[j+i*y_],particleSystem->forces[(j+i*y_)+1], dist , ks_near, kd_near));
        }
    }

    //add horizontal structural springs
    for (int i = 0; i < x_-1; i++) {
        for (int j = 0; j < y_; j++) {
            particleSystem->forces.push_back(new SpringForce(particleSystem->particles[j+i*y_],particleSystem->forces[(j+i*y_)+y_], dist , ks_near, kd_near));
        }
    }

    //add shear springs
    for (int i = 0; i < x_-1; i++) {
        for (int j = 0; j < y_-1; j++) {
            particleSystem->forces.push_back(new SpringForce(particleSystem->particles[j+i*y_],particleSystem->forces[(j+i*y_)+y_+1], sqrt(pow(dist,2)*2) , ks_cross, kd_cross));
            particleSystem->forces.push_back(new SpringForce(particleSystem->particles[j+i*y_+1],particleSystem->forces[(j+i*y_)+y_], sqrt(pow(dist,2)*2) , ks_cross, kd_cross));
        }
    }
}