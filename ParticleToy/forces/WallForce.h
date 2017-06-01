#pragma once

#include "../Particle.h"
#include "Force.h"

class WallForce : public Force{
public:
    WallForce(Particle *p1, double fixed_x);
    void calc_Force() override;
    void draw() override;

private:

    Particle *const m_p1;   // particle 1
    double const m_x;
};
