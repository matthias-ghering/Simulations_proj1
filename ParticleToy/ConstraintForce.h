//
// Created by Matthias Ghering on 23-5-2017.
//

#ifndef SIMULATION_1_CONSTRAINTFORCE_H
#define SIMULATION_1_CONSTRAINTFORCE_H


#include "Force.h"
#include "Particle.h"

class ConstraintForce : public Force {

public:
    ConstraintForce();

    virtual getC();
    virtual getCdot();
    virtual getJ();
    virtual getJdot();


};


#endif //SIMULATION_1_CONSTRAINTFORCE_H
