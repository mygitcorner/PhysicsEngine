#include "Spring.h"
#include "RigidBody.h"

Spring::Spring(Eigen::Vector2d localConnectionPoint, RigidBody* otherBody,
	Eigen::Vector2d otherLocalConnectionPoint, double springConstant, double restLength) :
	m_localConnectionPoint(localConnectionPoint),
	m_otherBody(otherBody),
	m_otherLocalConnectionPoint(otherLocalConnectionPoint),
	m_springConstant(springConstant),
	m_restLength(restLength) {
}

void Spring::apply(RigidBody* body) const {
	Eigen::Vector2d difference = m_otherBody->toWorldPoint(m_otherLocalConnectionPoint)
		- body->toWorldPoint(m_localConnectionPoint);
	double stretch = difference.norm() - m_restLength;
	Eigen::Vector2d force = m_springConstant * stretch * difference.normalized();
	body->addForceAtPoint(force, m_localConnectionPoint);
}
