#pragma once

#include "../Particle.h"
#include "Constraint.h"

class LineConstraint : public Constraint{

public:
    LineConstraint(Particle *p1, float fixed_y);
    double getC() override ;
    double getCdot() override ;
    std::vector<Vec2f> getJ() override ;
    std::vector<Vec2f> getJdot() override ;
    void draw() override;

private:
    float const m_y;
};
