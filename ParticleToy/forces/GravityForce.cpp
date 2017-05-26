//
// Created by Matthias Ghering on 23-5-2017.
//

#include "GravityForce.h"

GravityForce::GravityForce(Particle *p1) : Force() {
    gravitationalForce = Vec2f(0, (float) (-9.807 * 0.001));
    m_p1 = p1;
}

void GravityForce::calc_Force() {
    m_p1->m_Force += m_p1->m_Mass * Vec2f(0, gravitationalForce[1]);
}

void GravityForce::draw() {
    glBegin(GL_LINES);
    glColor3f(0.6, 0.2, 0.8);
    glVertex2f(m_p1->m_Position[0], m_p1->m_Position[1]);
    glColor3f(0.6, 0.2, 0.8);
    glVertex2f(m_p1->m_Position[0], m_p1->m_Position[1] - 0.1f);
    glEnd();
}