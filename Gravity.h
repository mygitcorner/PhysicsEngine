#pragma once
#include "ForceGenerator.h"

class Gravity : public ForceGenerator {
	double m_strength;

public:
	Gravity(double strength);

	virtual void apply(RigidBody* body) const override;
};

