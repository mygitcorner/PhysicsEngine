#include "ParticleWorld.h"
#include "Particle.h"
#include "ParticleContact.h"
#include "ParticleContactGenerator.h"
#include "SpringForceGenerator.h"
#include "ParticleForceRegistration.h"
#include "HardCollisionGenerator.h"
#include "ParticleLink.h"

void ParticleWorld::integrate(double dt) {
	for (auto& particle : m_particles) {
		particle->integrate(dt);
		particle->clearAccumulator();
	}
}

void ParticleWorld::resolveContacts(double dt) {
	std::list<ParticleContact> contacts;

	for (auto& contactGenerator : m_contactGenerators) {
		ParticleContact contact;
		if (contactGenerator->fillContact(contact))
			contacts.push_back(contact);
	}

	m_contactResolver.resolveContacts(contacts, dt);
}

ParticleWorld::ParticleWorld(int iterations) :
	m_contactResolver(iterations) {
}

void ParticleWorld::update(double dt) {
	m_forceRegistry.applyForces();
	integrate(dt);
	resolveContacts(dt);
	for (auto& particle : m_particles)
		particle->clearAccumulator();
}

void ParticleWorld::draw(sf::RenderTarget& target, sf::RenderStates states) const {
	states.transform *= getTransform();

	for (auto& particle : m_particles)
		particle->draw(target, states);
}
