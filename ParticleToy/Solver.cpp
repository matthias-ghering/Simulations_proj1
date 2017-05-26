#include "Particle.h"

#include <vector>
#include "Force.h"
#include "GravityForce.h"
#include "SpringForce.h"
#include "ConstraintForce.h"

#define DAMP 0.98f
#define RAND (((rand()%2000)/1000.f)-1.f)

void simulation_step(std::vector<Particle *> pVector, float dt) {
    int ii, size = pVector.size();

    // List of all the forces.
    std::vector<Force*> fl;
    fl.push_back(new GravityForce(pVector[0]));
    fl.push_back(new GravityForce(pVector[1]));
    fl.push_back(new SpringForce(pVector[0],pVector[1], 0.4 , 0.1, 0.01));

    for (ii = 0; ii < size; ii++) {

        pVector[ii]->m_Position += dt * pVector[ii]->m_Velocity;
        Vec2f a = pVector[ii]->m_Force / pVector[ii]->m_Mass;
        pVector[ii]->m_Velocity = DAMP * pVector[ii]->m_Velocity + a*dt;

        //Reset all forces
        pVector[ii]->m_Force = Vec2f(0.0,0.0);
    }

    size = fl.size();
    for(ii=0; ii < size; ii++){
        fl[ii]->calc_Force();
    }
    //ConstraintForce* cf = new ConstraintForce();


}

