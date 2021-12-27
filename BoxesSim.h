#pragma once
#include "Simulation.h"
#include "HalfSpace.h"
#include "CollisionDetector.h"
#include "ContactResolver.h"
#include <Eigen/Dense>

class RigidBox;

class BoxesSim : public Simulation {
	Eigen::Vector2d m_anchor;
	Eigen::Vector2d m_localConnectionPoint1;
	Eigen::Vector2d m_localConnectionPoint2;
	Eigen::Vector2d m_localConnectionPoint3;

	double m_springConstant;
	double m_restLength;

	RigidBox* m_box1;
	RigidBox* m_box2;

public:
	BoxesSim();

	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

private:
	void drawLine(const Eigen::Vector2d& p1, const Eigen::Vector2d& p2,
		sf::RenderTarget& target, sf::RenderStates states) const;
};

