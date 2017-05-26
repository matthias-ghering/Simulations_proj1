//
// Created by Matthias Ghering on 23-5-2017.
//

#ifndef SIMULATIONS_PROJ1_CONSTRAINTFORCE_H
#define SIMULATIONS_PROJ1_CONSTRAINTFORCE_H


#include "Force.h"
#include "Particle.h"

class ConstraintForce : public Force {

public:
    ConstraintForce();
    void calc_Force() override;


};


#endif //SIMULATIONS_PROJ1_CONSTRAINTFORCE_H
