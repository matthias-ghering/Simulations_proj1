#include "StaticForce.h"

StaticForce::StaticForce(Particle *p1, Vec2f sForce) :
        m_p1(p1), m_s(sForce) {}

void StaticForce::draw() {
    glBegin(GL_LINES);
    glColor3f(0.0, 0.0, 0.8);
    glVertex2f(m_p1->m_Position[0], m_p1->m_Position[1]);
    glVertex2f(m_p1->m_Position[0]+ m_s[0]*2.0, m_p1->m_Position[1]+m_s[1]*2.0);
    glEnd();
}

//Static force is directional force applied to particle
void StaticForce::calc_Force() {
    m_p1->m_Force += m_p1->m_Mass * m_s;
}
