#include "Particle.h"

#include <vector>
#include "Force.h"
#include "GravityForce.h"
#include "SpringForce.h"
#include "ConstraintForce.h"

#define DAMP 0.98f
#define RAND (((rand()%2000)/1000.f)-1.f)

void simulation_step(std::vector<Particle *> pVector, std::vector<Force *> fVector, float dt) {
    int ii, fSize = fVector.size(), pSize = pVector.size();

    for(ii=0; ii < fSize; ii++){
        fVector[ii]->calc_Force();
    }

    for (ii = 0; ii < pSize; ii++) {
        pVector[ii]->m_Position += dt * pVector[ii]->m_Velocity;
        Vec2f a = pVector[ii]->m_Force / pVector[ii]->m_Mass;
        pVector[ii]->m_Velocity = DAMP * pVector[ii]->m_Velocity + a*dt;

        //Reset all the forces on particles
        pVector[ii]->m_Force = Vec2f(0.0,0.0);
    }

    printf("pos: (%f, %f)\tvel: (%f, %f)\n",
           pVector[0]->m_Position[0], pVector[0]->m_Position[1], pVector[0]->m_Velocity[0], pVector[0]->m_Velocity[1]);
    //ConstraintForce* cf = new ConstraintForce();

}

