#pragma once
#include "RigidBody.h"
#include <Eigen/Dense>

class RigidWall : public RigidBody
{
	Eigen::Vector2d m_normal;
	double m_length;
	sf::Vertex m_line[2];

public:
	RigidWall(const Eigen::Vector2d& position, const Eigen::Vector2d& normal, double length);

	Eigen::Vector2d normal() const;

	virtual double radius() const override;

	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
};

