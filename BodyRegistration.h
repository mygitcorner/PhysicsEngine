#pragma once
#include "ForceGenerator.h"

class RigidBody;

class BodyRegistration {
public:
	RigidBody* body;
	ForceGenerator* forceGenerator;

	bool operator==(const BodyRegistration& other) const;
};

