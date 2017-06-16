#pragma once

#include <gfx/vec2.h>
#include <gfx/vec3.h>

class Particle {
public:

    Particle(const Vec3f &ConstructPos);
    Particle* copy(); //used to copy without reference
    virtual ~Particle(void);

    void reset();

    void draw();

    // Used by the constraint solver, which needs to know
    // the index of a particle in a vector of particles
    void setIndex(int i);

    Vec3f m_ConstructPos;
    Vec3f m_Position;
    Vec3f m_Velocity;
    Vec3f m_Force;
    float m_Mass;
    int index;

};
