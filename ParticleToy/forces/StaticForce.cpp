#include "StaticForce.h"

StaticForce::StaticForce(Particle *p1, Vec2f sForce) :
        m_p1(p1), m_s(sForce) {}

void StaticForce::draw() {
    /*glBegin(GL_LINES);
    glColor3f(0.6, 0.7, 0.8);
    glVertex2f(m_p1->m_Position[0], m_p1->m_Position[1]);
    glColor3f(0.6, 0.7, 0.8);
    glVertex2f(m_p2->m_Position[0], m_p2->m_Position[1]);
    glEnd();*/
}

void StaticForce::calc_Force() {
    m_p1->m_Force += m_p1->m_Mass * m_s;
}
