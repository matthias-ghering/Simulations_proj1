#include "GravityForce.h"

GravityForce::GravityForce(Particle *p1) : Force() {
    gravitationalForce = Vec3f(0, (float) (-9.807 * 0.001),0);
    m_p1 = p1;
}

/**
 * Applies the gravitational force to the particle.
 */
void GravityForce::calc_Force() {
    m_p1->m_Force += m_p1->m_Mass * Vec3f(0, gravitationalForce[1],0);
}

void GravityForce::draw() {
    glBegin(GL_LINES);
    glColor3f(0.6, 0.2, 0.8);
    glVertex3f(m_p1->m_Position[0], m_p1->m_Position[1],m_p1->m_Position[2]);
    glColor3f(0.6, 0.2, 0.8);
    glVertex3f(m_p1->m_Position[0], m_p1->m_Position[1] - 0.1f, m_p1->m_Position[2]);
    glEnd();
}