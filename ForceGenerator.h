#pragma once
class RigidBody;

class ForceGenerator {
public:
	virtual void apply(RigidBody* body) const = 0;
};

