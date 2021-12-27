#pragma once
#include "ParticleContactGenerator.h"

class HardCollisionGenerator : public ParticleContactGenerator {
public:
	HardCollisionGenerator(Particle* particle1, Particle* particle2, double restitution);

	virtual int fillContact(ParticleContact& contact) override;
};

