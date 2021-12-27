#pragma once
#include <Eigen/Dense>
#include <SFML/Graphics.hpp>
#include <list>
#include "Primitive.h"

class RigidBody : public sf::Drawable, public sf::Transformable {
	Eigen::Vector2d m_position;
	Eigen::Vector2d m_velocity;
	Eigen::Vector2d m_force;

	double m_angle;
	double m_angularVelocity;
	double m_torque;

	double m_mass;
	double m_inverseMass;
	double m_momentOfInertia;
	double m_inverseMomentOfInertia;

	double m_damping;
	double m_angularDamping;

	std::list<Primitive*> m_primitives;

public:
	std::list<Primitive*>& primitives() { return m_primitives; }

public:
	RigidBody(Eigen::Vector2d position, Eigen::Vector2d velocity, double angle, double angularVelocity, double mass, double momentOfInertia, double damping, double angularDamping);
	RigidBody(Eigen::Vector2d position, Eigen::Vector2d velocity, double angle, double angularVelocity, double mass, double momentOfInertia);
	RigidBody(Eigen::Vector2d position, Eigen::Vector2d velocity, double mass, double momentOfInertia);
	RigidBody();
	virtual ~RigidBody();

	void integrate(double dt);
	void addForceAtPoint(const Eigen::Vector2d& force, const Eigen::Vector2d& relativePoint);

	Eigen::Vector2d position() const { return m_position; }
	void setPosition(Eigen::Vector2d position);

	Eigen::Vector2d velocity() const { return m_velocity; }
	void setVelocity(Eigen::Vector2d velocity) { m_velocity = velocity; }

	double angle() const { return m_angle; }
	void setAngle(double angle);
	double angularVelocity() const { return m_angularVelocity; }
	void setAngularVelocity(double angularVelocity) { m_angularVelocity = angularVelocity; }

	void clearAccumulator();

	double mass() const { return m_mass; }
	void setMass(double mass);
	double inverseMass() const { return m_inverseMass; }
	void setInverseMass(double inverseMass);

	double momentOfInertia() const { return m_momentOfInertia; }
	void setMomentOfInertia(double momentOfInertia);
	double inverseMomentOfInertia() const { return m_inverseMomentOfInertia; }
	void setinverseMomentOfInertia(double inverseMomentOfInertia);

	double damping() const { return m_damping; }
	void setDamping(double damping) { m_damping = damping; }
	double angularDamping() const { return m_angularDamping; }
	void setAngularDamping(double angularDamping) { m_angularDamping = angularDamping; }

	Eigen::Vector2d toWorldPoint(Eigen::Vector2d localPoint) const;

	virtual double radius() const = 0;
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const = 0;
};

