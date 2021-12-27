#pragma once
#include "RigidBody.h"
#include <Eigen/Dense>

class RigidBall : public RigidBody {
	double m_radius;

public:
	RigidBall(const Eigen::Vector2d& position, const Eigen::Vector2d& velocity, double radius, double mass);

	virtual double radius() const override;

	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
};

