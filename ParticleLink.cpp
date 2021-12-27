#include "ParticleLink.h"
#include "Particle.h"
#include "ParticleContact.h"

ParticleLink::ParticleLink(Particle* particle1, Particle* particle2, double restitution, double maxLength) :
	ParticleContactGenerator(particle1, particle2, restitution),
	m_maxLength{ maxLength } {
}

int ParticleLink::fillContact(ParticleContact& contact) {
	Eigen::Vector2d separation = particle1()->position() - particle2()->position();
	double distance = separation.norm();

	if (distance <= m_maxLength)
		return 0;

	contact.particles[0] = particle1();
	contact.particles[1] = particle2();
	contact.restitution = restitution();
	contact.contactNormal = -separation.normalized();
	contact.penetration = distance - m_maxLength;

	return 1;
}
