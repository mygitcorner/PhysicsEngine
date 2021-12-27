#pragma once
#include "Primitive.h"
#include <Eigen/Dense>

class HalfSpace : public Primitive {
public:
	Eigen::Vector2d normal;
};

