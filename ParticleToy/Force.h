//
// Created by Matthias Ghering on 23-5-2017.
//

#ifndef SIMULATIONS_PROJ1_FORCE_H
#define SIMULATIONS_PROJ1_FORCE_H
#include <gfx/vec2.h>
#include "Particle.h"

class Force {

public:
    Force();

    virtual void calc_Force();
    virtual void draw();

};


#endif //SIMULATIONS_PROJ1_FORCE_H
