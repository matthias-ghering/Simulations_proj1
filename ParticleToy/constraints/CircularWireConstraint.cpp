#include "CircularWireConstraint.h"
#include <GL/glut.h>

#define PI 3.1415926535897932384626433832795

static void draw_circle(const Vec2f &vect, double radius) {
    glBegin(GL_LINE_LOOP);
    glColor3f(0.0, 1.0, 0.0);
    for (int i = 0; i < 360; i = i + 18) {
        double degInRad = i * PI / 180;
        glVertex2f((GLfloat) (vect[0] + cos(degInRad) * radius), (GLfloat) (vect[1] + sin(degInRad) * radius));
    }
    glEnd();
}

CircularWireConstraint::CircularWireConstraint(Particle *p, const Vec2f &center, const double radius) :
        m_p(p), m_center(center), m_radius(radius) {
    this->particles.push_back(p);
}

double CircularWireConstraint::getC() {
    Vec2f diff = particles[0]->m_Position - this->m_center;
    return (diff * diff) - (this->m_radius * this->m_radius);
}

double CircularWireConstraint::getCdot() {
    Vec2f diff = particles[0]->m_Position - this->m_center;
    return (2 * diff) * particles[0]->m_Velocity;
}

std::vector<Vec2f> CircularWireConstraint::getJ() {
    std::vector<Vec2f> result;
    result.push_back(2 * (particles[0]->m_Position - this->m_center));
    return result;
}

std::vector<Vec2f> CircularWireConstraint::getJdot() {
    std::vector<Vec2f> result;
    result.push_back(2 * particles[0]->m_Velocity);
    return result;
}

void CircularWireConstraint::draw() {
    draw_circle(m_center, m_radius);
}
