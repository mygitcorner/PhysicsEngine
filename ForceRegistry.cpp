#include "ForceRegistry.h"
#include "BodyRegistration.h"

void ForceRegistry::add(BodyRegistration registration) {
	m_registry.push_back(registration);
}

void ForceRegistry::remove(BodyRegistration registration) {
	m_registry.remove(registration);
}

void ForceRegistry::applyForces() {
	for (auto& registration : m_registry)
		registration.forceGenerator->apply(registration.body);
}