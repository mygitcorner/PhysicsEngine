#include "HardCollisionGenerator.h"
#include <Eigen/Dense>
#include "Particle.h"
#include "ParticleContact.h"

HardCollisionGenerator::HardCollisionGenerator(Particle* particle1, Particle* particle2, double restitution) :
	ParticleContactGenerator(particle1, particle2, restitution) {
}

int HardCollisionGenerator::fillContact(ParticleContact& contact) {
	Eigen::Vector2d separation = particle1()->position() - particle2()->position();
	double penetration = particle1()->radius() + particle2()->radius() - separation.norm();

	if (penetration <= 0)
		return 0;

	contact.particles[0] = particle1();
	contact.particles[1] = particle2();
	contact.restitution = restitution();
	contact.contactNormal = separation.normalized();
	contact.penetration = penetration;

	return 1;
}
