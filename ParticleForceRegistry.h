#pragma once
#include <list>

class ParticleForceRegistration;

class ParticleForceRegistry {
	std::list<ParticleForceRegistration> m_registry;

public:
	void add(ParticleForceRegistration registration);
	void remove(ParticleForceRegistration registration);
	void applyForces();
};