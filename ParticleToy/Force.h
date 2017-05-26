//
// Created by Matthias Ghering on 23-5-2017.
//

#ifndef SIMULATION_1_FORCE_H
#define SIMULATION_1_FORCE_H
#include <gfx/vec2.h>
#include "Particle.h"

class Force {

public:
    Force();

    virtual void calc_Force();
    virtual void draw();

};


#endif //SIMULATION_1_FORCE_H
