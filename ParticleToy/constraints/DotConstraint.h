#pragma once

#include "../Particle.h"
#include "Constraint.h"

class DotConstraint : public Constraint{

public:
    DotConstraint(Particle *p1, const Vec2f &center);
    double getC() override ;
    double getCdot() override ;
    std::vector<Vec2f> getJ() override ;
    std::vector<Vec2f> getJdot() override ;
    void draw() override;

private:
    Vec2f const m_center;
};
