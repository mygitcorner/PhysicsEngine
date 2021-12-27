#include "Simulation.h"
#include "RigidBody.h"
#include "BodyRegistration.h"
#include "BVHNode.h"
#include "BoundingSphere.h"
#include "Contact.h"

Simulation::Simulation(double width, double height) 
	: m_width(width), m_height(height)
{
	m_BVHRoot = new BVHNode;
}

Simulation::~Simulation()
{
	for (auto& body : m_bodies)
		delete body;

	delete m_BVHRoot;
}

void Simulation::update(double dt) 
{
	m_forceRegistry.applyForces();
	integrate(dt);
	resolveContacts(dt);
	clearAccumulators();
}

void Simulation::addBody(RigidBody* body)
{
	m_bodies.push_back(body);
}

void Simulation::integrate(double dt) 
{
	for (auto& body : m_bodies)
		body->integrate(dt);
}

void Simulation::resolveContacts(double dt) 
{
	delete m_BVHRoot;
	m_BVHRoot = new BVHNode;
	for (auto& body : m_bodies)
		m_BVHRoot->insert(body, BoundingSphere(body));

	std::list<PotentialContact> potentialContacts;
	m_BVHRoot->findPotentialContacts(potentialContacts);
	
	std::list<Contact> contacts;
	m_collisionDetector.findContacts(potentialContacts, contacts);

	m_contactResolver.resolveContacts(contacts, 100);
}

void Simulation::clearAccumulators() 
{
	for (auto& body : m_bodies)
		body->clearAccumulator();
}

void Simulation::draw(sf::RenderTarget& target, sf::RenderStates states) const 
{
	states.transform *= getTransform();
	
	//m_BVHRoot->draw(target, states);

	for (auto& body : m_bodies)
		body->draw(target, states);
}
