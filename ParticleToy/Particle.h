#pragma once

#include <gfx/vec2.h>

class Particle {
public:

    Particle(const Vec2f &ConstructPos);
    Particle* copy(); //used to copy without reference
    virtual ~Particle(void);

    void reset();

    void draw();

    // Used by the constraint solver, which needs to know
    // the index of a particle in a vector of particles
    void setIndex(int i);

    Vec2f m_ConstructPos;
    Vec2f m_Position;
    Vec2f m_Velocity;
    Vec2f m_Force;
    float m_Mass;
    int index;

};
