#include "WallForce.h"

WallForce::WallForce(Particle *p1, float fixed_x) :
        m_p1(p1), m_x(fixed_x) {}

void WallForce::draw() {
    glBegin(GL_LINES);
    glColor3f(0.8, 0.0, 0.0);
    glVertex3f(this->m_x, -10, -10);
    glVertex3f(this->m_x, 10, 10);
    glEnd();
}

//Implement vertical one-way wall by switching direction of force and velocity to positive while on left side of wall
void WallForce::calc_Force() {
    if (m_p1->m_Position[0] < m_x){
        if (m_p1->m_Force[0]<0)
            {m_p1->m_Force[0]*= -0.5;}
        if (m_p1->m_Velocity[0]<0)
            {m_p1->m_Velocity[0]*= -0.5;}
    }
}
