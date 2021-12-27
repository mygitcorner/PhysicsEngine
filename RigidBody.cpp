#include "RigidBody.h"
#include <cmath>

RigidBody::RigidBody(Eigen::Vector2d position, Eigen::Vector2d velocity, double angle,
	double angularVelocity, double mass, double momentOfInertia, double damping, double angularDamping) :
	m_position(position),
	m_velocity(velocity),
	m_angle(angle),
	m_angularVelocity(angularVelocity),
	m_mass(mass),
	m_inverseMass(1 / mass),
	m_momentOfInertia(momentOfInertia),
	m_inverseMomentOfInertia(1 / momentOfInertia),
	m_damping(damping),
	m_angularDamping(angularDamping),
	m_force(0, 0),
	m_torque(0) {
}

RigidBody::RigidBody(Eigen::Vector2d position, Eigen::Vector2d velocity, double angle,
	double angularVelocity, double mass, double momentOfInertia) :
	RigidBody(position, velocity, angle, angularVelocity, mass, momentOfInertia, 1, 1){
}

RigidBody::RigidBody(Eigen::Vector2d position, Eigen::Vector2d velocity, double mass, double momentOfInertia) :
	RigidBody(position, velocity, 0, 0, mass, momentOfInertia) {
}

RigidBody::RigidBody() :
	RigidBody({ 0, 0 }, { 0, 0 }, 1, 1) {
}

RigidBody::~RigidBody() {
	for (auto& primitive : m_primitives)
		delete primitive;
}

void RigidBody::integrate(double dt) {
	m_velocity *= pow(m_damping, dt);
	m_velocity += m_force * m_inverseMass * dt;
	setPosition(m_position + m_velocity * dt);

	m_angularVelocity *= pow(m_angularDamping, dt);
	m_angularVelocity += m_torque * m_inverseMomentOfInertia * dt;
	setAngle(m_angle + m_angularVelocity * dt);
}

void RigidBody::addForceAtPoint(const Eigen::Vector2d& force, const Eigen::Vector2d& localPoint) {
	m_force += force;
	Eigen::Vector2d rotatedPoint = Eigen::Rotation2D<double>(m_angle) * localPoint;
	m_torque += rotatedPoint.x() * force.y() - rotatedPoint.y() * force.x();
}

void RigidBody::setPosition(Eigen::Vector2d position) {
	m_position = position;
	sf::Transformable::setPosition(static_cast<float>(position.x()), static_cast<float>(position.y()));
}

void RigidBody::setAngle(double angle) {
	double pi = acos(-1);
	m_angle = fmod(angle + pi, 2 * pi) - pi;
	setRotation(static_cast<float>(angle/ pi * 180 + 180));
}

void RigidBody::clearAccumulator() {
	m_force.setZero();
	m_torque = 0;
}

void RigidBody::setMass(double mass) {
	m_mass = mass;
	m_inverseMass = 1 / mass;
}

void RigidBody::setInverseMass(double inverseMass) {
	m_inverseMass = inverseMass;
	if (inverseMass != 0)
		m_mass = 1 / inverseMass;
}

void RigidBody::setMomentOfInertia(double momentOfInertia) {
	m_momentOfInertia = momentOfInertia;
	m_inverseMomentOfInertia = 1 / momentOfInertia;
}

void RigidBody::setinverseMomentOfInertia(double inverseMomentOfInertia) {
	m_inverseMomentOfInertia = inverseMomentOfInertia;
	if (inverseMomentOfInertia != 0)
		m_momentOfInertia = 1 / inverseMomentOfInertia;
}

Eigen::Vector2d RigidBody::toWorldPoint(Eigen::Vector2d localPoint) const {
	return m_position + Eigen::Rotation2D<double>(m_angle) * localPoint;
}
