#ifndef SIMULATION_PROJ1_SOLVER_H
#define SIMULATION_PROJ1_SOLVER_H

#include <gfx/vec2.h>
#include "../Particle.h"
#include "../forces/Force.h"
#include "../constraints/Constraint.h"
#include "vector"
#include "../ParticleSystem.h"

class Solver {

public:
    Solver();

    virtual void simulation_step(std::vector<Particle *> pVector, std::vector<Force *> fVector, std::vector<Constraint *> cVector, float dt) = 0;
    virtual void simulation_step(ParticleSystem* p, float dt) = 0;

protected:
    unsigned int getDim(ParticleSystem* p);
    void getState(ParticleSystem* p, std::vector<float>& dst);
    void setState(ParticleSystem* p, std::vector<float>& src);
    void derivEval(ParticleSystem* p, std::vector<float>& dst);
    float const DAMP = 0.98f;

    void scaleVector(std::vector<float>& a, float dt);
    void addVectors(std::vector<float>& src1, std::vector<float>& src2, std::vector<float>& dst);

private:
    void clearForces(ParticleSystem* p);
    void computeForces(ParticleSystem* p);

    ConstraintSolver* constraintSolver;
};


#endif //SIMULATION_PROJ1_SOLVER_H