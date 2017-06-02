#pragma once

#include "../Particle.h"
#include "Force.h"

class AngularSpringForce : public Force{
public:
    AngularSpringForce(Particle *p1, Particle *p2, Particle *p3, double dist, double rstAngle, double ks, double kd);
    void calc_Force() override;
    void draw() override;

private:

    Particle *const m_p1;   // particle 1
    Particle *const m_p2;   // particle 2
    Particle *const m_p3;   // particle 2
    double const m_dist;    // rest length
    float originOrient;
    double m_rstAngle;
    double const m_ks, m_kd; // spring strength constants
};
