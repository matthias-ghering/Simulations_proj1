#pragma once

#include "../Particle.h"
#include "Force.h"

class FloorForce : public Force{
public:
    FloorForce(Particle *p1, float fixed_y);
    void calc_Force() override;
    void draw() override;

private:

    Particle *const m_p1;   // particle 1
    float const m_y;
};
