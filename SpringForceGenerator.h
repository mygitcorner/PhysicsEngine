#pragma once
#include "ParticleForceGenerator.h"
#include "Particle.h"

class SpringForceGenerator : public ParticleForceGenerator
{
	Particle* m_otherParticle; 
	double m_springConstant;
	double m_restLength;

public:
	SpringForceGenerator(Particle* otherParticle, double springConstant, double restLength);

	virtual void apply(Particle* particle) const override;
};

