//
// Created by woute on 01/06/2017.
//

#ifndef SIMULATION_1_SCENEBUILDER_H
#define SIMULATION_1_SCENEBUILDER_H

#include "ParticleSystem.h"
#include "forces/GravityForce.h"
#include "forces/DampeningForce.h"
#include "forces/WallForce.h"
#include "forces/SpringForce.h"
#include "forces/StaticForce.h"
#include "forces/FloorForce.h"
#include "constraints/CircularWireConstraint.h"
#include "constraints/RodConstraint.h"
#include "constraints/LineConstraint.h"



ParticleSystem* createEmptyScene();
ParticleSystem* createCircularWireScene();
ParticleSystem* createCurtainScene();

#endif //SIMULATION_1_SCENEBUILDER_H
