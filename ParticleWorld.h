#pragma once
#include <list>
#include "ParticleForceRegistry.h"
#include "ParticleContactResolver.h"
#include <SFML/Graphics.hpp>

class Particle;
class ParticleContactGenerator;

class ParticleWorld : public sf::Drawable, public sf::Transformable {
protected:
	std::list<Particle*> m_particles;

	ParticleForceRegistry m_forceRegistry;

	std::list<ParticleContactGenerator*> m_contactGenerators;
	ParticleContactResolver m_contactResolver;

	void integrate(double dt);
	void resolveContacts(double dt);
	
public:
	ParticleWorld(int iterations);

	void update(double dt);

	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
};

