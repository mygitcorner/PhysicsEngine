#include "SpringWorld.h"
#include "Particle.h"
#include "SpringForceGenerator.h"
#include "ParticleForceRegistration.h"
#include "HardCollisionGenerator.h"
#include "ParticleLink.h"

SpringWorld::SpringWorld(int iterations) :
	ParticleWorld(iterations) {
	m_particles = {
		new Particle({ 100, 350 }, { -200, 100 }),
		new Particle({ 200, 350 }, { 200, -100 }),
		new Particle({ 300, 350 }, { 200, 100 }),
		new Particle({ 380, 350 }, { -200, -100 }),
		new Particle({ 500, 350 }, { -200, -100 }),
		new Particle({ 600, 350 }, { 200, -100 }),
		new Particle({ 700, 350 }, { 200, 100 }),
		new Particle({ 750, 350 }, {-200, 100 })
	};

	for (auto& particle : m_particles) {
		if (particle == m_particles.front())
			continue;

		m_forceRegistry.add({ particle, new SpringForceGenerator(m_particles.front(), 1, 0) });
		m_forceRegistry.add({ m_particles.front(), new SpringForceGenerator(particle, 1, 0) });
	}

	for (auto& particle1 : m_particles) {
		for (auto& particle2 : m_particles) {
			if (particle1 == particle2)
				continue;

			HardCollisionGenerator* gen = new HardCollisionGenerator(particle1, particle2, 1);
			m_contactGenerators.push_back(gen);
		}
	}

	ParticleLink* link = new ParticleLink(m_particles.front(), *(++m_particles.begin()), 0, 50);
	m_contactGenerators.push_back(link);
}
