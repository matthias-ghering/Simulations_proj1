#include "SpringForce.h"

SpringForce::SpringForce(Particle *p1, Particle *p2, double dist, double ks, double kd) :
        m_p1(p1), m_p2(p2), m_dist(dist), m_ks(ks), m_kd(kd) {}

void SpringForce::draw() {
    glBegin(GL_LINES);
    glColor3f(0.6, 0.7, 0.8);
    glVertex3f(m_p1->m_Position[0], m_p1->m_Position[1], m_p1->m_Position[2]);
    glVertex3f(m_p2->m_Position[0], m_p2->m_Position[1], m_p2->m_Position[2] );
    glEnd();


}

void SpringForce::calc_Force() {
    Vec3f l = m_p1->m_Position - m_p2->m_Position;
    Vec3f ldot = m_p1->m_Velocity - m_p2->m_Velocity;
    float ls = (float) sqrt(l*l); //This calculates the ||l|| also known as the distance between p1 and p2.
    Vec3f f = (m_ks * (ls - m_dist) + m_kd * ((ldot * l)/ls)) * (l/ls);
    m_p1->m_Force += f*-1;
    m_p2->m_Force += f;
}
