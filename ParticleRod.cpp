#include "ParticleRod.h"
#include <Eigen/Dense>
#include "Particle.h"
#include "ParticleContact.h"

ParticleRod::ParticleRod(Particle* particle1, Particle* particle2, double length) :
	ParticleContactGenerator(particle1, particle2, 0),
	m_length(length) {
}

int ParticleRod::fillContact(ParticleContact& contact) {
	Eigen::Vector2d separation = particle1()->position() - particle2()->position();
	double distance = separation.norm();

	if (distance == m_length)
		return 0;

	contact.particles[0] = particle1();
	contact.particles[1] = particle2();
	contact.restitution = 0;

	if (distance > m_length) {
		contact.contactNormal = -separation.normalized();
		contact.penetration = distance - m_length;
	}
	else {
		contact.contactNormal = separation.normalized();
		contact.penetration = m_length - distance;
	}

	return 1;
}
