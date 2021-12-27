#include "AnchoredSpringForceGenerator.h"
#include "Particle.h"

AnchoredSpringForceGenerator::AnchoredSpringForceGenerator(Eigen::Vector2d anchor, double springConstant, double restLength) :
	m_anchor(anchor), m_springConstant(springConstant), m_restLength(restLength) {
}

void AnchoredSpringForceGenerator::apply(Particle* particle) const {
	Eigen::Vector2d difference = m_anchor - particle->position();
	double stretch = difference.norm() - m_restLength;
	Eigen::Vector2d force = m_springConstant * stretch * difference.normalized();
	particle->addForce(force);
}
