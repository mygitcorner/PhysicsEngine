#pragma once
#include "ParticleContactGenerator.h"

class ParticleRod : public ParticleContactGenerator {
	double m_length;

public:
	ParticleRod(Particle* particle1, Particle* particle2, double length);

	virtual int fillContact(ParticleContact& contact) override;

};

