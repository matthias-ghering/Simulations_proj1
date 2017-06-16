#include "Particle.h"
#include <GL/glut.h>

Particle::Particle(const Vec3f &ConstructPos) :
        m_ConstructPos(ConstructPos), m_Position(ConstructPos), m_Velocity(Vec3f(0.0, 0.0, 0.0)), m_Force(0.0, 0.0,0.0), m_Mass(1.0) {
}

Particle::~Particle(void) {
}

void Particle::reset() {
    m_Position = m_ConstructPos;
    m_Velocity = Vec3f(0.0, 0.0,0.0);
    m_Force= Vec3f(0.0, 0.0,0.0);
}

void Particle::draw() {
    const double h = 0.03;

    glBegin(GL_LINES);
    glColor3f(1.f, 1.f, 0.075f);
    glVertex3f((GLfloat) (m_Position[0]), (GLfloat) (m_Position[1]),(GLfloat) (m_Position[2]));
    glVertex3f((GLfloat) (m_Position[0]+m_Velocity[0]*15), (GLfloat) (m_Position[1]+m_Velocity[1]*15), (GLfloat) (m_Position[2]+m_Velocity[2]*15));
    glEnd();


    glBegin(GL_QUADS);
    glColor3f(1.f, 1.f, 1.f);
    glVertex3f((GLfloat) (m_Position[0] - h / 2.0), (GLfloat) (m_Position[1] - h / 2.0), (GLfloat) (m_Position[2] - h / 2.0));
    glVertex3f((GLfloat) (m_Position[0] + h / 2.0), (GLfloat) (m_Position[1] - h / 2.0), (GLfloat) (m_Position[2] - h / 2.0));
    glVertex3f((GLfloat) (m_Position[0] + h / 2.0), (GLfloat) (m_Position[1] + h / 2.0), (GLfloat) (m_Position[2] - h / 2.0));
    glVertex3f((GLfloat) (m_Position[0] - h / 2.0), (GLfloat) (m_Position[1] + h / 2.0), (GLfloat) (m_Position[2] - h / 2.0));

    //TODO: draw all sides (so 6x upper one with changing -h and +h values.
    //https://www3.ntu.edu.sg/home/ehchua/programming/opengl/CG_Examples.html

    //glVertex2f((GLfloat) (m_Position[0]+m_Velocity[0]*10000), (GLfloat) (m_Position[1]+m_Velocity[1]*10000));
    glEnd();

}

void Particle::setIndex(int i) {
    this->index = i;
}
