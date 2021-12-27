#include "RigidWall.h"
#include "HalfSpace.h"

RigidWall::RigidWall(const Eigen::Vector2d& position, const Eigen::Vector2d& normal, double length)
	: RigidBody(), m_normal(normal), m_length(length)
{
	setPosition(position);
	setInverseMass(0);
	setinverseMomentOfInertia(0);

	m_line[0] = sf::Vertex(sf::Vector2f(static_cast<float>(-length / 2), 0), sf::Color::Black);
	m_line[1] = sf::Vertex(sf::Vector2f(static_cast<float>(length / 2), 0), sf::Color::Black);
	
	setAngle(atan2(normal.x(), -normal.y()));

	HalfSpace* halfSpace = new HalfSpace;
	halfSpace->offset = { 0, 0 };
	halfSpace->angle = 0;
	halfSpace->body = this;
	halfSpace->normal = normal;
	primitives().push_back(halfSpace);
}

Eigen::Vector2d RigidWall::normal() const
{
	return m_normal;
}

double RigidWall::radius() const
{
	return 0.5 * m_length;
}

void RigidWall::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	states.transform *= getTransform();
	target.draw(m_line, 2, sf::Lines, states);
}
