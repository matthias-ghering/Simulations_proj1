#pragma once

#include "../Particle.h"
#include "Constraint.h"

class WallConstraint : public Constraint{

public:
    WallConstraint(Particle *p1, double fixed_x);
    double getC() override ;
    double getCdot() override ;
    std::vector<Vec2f> getJ() override ;
    std::vector<Vec2f> getJdot() override ;
    void draw() override;

private:
    double const m_x;
};
