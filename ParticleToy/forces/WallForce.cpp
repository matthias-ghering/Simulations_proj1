#include "WallForce.h"

WallForce::WallForce(Particle *p1, double fixed_x) :
        m_p1(p1), m_x(fixed_x) {}

void WallForce::draw() {
    glBegin(GL_LINES);
    glColor3f(0.8, 0.0, 0.0);
    glVertex2f(this->m_x, -10);
    glVertex2f(this->m_x, 10);
    glEnd();
}

void WallForce::calc_Force() {
    if (m_p1->m_Position[0] < m_x){
        m_p1->m_Force[0] *= -1;
        m_p1->m_Velocity[0] *= -0.9;
    }
}