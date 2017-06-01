//
// Created by Matthias Ghering on 23-5-2017.
//

#include "DampeningForce.h"

DampeningForce::DampeningForce(Particle *p1) : Force() {
    m_p1 = p1;
}

void DampeningForce::calc_Force() {
    m_p1->m_Force -= (m_p1->m_Velocity*DAMP)/m_p1->m_Mass;
}

void DampeningForce::draw() {

}