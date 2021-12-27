#pragma once
#include <Eigen/Dense>
#include "RigidBody.h"

class RigidBox : public RigidBody {
	double m_width;
	double m_height;

public:
	RigidBox(Eigen::Vector2d position, double width, double height);

	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

	double width() const { return m_width; }
	double height() const { return m_height; }

	virtual double radius() const override;
};

