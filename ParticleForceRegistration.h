#pragma once

#pragma once
#include "Particle.h"
#include "ParticleForceGenerator.h"

class ParticleForceRegistration {
public:
	Particle* particle;
	ParticleForceGenerator* forceGenerator;

	bool operator==(const ParticleForceRegistration& reg);
};

