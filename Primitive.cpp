#include "Primitive.h"
#include "RigidBody.h"

Eigen::Vector2d Primitive::getGlobal(const Eigen::Vector2d& local) const {
	Eigen::Vector2d bodyLocal = offset + Eigen::Rotation2D<double>(angle) * local;
	return body->toWorldPoint(bodyLocal);
}

Primitive::~Primitive() {
}
