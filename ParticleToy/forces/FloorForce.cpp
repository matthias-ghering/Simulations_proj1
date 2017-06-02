#include "FloorForce.h"

FloorForce::FloorForce(Particle *p1, float fixed_y) :
        m_p1(p1), m_y(fixed_y) {}

void FloorForce::draw() {
    glBegin(GL_LINES);
    glColor3f(0.8, 0.0, 0.0);
    glVertex2f(-10, this->m_y);
    glVertex2f(10, this->m_y);
    glEnd();
}

//Implement horizontal one-way wall by switching direction of force and velocity to positive while under the wall
void FloorForce::calc_Force() {
    if (m_p1->m_Position[1] < m_y){
        if (m_p1->m_Force[1]<0){m_p1->m_Force[1]*= -.5;}
        if (m_p1->m_Velocity[1]<0){m_p1->m_Velocity[1]*= -0.5;}

    }
}