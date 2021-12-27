#pragma once
#include "ParticleContactGenerator.h"

class Particle;
class ParticleContact;

class ParticleLink : public ParticleContactGenerator {
	double m_maxLength;

public:
	ParticleLink(Particle* particle1, Particle* particle2, double restitution, double maxLength);

	virtual int fillContact(ParticleContact& contact) override;
};

