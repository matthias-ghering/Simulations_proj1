#include "Particle.h"

#include <vector>
#include "forces/Force.h"
#include "forces/GravityForce.h"
#include "forces/SpringForce.h"
#include "constraints/ConstraintSolver.h"

#define DAMP 0.98f
#define RAND (((rand()%2000)/1000.f)-1.f)

void simulation_step(std::vector<Particle *> pVector, std::vector<Force *> fVector, std::vector<Constraint *> cVector, float dt) {
    int fSize = fVector.size(), pSize = pVector.size();

    for(int i = 0; i < fSize; i++){
        //Reset all the forces on particles
        pVector[i]->m_Force = Vec2f(0.0,0.0);

        fVector[i]->calc_Force();
    }

    ConstraintSolver solver = ConstraintSolver();
    solver.applyConstraints(pVector, cVector);

    for (int i = 0; i < pSize; i++) {
        Vec2f a = pVector[i]->m_Force / pVector[i]->m_Mass;
        pVector[i]->m_Velocity = DAMP * pVector[i]->m_Velocity + a*dt;
        pVector[i]->m_Position += dt * pVector[i]->m_Velocity;
    }

    printf("pos: (%f, %f)\tvel: (%f, %f)\n",
           pVector[1]->m_Position[0], pVector[1]->m_Position[1], pVector[1]->m_Velocity[0], pVector[1]->m_Velocity[1]);
    //Constraint* cf = new Constraint();

}

