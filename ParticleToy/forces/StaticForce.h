#pragma once

#include "../Particle.h"
#include "Force.h"

class HorizontalForce : public Force{ //
public:
    HorizontalForce(Particle *p1, double hForce);
    void calc_Force() override;
    void draw() override;

private:

    Particle *const m_p1;   // particle 1
    Vec2f force;
};
