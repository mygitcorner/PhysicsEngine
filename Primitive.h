#pragma once
#include <Eigen/Dense>

class RigidBody;

class Primitive {
public:
	RigidBody* body;
	Eigen::Vector2d offset;
	double angle;

	Eigen::Vector2d getGlobal(const Eigen::Vector2d& local) const;
	virtual ~Primitive();
};

