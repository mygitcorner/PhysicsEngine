#include "ParticleForceRegistry.h"
#include "ParticleForceRegistration.h"

void ParticleForceRegistry::add(ParticleForceRegistration registration) {
	m_registry.push_back(registration);
}

void ParticleForceRegistry::remove(ParticleForceRegistration registration) {
	m_registry.remove(registration);
}

void ParticleForceRegistry::applyForces() {
	for (auto& registration : m_registry)
		registration.forceGenerator->apply(registration.particle);
}
