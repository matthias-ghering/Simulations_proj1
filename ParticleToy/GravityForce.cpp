//
// Created by Matthias Ghering on 23-5-2017.
//

#include "GravityForce.h"

GravityForce::GravityForce(Particle *p1) : Force() {
    m_p1 = p1;
}

void GravityForce::calc_Force() {
    m_p1->m_Force += m_p1->m_Mass * Vec2f(0, (float) -0.0009807);
}
