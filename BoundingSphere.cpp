#include "BoundingSphere.h"
#include "RigidBody.h"

BoundingSphere::BoundingSphere(Eigen::Vector2d center, double radius) :
	m_center(center), m_radius(radius) {
}

BoundingSphere::BoundingSphere(RigidBody* body) :
	BoundingSphere(body->position(), body->radius()) {
}

BoundingSphere::BoundingSphere(const BoundingSphere& first, const BoundingSphere& second) {
	Eigen::Vector2d d = first.m_center - second.m_center;
	double s = d.norm();

	if (s < first.m_radius - second.m_radius) {
		m_center = first.m_center;
		m_radius = first.m_radius;
	}
	else if (s < second.m_radius - first.m_radius) {
		m_center = second.m_center;
		m_radius = second.m_radius;
	}
	else {
		Eigen::Vector2d u = d / s;
		m_center = 0.5 * (first.m_center + first.m_radius * u
			+ second.m_center - second.m_radius * u);
		m_radius = 0.5 * (first.m_radius + second.m_radius + s);
	}
}

bool BoundingSphere::overlaps(const BoundingSphere& other) const {
	double sumRadii = m_radius + other.m_radius;
	return (other.m_center - m_center).squaredNorm() < sumRadii * sumRadii;
}

double BoundingSphere::size() const {
	return m_radius;
}

double BoundingSphere::growth(const BoundingSphere& other) const {
	return BoundingSphere(*this, other).size() - size();
}
