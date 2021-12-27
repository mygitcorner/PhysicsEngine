#include "RigidBall.h"
#include "Sphere.h"

RigidBall::RigidBall(const Eigen::Vector2d& position, const Eigen::Vector2d& velocity, double radius, double mass) 
	: RigidBody(), m_radius(radius) 
{
	setPosition(position);
	setVelocity(velocity);
	setMass(mass);
	setinverseMomentOfInertia(0);

	Sphere* sphere = new Sphere;
	sphere->offset = { 0, 0 };
	sphere->angle = 0;
	sphere->body = this;
	sphere->radius = m_radius;
	primitives().push_back(sphere);
}

void RigidBall::draw(sf::RenderTarget& target, sf::RenderStates states) const {
	states.transform *= getTransform();

	sf::CircleShape circle;
	circle.setPosition(static_cast<float>(-m_radius), static_cast<float>(-m_radius));
	circle.setRadius(static_cast<float>(m_radius));
	circle.setOutlineColor(sf::Color::Black);
	circle.setFillColor(sf::Color(199, 70, 70));
	//circle.setOutlineThickness(1);

	target.draw(circle, states);
}

double RigidBall::radius() const
{
	return m_radius;
}
