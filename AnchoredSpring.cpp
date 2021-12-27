#include "AnchoredSpring.h"
#include "RigidBody.h"

AnchoredSpring::AnchoredSpring(Eigen::Vector2d anchor, Eigen::Vector2d localConnectionPoint,
	double springConstant, double restLength) :
	m_anchor(anchor),
	m_localConnectionPoint(localConnectionPoint),
	m_springConstant(springConstant),
	m_restLength(restLength) {
}

void AnchoredSpring::apply(RigidBody* body) const {
	Eigen::Vector2d difference = m_anchor - body->toWorldPoint(m_localConnectionPoint);
	double stretch = difference.norm() - m_restLength;
	Eigen::Vector2d force = m_springConstant * stretch * difference.normalized();
	body->addForceAtPoint(force, m_localConnectionPoint);
}
