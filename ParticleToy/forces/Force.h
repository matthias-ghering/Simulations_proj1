//
// Created by Matthias Ghering on 23-5-2017.
//

#ifndef SIMULATIONS_PROJ1_FORCE_H
#define SIMULATIONS_PROJ1_FORCE_H
#include <gfx/vec2.h>
#include <GL/gl.h>
#include "../Particle.h"

class Force {

public:
    virtual void calc_Force() = 0;
    virtual void draw() = 0;

};


#endif //SIMULATIONS_PROJ1_FORCE_H
