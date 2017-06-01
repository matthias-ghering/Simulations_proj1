#include "AngularSpringForce.h"
#include <cmath>
#include <math.h>
AngularSpringForce::AngularSpringForce(Particle *p1, Particle *p2, Particle *p3, double dist, double rstAngle,double ks,  double kd) :
        m_p1(p1), m_p2(p2), m_p3(p3), m_dist(dist), m_rstAngle(cos(rstAngle*(M_PI/180.0))), m_ks(ks), m_kd(kd) {}

void AngularSpringForce::draw() {
    glBegin(GL_LINES);
    glColor3f(0.4, 0.4, 0.4);
    glVertex2f(m_p1->m_Position[0], m_p1->m_Position[1]);
    glVertex2f(m_p2->m_Position[0], m_p2->m_Position[1]);
    glVertex2f(m_p2->m_Position[0], m_p2->m_Position[1]);
    glVertex2f(m_p3->m_Position[0], m_p3->m_Position[1]);
    glEnd();
}

static float distance(Particle* p1, Particle* p2){
    Vec2f distVec = p1->m_Position - p2->m_Position;
    return sqrt(distVec * distVec);
}

static float lenPos(Vec2f v){
    return sqrt(v * v);
}

static float dotVec2f(Vec2f v1,Vec2f v2){
    float dot = v1[0]*v2[0]+v1[1]*v2[1];
    //printf("ehm: %f,%f",v1[0],v1[1]);
    return dot;
}

void AngularSpringForce::calc_Force() {
    /*Vec2f l = m_p1->m_Position - m_p2->m_Position;
    Vec2f ldot = m_p1->m_Velocity - m_p2->m_Velocity;
    float ls = (float) sqrt(l*l); //This calculates the ||l|| also known as the distance between p1 and p2.

    float t1 = (ldot * l);

    Vec2f f = (m_ks * (ls - m_dist) + m_kd * ((ldot * l)/ls)) * (l/ls);
    m_p1->m_Force += f*-1;
    m_p2->m_Force += f;*/
    Vec2f arm12 = m_p1->m_Position - m_p2->m_Position;
    Vec2f arm23 = m_p3->m_Position - m_p2->m_Position;
    float cos = (arm12*arm23)/(lenPos(arm12)*lenPos(arm23));
    //printf("dot:%f, \n",dotVec2f(arm1,arm2));
    printf("cos: %f, %f, %f\n",cos, m_rstAngle, M_PI);

    m_p1->m_Force += -m_ks*(cos-m_rstAngle)*(arm23/lenPos(arm23));
    m_p3->m_Force += -m_ks*(cos-m_rstAngle)*(arm12/lenPos(arm12));

}



