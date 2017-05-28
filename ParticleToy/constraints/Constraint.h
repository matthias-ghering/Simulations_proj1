//
// Created by Matthias Ghering on 23-5-2017.
//

#ifndef SIMULATION_1_CONSTRAINT_H
#define SIMULATION_1_CONSTRAINT_H


#include <vector>

class Constraint {

public:
    virtual float getC() = 0;
    virtual float getCdot() = 0;
    virtual std::vector<Vec2f> getJ() = 0;
    virtual std::vector<Vec2f> getJdot() = 0;

    std::vector<Particle *> particles;
};


#endif //SIMULATION_1_CONSTRAINT_H
