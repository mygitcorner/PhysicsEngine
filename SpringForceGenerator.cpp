#include "SpringForceGenerator.h"
#include <Eigen/Dense>

SpringForceGenerator::SpringForceGenerator(Particle* otherParticle, double springConstant, double restLength) :
	m_otherParticle(otherParticle),
	m_springConstant(springConstant),
	m_restLength(restLength) {
}

void SpringForceGenerator::apply(Particle* particle) const {
	Eigen::Vector2d difference = m_otherParticle->position() - particle->position();
	double stretch = difference.norm() - m_restLength;
	Eigen::Vector2d force = m_springConstant * stretch * difference.normalized();
	particle->addForce(force);
}
