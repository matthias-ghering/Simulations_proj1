#include "Particle.h"
#include <GL/glut.h>

Particle::Particle(const Vec2f &ConstructPos) :
        m_ConstructPos(ConstructPos), m_Position(ConstructPos), m_Velocity(Vec2f(0.0, 0.0)), m_Force(0.0, 0.0), m_Mass(1.0) {
}

Particle::~Particle(void) {
}

Particle* Particle::copy() {
    Particle *p = new Particle(m_ConstructPos);
    p->m_Position = m_Position;
    p->m_Velocity = m_Velocity;
    p->m_Force = m_Force;
    p->m_Mass = m_Mass;
    return p;

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

void Particle::setIndex(int i) {
    this->index = i;
}
