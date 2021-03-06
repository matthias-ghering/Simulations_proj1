#include "LineConstraint.h"
#include <GL/glut.h>

LineConstraint::LineConstraint(Particle *p1, float fixed_y) : m_y(fixed_y) {
    this->particles.push_back(p1);
}

double LineConstraint:: getC() {
    float diff = this->particles[0]->m_Position[1] - this->m_y;
    return diff;
}

double LineConstraint::getCdot() {
    float diff = this->particles[0]->m_Position[1] - this->m_y;
    return diff * particles[0]->m_Velocity[1];
}

std::vector<Vec2f> LineConstraint::getJ() {
    std::vector<Vec2f> J;
    J.push_back(Vec2f(0,1));
    return J;
}

std::vector<Vec2f> LineConstraint::getJdot() {
    std::vector<Vec2f> Jdot;
    Jdot.push_back(Vec2f(0,0));
    return Jdot;
}

void LineConstraint::draw() {
    glBegin(GL_LINES);
    glColor3f(0.0, 0.7, 0.6);
    glVertex2f(-10, this->m_y);
    glVertex2f(10, this->m_y);
    glEnd();

}
