#include "ParticleContactResolver.h"
#include "ParticleContact.h"
#include <algorithm>

ParticleContactResolver::ParticleContactResolver(int iterations) :
	m_iterations{ iterations } {
}

void ParticleContactResolver::resolveContacts(std::list<ParticleContact> contacts, double dt) {
	if (contacts.empty())
		return;

	for (int i = 0; i < m_iterations; i++) {
		auto it = std::min_element(contacts.begin(), contacts.end(),
			[](auto& c1, auto& c2) {
				return c1.calculateSeparatingVelocity() <
					c2.calculateSeparatingVelocity();
			}
		);

		ParticleContact& minContact = *it;
		if (minContact.calculateSeparatingVelocity() > 0)
			return;
		minContact.resolve(dt);
	}
}
