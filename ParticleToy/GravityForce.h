//
// Created by Matthias Ghering on 23-5-2017.
//

#ifndef SIMULATION_1_GRAVITYFORCE_H
#define SIMULATION_1_GRAVITYFORCE_H


#include "Force.h"
#include "Particle.h"

class GravityForce : public Force {

public:
    GravityForce(Particle *p1);
    void calc_Force() override;

private:
    Particle *m_p1;   // particle 1

};


#endif //SIMULATION_1_GRAVITYFORCE_H
