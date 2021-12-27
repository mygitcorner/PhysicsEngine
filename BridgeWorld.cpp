#include "BridgeWorld.h"
#include "Particle.h"
#include "AnchoredSpringForceGenerator.h"
#include "ParticleForceRegistration.h"
#include "GravityForceGenerator.h"
#include "ParticleRod.h"

BridgeWorld::BridgeWorld(int iterations) :
	ParticleWorld(iterations) {
	Particle* particle1 = new Particle({ 300, 1 }, { 50, 0 }, 1, 0.5, 10);
	Particle* particle2 = new Particle({ 500, 1 }, { 50, 0 }, 1, 0.5, 10);

	m_particles.push_back(particle1);
	m_particles.push_back(particle2);

	m_forceRegistry.add({ particle1, new AnchoredSpringForceGenerator({ 200, 0 }, 10, 200) });
	m_forceRegistry.add({ particle2, new AnchoredSpringForceGenerator({ 600, 0 }, 10, 200) });
	m_forceRegistry.add({ particle1, new GravityForceGenerator(1000) });
	m_forceRegistry.add({ particle2, new GravityForceGenerator(1000) });

	m_contactGenerators.push_back(new ParticleRod(particle1, particle2, 400));
}
