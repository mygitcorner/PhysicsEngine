#include "Contact.h"
#include "RigidBody.h"
#include <iostream>


void Contact::resolveContact() const {
	resolveCollision();
	resolvePenetration();
}

void Contact::resolveCollision() const {
	double separatingVelocity = calculateSeparatingVelocity();
	if (separatingVelocity > 0)
		return;

	double separatingVelocityChange = -(1 + restitution) * separatingVelocity;

	double linearChangePerImpulse = body1->inverseMass();
	if (body2)
		linearChangePerImpulse += body2->inverseMass();

	Eigen::Vector2d q1 = contactPoint - body1->position();
	Eigen::Vector2d q2 = (body2 ? contactPoint - body2->position() : Eigen::Vector2d{ 0, 0 });

	Eigen::Vector2d AngularChangePerImpulse = q1 * cross2d(q1, contactNormal)
		* body1->inverseMomentOfInertia();
	if (body2)
		AngularChangePerImpulse += q2 * cross2d(q2, contactNormal)
		* body2->inverseMomentOfInertia();

	double separatingVelocityChangePerImpulse = linearChangePerImpulse
		+ cross2d(AngularChangePerImpulse, contactNormal);
	if (separatingVelocityChangePerImpulse == 0)
		return;

	Eigen::Vector2d impulse = separatingVelocityChange
		/ separatingVelocityChangePerImpulse * contactNormal;

	body1->setVelocity(body1->velocity() + body1->inverseMass() * impulse);
	body1->setAngularVelocity(body1->angularVelocity()
		+ body1->inverseMomentOfInertia() * cross2d(q1, impulse));
	if (body2) {
		body2->setVelocity(body2->velocity() - body2->inverseMass() * impulse);
		body2->setAngularVelocity(body2->angularVelocity()
			- body2->inverseMomentOfInertia() * cross2d(q2, impulse));
	}
}

void Contact::resolvePenetration() const {
	double totalIMass = body1->inverseMass();
	if (body2)
		totalIMass += body2->inverseMass();

	if (totalIMass == 0)
		return;

	Eigen::Vector2d movePerIMass = penetration * contactNormal / totalIMass;

	body1->setPosition(body1->position()
		+ body1->inverseMass() * movePerIMass);
	if (body2)
		body2->setPosition(body2->position()
			- body2->inverseMass() * movePerIMass);
}

double Contact::calculateSeparatingVelocity() const {
	Eigen::Vector2d linearSeparatingVelocity = body1->velocity();
	Eigen::Vector2d angularSeparatingVelocity = (contactPoint - body1->position()) * body1->angularVelocity();

	if (body2) {
		linearSeparatingVelocity -= body2->velocity();
		angularSeparatingVelocity -= (contactPoint - body2->position()) * body2->angularVelocity();
	}

	return linearSeparatingVelocity.dot(contactNormal) 
		+ cross2d(angularSeparatingVelocity, contactNormal);
}


double Contact::cross2d(const Eigen::Vector2d& v1, const Eigen::Vector2d& v2) const {
	return v1.x() * v2.y() - v1.y() * v2.x();
}