#pragma once
#include "ForceGenerator.h"
#include <Eigen/Dense>

class AnchoredSpring : public ForceGenerator {
	Eigen::Vector2d m_anchor;
	Eigen::Vector2d m_localConnectionPoint;
	double m_springConstant;
	double m_restLength;

public:
	AnchoredSpring(Eigen::Vector2d anchor, Eigen::Vector2d localConnectionPoint, double springConstant, double restLength);

	virtual void apply(RigidBody* body) const override;
};

