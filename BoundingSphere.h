#pragma once
#include <Eigen/Dense>

class RigidBody;

class BoundingSphere {
	Eigen::Vector2d m_center;
	double m_radius;

public:
	BoundingSphere(Eigen::Vector2d center = { 0, 0 }, double radius = 0);
	BoundingSphere(RigidBody* body);
	BoundingSphere(const BoundingSphere& first, const BoundingSphere& second);

	bool overlaps(const BoundingSphere& other) const;
	double size() const;
	double growth(const BoundingSphere& other) const;

	Eigen::Vector2d center() const { return m_center; }
	double radius() const { return m_radius; }

};

