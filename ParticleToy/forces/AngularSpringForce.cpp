#include "AngularSpringForce.h"

AngularSpringForce::AngularSpringForce(Particle *p1, Particle *p2, Particle *p3, double dist, double ks, double kd) :
        m_p1(p1), m_p2(p2), m_p3(p3), m_dist(dist), m_ks(ks), m_kd(kd) {}

void AngularSpringForce::draw() {
    glBegin(GL_LINES);
    glColor3f(0.4, 0.4, 0.4);
    glVertex2f(m_p1->m_Position[0], m_p1->m_Position[1]);
    glVertex2f(m_p2->m_Position[0], m_p2->m_Position[1]);
    glVertex2f(m_p2->m_Position[0], m_p2->m_Position[1]);
    glVertex2f(m_p3->m_Position[0], m_p3->m_Position[1]);
    glEnd();
}

void AngularSpringForce::calc_Force() {
    Vec2f l = m_p1->m_Position - m_p2->m_Position;
    Vec2f ldot = m_p1->m_Velocity - m_p2->m_Velocity;
    float ls = (float) sqrt(l*l); //This calculates the ||l|| also known as the distance between p1 and p2.

    float t1 = (ldot * l);

    Vec2f f = (m_ks * (ls - m_dist) + m_kd * ((ldot * l)/ls)) * (l/ls);
    m_p1->m_Force += f*-1;
    m_p2->m_Force += f;
}
