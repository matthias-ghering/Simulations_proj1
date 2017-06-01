

#include "../Particle.h"
#include "Force.h"

class StaticForce : public Force{
public:
    StaticForce(Particle *p1, Vec2f sForce);
    void calc_Force() override;
    void draw() override;

private:

    Particle *const m_p1;   // particle 1
    Vec2f m_s;
};
