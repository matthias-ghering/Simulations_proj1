#pragma once

#include "../Particle.h"
#include "Force.h"

class WallForce : public Force{
public:
    WallForce(Particle *p1, float fixed_x);
    void calc_Force() override;
    void draw() override;

private:

    Particle *const m_p1;   // particle 1
    float const m_x;
};
