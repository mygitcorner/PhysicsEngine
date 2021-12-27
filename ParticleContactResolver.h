#pragma once
#include <list>

class ParticleContact;

class ParticleContactResolver {
protected:
	int m_iterations;

public:
	ParticleContactResolver(int iterations);

	void setIterations(int iterations) { m_iterations = iterations; }
	void resolveContacts(std::list<ParticleContact> contacts, double dt);
};

