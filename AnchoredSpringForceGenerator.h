#pragma once
#include "ParticleForceGenerator.h"
#include <Eigen/Dense>

class AnchoredSpringForceGenerator : public ParticleForceGenerator {
	Eigen::Vector2d m_anchor;
	double m_springConstant;
	double m_restLength;

public:
	AnchoredSpringForceGenerator(Eigen::Vector2d anchor, double springConstant, double restLength);

	virtual void apply(Particle* particle) const;
};

