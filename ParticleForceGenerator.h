#pragma once
class Particle;

class ParticleForceGenerator
{
public:
	virtual void apply(Particle* particle) const = 0;
};

