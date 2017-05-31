#include "Particle.h"
#include <GL/glut.h>

Particle::Particle(const Vec2f &ConstructPos) :
        m_ConstructPos(ConstructPos), m_Position(ConstructPos), m_Velocity(Vec2f(0.0, 0.0)), m_Force(0.0, 0.0), m_Mass(1.0) {
}

Particle::~Particle(void) {
}

void Particle::reset() {
    m_Position = m_ConstructPos;
    m_Velocity = Vec2f(0.0, 0.0);
    m_Force= Vec2f(0.0, 0.0);
    //mass is constant?
}

void Particle::draw() {
    const double h = 0.03;
    glColor3f(1.f, 1.f, 1.f);
    glBegin(GL_QUADS);
    glVertex2f((GLfloat) (m_Position[0] - h / 2.0), (GLfloat) (m_Position[1] - h / 2.0));
    glVertex2f((GLfloat) (m_Position[0] + h / 2.0), (GLfloat) (m_Position[1] - h / 2.0));
    glVertex2f((GLfloat) (m_Position[0] + h / 2.0), (GLfloat) (m_Position[1] + h / 2.0));
    glVertex2f((GLfloat) (m_Position[0] - h / 2.0), (GLfloat) (m_Position[1] + h / 2.0));
    glEnd();
}
