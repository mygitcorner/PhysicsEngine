#include "Gravity.h"
#include "RigidBody.h"

Gravity::Gravity(double strength) :
	m_strength(strength) {
}

void Gravity::apply(RigidBody* body) const {
	body->addForceAtPoint({ 0, body->mass() * m_strength }, { 0, 0 });
}
