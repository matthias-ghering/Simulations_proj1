//
// Created by Matthias Ghering on 26-5-2017.
//

#ifndef SIMULATIONS_PROJ1_EULERIANVECSOLVER_H
#define SIMULATIONS_PROJ1_EULERIANVECSOLVER_H

#include "Solver.h"

class EulerianVecSolver : public Solver {
public:
    EulerianVecSolver();
    void simulation_step(std::vector<Particle *> pVector, std::vector<Force *> fVector, std::vector<Constraint *> cVector, float dt) override;
    void initStateVectors(std::vector<Particle *> pVector);
    std::vector<Vec2f> stateVelocity;   //perhaps static ref to values?
    std::vector<Vec2f> statePosition;

};


#endif //SIMULATIONS_PROJ1_EULERIANVECSOLVER_H
