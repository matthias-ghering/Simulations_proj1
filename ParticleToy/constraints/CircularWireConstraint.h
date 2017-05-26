#pragma once

#include <vector>
#include "../Particle.h"
#include "Constraint.h"

class CircularWireConstraint : Constraint {
public:
    CircularWireConstraint(Particle *p, const Vec2f &center, const double radius);
    float getC() override ;
    float getCdot() override ;
    std::vector<Vec2f> getJ() override ;
    std::vector<Vec2f> getJdot() override ;
    void draw();

private:
    Particle *const m_p;
    Vec2f const m_center;
    double const m_radius;
};
