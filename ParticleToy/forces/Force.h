//
// Created by Matthias Ghering on 23-5-2017.
//

#ifndef SIMULATION_1_FORCE_H
#define SIMULATION_1_FORCE_H
#include <gfx/vec2.h>
#include "../Particle.h"

class Force {

public:

    virtual void calc_Force() = 0;
    virtual void draw() = 0;

};


#endif //SIMULATION_1_FORCE_H
