#pragma once
#include <Eigen/Dense>

class Particle;

class ParticleContact {
public:
	Particle* particles[2];
	double restitution;
	Eigen::Vector2d contactNormal;
	double penetration;

	void resolve(double dt);
	double calculateSeparatingVelocity() const;

private:
	void resolveVelocity(double dt) const;
	void resolveInterpenetration() const;
	double calculateTotalInverseMass() const;
};

