#include "DotConstraint.h"
#include <GL/glut.h>
#include <iostream>

DotConstraint::DotConstraint(Particle *p1, const Vec2f &center) : m_center(center) {
    this->particles.push_back(p1);
}

double DotConstraint:: getC() {
    Vec2f diff = particles[0]->m_Position - this->m_center;
    return (diff * diff);
}

double DotConstraint::getCdot() {
    Vec2f diff = particles[0]->m_Position - this->m_center;
    return (2.0 * diff) * particles[0]->m_Velocity;
}

std::vector<Vec2f> DotConstraint::getJ() {
    std::vector<Vec2f> result;
    result.push_back(2.0 * (particles[0]->m_Position - this->m_center));
    //result.push_back(2.0 * (this->m_center - particles[0]->m_Position));
    return result;
}

std::vector<Vec2f> DotConstraint::getJdot() {
    std::vector<Vec2f> result;
    result.push_back(particles[0]->m_Velocity);
    //result.push_back(-1.0 *  particles[0]->m_Velocity);
    return result;
}

void DotConstraint::draw() {
}
