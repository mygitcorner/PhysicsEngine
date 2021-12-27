#pragma once
#include <Eigen/Dense>
#include "Primitive.h"

class Box : public Primitive {
public:
	Eigen::Vector2d halfSize;
};

