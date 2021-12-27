#pragma once
#include <Eigen/Dense>

class RigidBody;

class Contact {
public:
	Eigen::Vector2d contactPoint;
	Eigen::Vector2d contactNormal;
	double penetration;
	double restitution;

	RigidBody* body1;
	RigidBody* body2;

	void resolveContact() const;
	void resolveCollision() const;
	void resolvePenetration() const;
	double calculateSeparatingVelocity() const;

private:
	double cross2d(const Eigen::Vector2d& v1, const Eigen::Vector2d& v2) const;
};

