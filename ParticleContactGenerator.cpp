#include "ParticleContactGenerator.h"

ParticleContactGenerator::ParticleContactGenerator(Particle* particle1, Particle* particle2, double restitution) :
	m_particle1(particle1),
	m_particle2(particle2),
	m_restitution(restitution) {
}
