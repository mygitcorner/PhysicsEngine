#pragma once
class Particle;
class ParticleContact;

class ParticleContactGenerator {
	Particle* m_particle1;
	Particle* m_particle2;
	double m_restitution;

public:
	ParticleContactGenerator(Particle* particle1, Particle* particle2, double restitution);

	virtual int fillContact(ParticleContact& contact) = 0;
	Particle* particle1() const { return m_particle1; }
	Particle* particle2() const { return m_particle2; }
	double restitution() const { return m_restitution; }
};

