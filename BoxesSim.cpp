#include "BoxesSim.h"
#include "BodyRegistration.h"
#include "RigidBox.h"
#include "Gravity.h"
#include "AnchoredSpring.h"
#include "Spring.h"
#include "Box.h"

BoxesSim::BoxesSim() 
	: Simulation(900, 1000)
{
	m_anchor = { 450, 0 };
	m_localConnectionPoint1 = { -50, 25 };
	m_localConnectionPoint2 = { 50, -25 };
	m_localConnectionPoint3 = { -50, 25 };
	m_springConstant = 20;
	m_restLength = 120;

	m_box1 = new RigidBox({ m_anchor.x() + m_restLength + 50, -25 }, 100, 50);
	m_box1->setMomentOfInertia(8000);
	m_box1->setDamping(0.4);
	m_box1->setAngularDamping(0.4);
	addBody(m_box1);

	forceRegistry().add({ m_box1, new Gravity(2000) });
	forceRegistry().add({ m_box1, new AnchoredSpring(m_anchor, m_localConnectionPoint1,
		m_springConstant, m_restLength) });

	m_box2 = new RigidBox({ m_box1->position().x() + m_restLength + 50, -25 }, 100, 50);
	m_box2->setMomentOfInertia(8000);
	m_box2->setDamping(0.4);
	m_box2->setAngularDamping(0.4);
	addBody(m_box2);

	forceRegistry().add({ m_box1, new Spring(m_localConnectionPoint2, m_box2,
		m_localConnectionPoint3, m_springConstant, m_restLength) });
	forceRegistry().add({ m_box2, new Gravity(2000) });
	forceRegistry().add({ m_box2, new Spring(m_localConnectionPoint3, m_box1,
		m_localConnectionPoint2, m_springConstant, m_restLength) });
}

void BoxesSim::draw(sf::RenderTarget& target, sf::RenderStates states) const 
{
	Simulation::draw(target, states);
	drawLine(m_anchor, m_box1->toWorldPoint(m_localConnectionPoint1), target, states);
	drawLine(m_box1->toWorldPoint(m_localConnectionPoint2),
		m_box2->toWorldPoint(m_localConnectionPoint3), target, states);
}

void BoxesSim::drawLine(const Eigen::Vector2d& p1, const Eigen::Vector2d& p2,
	sf::RenderTarget& target, sf::RenderStates states) const 
{
	sf::Vertex line[] = {
		sf::Vertex(sf::Vector2f(static_cast<float>(p1.x()), static_cast<float>(p1.y()))),
		sf::Vertex(sf::Vector2f(static_cast<float>(p2.x()), static_cast<float>(p2.y())))
	};
	target.draw(line, 2, sf::Lines, states);
}
