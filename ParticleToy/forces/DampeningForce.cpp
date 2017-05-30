//
// Created by Matthias Ghering on 23-5-2017.
//

#include "DampeningForce.h"

DampeningForce::DampeningForce(Particle *p1) : Force() {
    m_p1 = p1;
}

void DampeningForce::calc_Force() {
    m_p1->m_Force -= m_p1->m_Velocity*(1-DAMP)/m_p1->m_Mass/0.02;
}

void DampeningForce::draw() {
    glBegin(GL_LINES);
    glColor3f(0.6, 0.2, 0.8);
    glVertex2f(m_p1->m_Position[0], m_p1->m_Position[1]);
    glColor3f(0.6, 0.2, 0.8);
    glVertex2f(m_p1->m_Position[0], m_p1->m_Position[1] - 0.1f);
    glEnd();
}