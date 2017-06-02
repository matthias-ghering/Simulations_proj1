#ifndef SIMULATIONS_PROJ1_GRAVITYFORCE_H
#define SIMULATIONS_PROJ1_GRAVITYFORCE_H

#include "Force.h"
#include "../Particle.h"

class GravityForce : public Force {

public:
    GravityForce(Particle *p1);
    void calc_Force() override;
    void draw() override;

private:
    Particle *m_p1;   // particle 1
    Vec2f gravitationalForce;
};


#endif //SIMULATIONS_PROJ1_GRAVITYFORCE_H
