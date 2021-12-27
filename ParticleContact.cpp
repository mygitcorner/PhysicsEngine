#include "ParticleContact.h"
#include "Particle.h"

void ParticleContact::resolve(double dt) {
	resolveVelocity(dt);
	resolveInterpenetration();
}

double ParticleContact::calculateSeparatingVelocity() const {
	Eigen::Vector2d relVelocity = particles[0]->velocity();
	if (particles[1])
		relVelocity -= particles[1]->velocity();
	return relVelocity.dot(contactNormal);
}

void ParticleContact::resolveVelocity(double dt) const {
	double separatingVelocity = calculateSeparatingVelocity();

	if (separatingVelocity >= 0)
		return;

	double newSeparatingVelocity = -restitution * separatingVelocity;

	Eigen::Vector2d accCausedVelocity = particles[0]->acceleraton();
	if (particles[1])
		accCausedVelocity -= particles[1]->acceleraton();
	double accCausedSepVelocity = accCausedVelocity.dot(contactNormal) * dt;

	if (accCausedSepVelocity < 0) {
		newSeparatingVelocity += restitution * accCausedSepVelocity;

		if (newSeparatingVelocity < 0)
			newSeparatingVelocity = 0;
	}

	double separatingVelocityChange = newSeparatingVelocity - separatingVelocity;

	double totalInverseMass = calculateTotalInverseMass();
	if (totalInverseMass <= 0)
		return;

	Eigen::Vector2d velocityChangePerIMass = separatingVelocityChange / totalInverseMass * contactNormal;

	particles[0]->setVelocity(particles[0]->velocity()
		+ velocityChangePerIMass * particles[0]->inverseMass());
	if (particles[1])
		particles[1]->setVelocity(particles[1]->velocity()
			- velocityChangePerIMass * particles[1]->inverseMass());
}

void ParticleContact::resolveInterpenetration() const {
	if (penetration <= 0)
		return;

	double totalInverseMass = calculateTotalInverseMass();
	if (totalInverseMass <= 0)
		return;

	Eigen::Vector2d displacementPerIMass = -penetration / totalInverseMass * contactNormal;

	particles[0]->setPosition(particles[0]->position() 
		- displacementPerIMass * particles[0]->inverseMass());
	if (particles[1])
		particles[1]->setPosition(particles[1]->position()
			+ displacementPerIMass * particles[1]->inverseMass());
}

double ParticleContact::calculateTotalInverseMass() const {
	double totalInverseMass = particles[0]->inverseMass();
	if (particles[1])
		totalInverseMass += particles[1]->inverseMass();
	return totalInverseMass;
}
