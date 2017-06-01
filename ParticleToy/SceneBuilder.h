//
// Created by woute on 01/06/2017.
//

#ifndef SIMULATION_1_SCENEBUILDER_H
#define SIMULATION_1_SCENEBUILDER_H

#include "ParticleSystem.h"
#include "forces/GravityForce.h"
#include "forces/DampeningForce.h"
#include "constraints/CircularWireConstraint.h"
#include "constraints/RodConstraint.h"

ParticleSystem* createEmptyScene();
ParticleSystem* createCircularWireScene();

#endif //SIMULATION_1_SCENEBUILDER_H