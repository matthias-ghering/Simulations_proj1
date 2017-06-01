#include "RodConstraint.h"
#include <GL/glut.h>

WallConstraint::WallConstraint(Particle *p1, double fixed_x) : m_dist(dist) {
    this->particles.push_back(p1);
}

double WallConstraint:: getC() {
    Vec2f diff = this->particles[0]->m_Position - this->particles[1]->m_Position;
    return (diff * diff) - (this->m_dist * this->m_dist);
}

double WallConstraint::getCdot() {
    Vec2f diff1 = this->particles[0]->m_Position - this->particles[1]->m_Position;
    Vec2f diff2 = this->particles[1]->m_Position - this->particles[0]->m_Position;
    return (2 * diff1) * this->particles[0]->m_Velocity + (2 * diff2) * this->particles[1]->m_Velocity;
}

std::vector<Vec2f> WallConstraint::getJ() {
    std::vector<Vec2f> J;
    J.push_back(2 * (this->particles[0]->m_Position - this->particles[1]->m_Position));
    J.push_back(2 * (this->particles[1]->m_Position - this->particles[0]->m_Position));
    return J;
}

std::vector<Vec2f> WallConstraint::getJdot() {
    std::vector<Vec2f> Jdot;
    Jdot.push_back(2 * (this->particles[0]->m_Velocity - this->particles[1]->m_Velocity));
    Jdot.push_back(2 * (this->particles[1]->m_Velocity- this->particles[0]->m_Velocity));
    return Jdot;
}

void WallConstraint::draw() {
    glBegin(GL_LINES);
    glColor3f(0.8, 0.7, 0.6);
    glVertex2f(this->particles[0]->m_Position[0], this->particles[0]->m_Position[1]);
    glColor3f(0.8, 0.7, 0.6);
    glVertex2f(this->particles[1]->m_Position[0], this->particles[1]->m_Position[1]);
    glEnd();

}
