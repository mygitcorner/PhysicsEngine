#pragma once
#include <list>
#include "BodyRegistration.h"

class ForceRegistry {
	std::list<BodyRegistration> m_registry;

public:
	void add(BodyRegistration registration);
	void remove(BodyRegistration registration);
	void applyForces();
};

