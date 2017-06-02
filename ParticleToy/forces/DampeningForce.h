//
// Created by Matthias Ghering on 23-5-2017.
//

#ifndef SIMULATIONS_PROJ1_DAMPENINGFORCE_H
#define SIMULATIONS_PROJ1_DAMPENINGFORCE_H

#include "Force.h"
#include "../Particle.h"

class DampeningForce : public Force {

public:
    DampeningForce(Particle *p1);
    void calc_Force() override;
    void draw() override;

private:
    Particle *m_p1;   // particle 1
    float DAMP = 0.99;
};


#endif //SIMULATIONS_PROJ1_DAMPENINGFORCE_H
