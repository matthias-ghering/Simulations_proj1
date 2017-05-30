#include "Particle.h"

#include <vector>
#include "forces/Force.h"
#include "Solver.h"
#include "constraints/ConstraintSolver.h"

//#define DAMP 0.98f
#define RAND (((rand()%2000)/1000.f)-1.f)

Solver::Solver() {}

void Solver::simulation_step(std::vector<Particle *> pVector, std::vector<Force *> fVector, std::vector<Constraint *> cVector, float dt) {}

