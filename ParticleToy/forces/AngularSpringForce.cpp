#include "AngularSpringForce.h"
#include <cmath>
#include <math.h>
AngularSpringForce::AngularSpringForce(Particle *p1, Particle *p2, Particle *p3, double dist, double rstAngle,double ks,  double kd) :
        m_p1(p1), m_p2(p2), m_p3(p3), m_dist(dist), m_rstAngle(rstAngle), m_ks(ks), m_kd(kd) {
    //The orientation of the original angle is based on if p3 is on the right had side of p1.
    Vec2f arm12 = (m_p1->m_Position - m_p2->m_Position);
    Vec2f arm23 = (m_p3->m_Position - m_p2->m_Position);
    originOrient= -arm12[0]*arm23[1] + arm12[1] * arm23[0];
}

void AngularSpringForce::draw() {
    const double h = 0.04;
    glBegin(GL_LINES);

    glColor3f(0.945, 0.851, 0.566);
    glVertex2f(m_p1->m_Position[0], m_p1->m_Position[1]);
    glVertex2f(m_p2->m_Position[0], m_p2->m_Position[1]);
    glVertex2f(m_p2->m_Position[0], m_p2->m_Position[1]);
    glVertex2f(m_p3->m_Position[0], m_p3->m_Position[1]);

    glLineWidth(10.f);
    glVertex2f((GLfloat) (m_p2->m_Position[0] - h / 2.0), (GLfloat) (m_p2->m_Position[1] - h / 2.0));
    glVertex2f((GLfloat) (m_p2->m_Position[0] + h / 2.0), (GLfloat) (m_p2->m_Position[1] - h / 2.0));
    glVertex2f((GLfloat) (m_p2->m_Position[0] + h / 2.0), (GLfloat) (m_p2->m_Position[1] + h / 2.0));
    glVertex2f((GLfloat) (m_p2->m_Position[0] - h / 2.0), (GLfloat) (m_p2->m_Position[1] + h / 2.0));

    glColor3f(0.9, 0.01, 0.01);
    glLineWidth(10.f);
    glVertex2f((GLfloat) (m_p3->m_Position[0] - h / 2.0), (GLfloat) (m_p3->m_Position[1] - h / 2.0));
    glVertex2f((GLfloat) (m_p3->m_Position[0] + h / 2.0), (GLfloat) (m_p3->m_Position[1] - h / 2.0));
    glVertex2f((GLfloat) (m_p3->m_Position[0] + h / 2.0), (GLfloat) (m_p3->m_Position[1] + h / 2.0));
    glVertex2f((GLfloat) (m_p3->m_Position[0] - h / 2.0), (GLfloat) (m_p3->m_Position[1] + h / 2.0));

    glEnd();
}

static float lenVec(Vec2f v){
    return sqrt(v * v);
}

void AngularSpringForce::calc_Force() {

    if(m_rstAngle > 180){
        m_rstAngle = m_rstAngle - 180;
        m_correctSide = 1;            //This can in the future be used to know if the angle is on the correct side.
    }

    float cosRstA = cosf(M_PI*m_rstAngle/180.0);
    Vec2f arm12 = m_p1->m_Position - m_p2->m_Position;
    Vec2f arm23 = m_p3->m_Position - m_p2->m_Position;
    float lenArm12 = lenVec(arm12);
    float lenArm23 = lenVec(arm23);
    Vec2f dotArm12 = m_p1->m_Velocity-m_p2->m_Velocity;
    Vec2f dotArm23 = m_p2->m_Velocity-m_p3->m_Velocity;
    float cos = (arm12*arm23)/(lenArm12*lenArm23);

    //int onOriginSide = 1;
    float newOrient= -arm12[0]*arm23[1] + arm12[1] * arm23[0];
    if(std::signbit(originOrient)!=std::signbit(newOrient)){
        //printf("wrong origin");
        //onOriginSide = -1;
        m_p1->m_Force += -m_ks*(cos+1.1)*(arm23/lenVec(arm23));
        m_p3->m_Force += -m_ks*(cos+1.1)*(arm12/lenVec(arm12));
    }
    else{
        m_p1->m_Force += -m_ks*(cos-cosRstA)*(arm23/lenVec(arm23));
        m_p3->m_Force += -m_ks*(cos-cosRstA)*(arm12/lenVec(arm12));
    }



    //Regular spring force on arm12.
    Vec2f springForce = (m_ks * (lenArm12 - m_dist) + m_kd * ((dotArm12 * arm12)/lenArm12)) * (arm12/lenArm12) * 5;
    //Angular spring force function.
    //m_p1->m_Force += -m_ks*(cos-cosRstA)*(arm23/lenVec(arm23))*onOriginSide;
    m_p1->m_Force += -1*springForce;
    m_p2->m_Force += springForce;

    //Regular spring force on arm23.
    springForce = (m_ks * (lenArm23 - m_dist) + m_kd * ((dotArm23 * arm23)/lenArm23)) * (arm23/lenArm23) * 5;
    //Angular spring force function.
    //m_p3->m_Force += -m_ks*(cos-cosRstA)*(arm12/lenVec(arm12))*onOriginSide;
    m_p3->m_Force += -1*springForce;
    m_p2->m_Force += springForce;



    //printf("NewO: %f, OldO:%f, %d\n", newOrient, originOrient, std::signbit(originOrient)==std::signbit(newOrient) );
}



