#include "Particle.h"

Particle::Particle() {
}

Particle::Particle(Eigen::Vector2d position, Eigen::Vector2d velocity, double mass, double damping, double radius) :
	m_position(position),
	m_velocity(velocity),
	m_mass(mass),
	m_inverseMass(1 / mass),
	m_damping(damping),
	m_radius(radius) {
	m_force.setZero();
}

Particle::Particle(Eigen::Vector2d position, double mass, double radius) :
	Particle(position, { 0, 0 }, mass, 1, radius) {
}

Particle::Particle(Eigen::Vector2d position, Eigen::Vector2d velocity) :
	Particle(position, velocity, 1, 1, 10) {
}

void Particle::integrate(double dt) {
	m_velocity *= pow(m_damping, dt);
	m_velocity += m_force * m_inverseMass * dt;
	m_position += m_velocity * dt;
}

void Particle::addForce(const Eigen::Vector2d& force) {
	m_force += force;
}

void Particle::setMass(double mass) {
	m_mass = mass;
	m_inverseMass = 1 / mass;
}

void Particle::setInverseMass(double inverseMass) {
	m_inverseMass = inverseMass;
	if (inverseMass != 0.0)
		m_mass = 1 / inverseMass;
}

void Particle::draw(sf::RenderTarget& target, sf::RenderStates states) const {
	states.transform *= getTransform();
	
	sf::CircleShape circle(static_cast<float>(m_radius));
	circle.setFillColor(sf::Color::White);
	circle.setOutlineColor(sf::Color::Black);
	circle.setOutlineThickness(1);

	Eigen::Vector2d position = m_position - Eigen::Vector2d(m_radius, m_radius);
	circle.setPosition(sf::Vector2f(static_cast<float>(position.x()), static_cast<float>(position.y())));

	target.draw(circle, states);
}
