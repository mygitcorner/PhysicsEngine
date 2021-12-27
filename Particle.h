#pragma once

#include <Eigen/Dense>
#include <SFML/Graphics.hpp>

class Particle : public sf::Drawable, public sf::Transformable {
	Eigen::Vector2d m_position;
	Eigen::Vector2d m_velocity;
	Eigen::Vector2d m_force;

	double m_mass;
	double m_inverseMass;
	double m_damping;
	double m_radius;

public:
	Particle();
	Particle(Eigen::Vector2d position, Eigen::Vector2d velocity, double mass, double damping, double radius);
	Particle(Eigen::Vector2d position, double mass, double radius);
	Particle(Eigen::Vector2d position, Eigen::Vector2d velocity);

	void integrate(double dt);
	void addForce(const Eigen::Vector2d& force);

	Eigen::Vector2d position() const { return m_position; }
	void setPosition(Eigen::Vector2d position) { m_position = position; }

	Eigen::Vector2d velocity() const { return m_velocity; }
	void setVelocity(Eigen::Vector2d velocity) { m_velocity = velocity; }

	Eigen::Vector2d acceleraton() const { return m_force * m_inverseMass; }
	void clearAccumulator() { m_force.setZero(); }

	double mass() const { return m_mass; }
	void setMass(double mass);

	double inverseMass() const { return m_inverseMass; }
	void setInverseMass(double inverseMass);

	double damping() const { return m_damping; }
	void setDamping(double damping) { m_damping = damping; }

	double radius() const { return m_radius; }
	void setRadius(double radius) { m_radius = radius; }

	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
};

