#pragma once
#include "ForceGenerator.h"
#include <Eigen/Dense>

class RigidBody;

class Spring : public ForceGenerator {
	Eigen::Vector2d m_localConnectionPoint;
	RigidBody* m_otherBody;
	Eigen::Vector2d m_otherLocalConnectionPoint;
	double m_springConstant;
	double m_restLength;

public:
	Spring(Eigen::Vector2d localConnectionPoint, RigidBody* otherBody,
		Eigen::Vector2d otherLocalConnectionPoint, double springConstant,
		double restLength);

	virtual void apply(RigidBody* body) const override;
};

