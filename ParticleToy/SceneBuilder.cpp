#include "SceneBuilder.h"
#include "forces/AngularSpringForce.h"

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

    particleSystem->forces.push_back(new FloorForce(particleSystem->particles[0], -0.5));
    particleSystem->forces.push_back(new FloorForce(particleSystem->particles[1], -0.5));
    particleSystem->forces.push_back(new FloorForce(particleSystem->particles[2], -0.5));

    return particleSystem;
}

ParticleSystem* createCurtainScene(){

    int x_=5;
    int y_=9;
    const Vec2f lower_left_corner(0.0, -0.8);
    const double dist = 0.2;
    //spring variables
    const double ks_near = 10;
    const double kd_near = 1;
    const double ks_cross = 0.5;
    const double kd_cross = 0.05;

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
    particleSystem->forces.push_back(new StaticForce(particleSystem->particles[8],Vec2f(-0.05f,0)));

    return particleSystem;

}
/**
 * This scene consists of some hair and a wire constraint. This is unfortunately instable even at a low td.
 * Probably due to double spring forces.
 * @return
 */
ParticleSystem* createHairAngularSprings() {
    ParticleSystem* particleSystem = new ParticleSystem();
    int curls = 5;
    float curlYLength = 0.15;
    float curlXLength = 0.1;
    float curlRestDist = 0.25;
    float curlAngle = 70;

    for(int i = 0; i < curls; i++){
        float offset = 0.0;
        if(i%2 ==1){
            offset = curlXLength;
        }
        particleSystem->particles.push_back(new Particle(Vec2f(0.2f+offset,0.0f-curlYLength*i)));
        particleSystem->particles.push_back(new Particle(Vec2f(-0.2f-offset,0.0f-curlYLength*i)));
    }

    for(int i = 0; i < curls-2; i++){
        particleSystem->forces.push_back(new AngularSpringForce(particleSystem->particles[i*2]
                ,particleSystem->particles[i*2+2],particleSystem->particles[i*2+4],curlRestDist,curlAngle, 0.1, 0.1));
        particleSystem->forces.push_back(new AngularSpringForce(particleSystem->particles[i*2+1]
                ,particleSystem->particles[i*2+3],particleSystem->particles[i*2+5],curlRestDist,curlAngle, 0.1, 0.1));
        particleSystem->forces.push_back(new DampeningForce(particleSystem->particles[i]));
        particleSystem->forces.push_back(new DampeningForce(particleSystem->particles[i+1]));
    }
    for(int i = 0; i < curls*2; i++){
        particleSystem->forces.push_back(new GravityForce(particleSystem->particles[i]));
    }



    if(curls>2) {
        particleSystem->constraints.push_back(
                new CircularWireConstraint(particleSystem->particles[0], Vec2f(0, 0), 0.2));
        particleSystem->constraints.push_back(
                new CircularWireConstraint(particleSystem->particles[0], Vec2f(0, 0), 0.2));

        particleSystem->forces.push_back(new SpringForce(particleSystem->particles[curls*2-3]
                    ,particleSystem->particles[curls*2-1],curlRestDist,0.001,0.1));
        particleSystem->forces.push_back(new SpringForce(particleSystem->particles[curls*2-4]
                    ,particleSystem->particles[curls*2-2], curlRestDist,0.001,0.1));


    }
    return particleSystem;
}

ParticleSystem* createSimpleAngularSprings() {
    ParticleSystem* particleSystem = new ParticleSystem();
    float curlRestDist = 0.2;
    float curlAngle = 130;
    float signY =1;
    float signX =1;
    for(int i=0; i < 4; i++) {
        if (i > 0) {
            signX = -1;
        }
        if (i > 1) {
            signY = -1;
        }
        if (i > 2) {
            signX = 1;
        }
        particleSystem->particles.push_back(new Particle(Vec2f(0.5 * signX, 0.6 * signY)));
        particleSystem->particles.push_back(new Particle(Vec2f(0.5 * signX, 0.5 * signY)));
        particleSystem->particles.push_back(new Particle(Vec2f(0.6 * signX, 0.5 * signY)));
        particleSystem->forces.push_back(new DampeningForce(particleSystem->particles[i * 3]));
        particleSystem->forces.push_back(new DampeningForce(particleSystem->particles[i * 3 + 1]));
        particleSystem->forces.push_back(new DampeningForce(particleSystem->particles[i * 3 + 2]));
        particleSystem->forces.push_back(
                new AngularSpringForce(particleSystem->particles[i * 3], particleSystem->particles[i * 3 + 1],
                                       particleSystem->particles[i * 3 + 2], curlRestDist, curlAngle, 0.1, 0.0001));
    }
    Particle * p1 = new Particle(Vec2f(0.0,0.0));
    Particle * p2 = new Particle(Vec2f(0.0,0.2));
    particleSystem->particles.push_back(p1);
    particleSystem->particles.push_back(p2);

    particleSystem->forces.push_back(new SpringForce(p1,p2,0.15,0.001,0.1));
    particleSystem->forces.push_back(new SpringForce(p2,p1,0.15,0.001,0.1));




    return particleSystem;
}
