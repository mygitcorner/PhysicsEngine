#pragma once
#include "ParticleForceGenerator.h"
#include "Particle.h"

class GravityForceGenerator : public ParticleForceGenerator {
	Eigen::Vector2d m_gravity;

public:
	GravityForceGenerator(double strength);

	virtual void apply(Particle* particle) const;
};

