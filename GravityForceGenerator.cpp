#include "GravityForceGenerator.h"

GravityForceGenerator::GravityForceGenerator(double strength) :
	m_gravity(0, strength) {
}

void GravityForceGenerator::apply(Particle* particle) const {
	particle->addForce(particle->mass() * m_gravity);
}
