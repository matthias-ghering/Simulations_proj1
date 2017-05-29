#include "Particle.h"

#include <vector>
#include "forces/Force.h"
#include "Solver.h"
#include "constraints/ConstraintSolver.h"

//#define DAMP 0.98f
#define RAND (((rand()%2000)/1000.f)-1.f)

Solver::Solver() {}

void Solver::simulation_step(std::vector<Particle *> pVector, std::vector<Force *> fVector, std::vector<Constraint *> cVector, float dt) {}

/*====
#include "forces/Force.h"
#include "constraints/ConstraintSolver.h"

#define DAMP 0.98f
//#define RAND (((rand()%2000)/1000.f)-1.f)

void simulation_step(std::vector<Particle *> pVector, std::vector<Force *> fVector, std::vector<Constraint *> cVector, float dt) {
    int fSize = fVector.size(), pSize = pVector.size();

    for(int i = 0; i < fSize; i++){
        //Reset all the forces on particles
        pVector[i]->m_Force = Vec2f(0.0,0.0);

        fVector[i]->calc_Force();
    }

    ConstraintSolver solver = ConstraintSolver();
    solver.applyConstraints(pVector, cVector, 0.97, 0.98);

    for (int i = 0; i < pSize; i++) {
        Vec2f a = pVector[i]->m_Force / pVector[i]->m_Mass;
        pVector[i]->m_Velocity = DAMP * pVector[i]->m_Velocity + a*dt;
        pVector[i]->m_Position += dt * pVector[i]->m_Velocity;
    }

    printf("\npos0: (%f, %f)\tpos1: (%f, %f)",
           pVector[0]->m_Position[0], pVector[0]->m_Position[1], pVector[1]->m_Position[0], pVector[1]->m_Position[1]);
    printf("\tvel0: (%f, %f)\tvel1: (%f, %f)\n",
           pVector[0]->m_Velocity[0], pVector[0]->m_Velocity[1], pVector[1]->m_Velocity[0], pVector[1]->m_Velocity[1]);
    //Constraint* cf = new Constraint();

}
>>>>>>> master
*/
