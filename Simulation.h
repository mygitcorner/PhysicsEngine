#pragma once
#include <list>
#include <SFML/Graphics.hpp>
#include "CollisionDetector.h"
#include "ForceRegistry.h"
#include "ContactResolver.h"
#include "CollisionDetector.h"
#include "RigidBody.h"

class BVHNode;

class Simulation : public sf::Drawable, public sf::Transformable {
	double m_width;
	double m_height;

	std::list<RigidBody*> m_bodies;
	ForceRegistry m_forceRegistry;

	BVHNode* m_BVHRoot;
	CollisionDetector m_collisionDetector;
	ContactResolver m_contactResolver;

public:
	Simulation(double width, double height);
	virtual ~Simulation();

	virtual void update(double dt);

	double width() const { return m_width; }
	double height() const { return m_height; }

protected:
	const std::list<RigidBody*>& bodies() const { return m_bodies; }
	void addBody(RigidBody* body);

	ForceRegistry& forceRegistry() { return m_forceRegistry; }

private:
	void integrate(double dt);
	void resolveContacts(double dt);
	void clearAccumulators();

public:
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
};

