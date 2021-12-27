#pragma once

#include <list>
#include <vector>
#include <Eigen/Dense>

class Sphere;
class HalfSpace;
class Box;
class Contact;
struct PotentialContact;
struct Primitive;

class CollisionDetector {
public:
	void findContacts(const std::list<PotentialContact>& potentialContacts,
		std::list<Contact>& contacts) const;

private:
	void findContactBetween(Primitive* primitive1,
		Primitive* primitive2,
		std::list<Contact>& contacts) const;

	void sphereAndSphere(const Sphere& sphere1,
		const Sphere& sphere2,
		std::list<Contact>& contacts) const;

	void sphereAndHalfSpace(const Sphere& sphere,
		const HalfSpace& halfSpace,
		std::list<Contact>& contacts) const;

	void halfSpaceAndBox(const HalfSpace& halfSpace,
		const Box& box,
		std::list<Contact>& contacts) const;

	void halfSpaceAndCorner(const HalfSpace& halfSpace,
		const Box& box,
		const Eigen::Vector2d& corner,
		std::list<Contact>& contacts) const;

	void sphereAndBox(const Sphere& sphere,
		const Box& box,
		std::list<Contact>& contacts) const;

	void boxAndBox(const Box& box1,
		const Box& box2,
		std::list<Contact>& contacts) const;

	void cornerAndBox(const Box& box1,
		const Eigen::Vector2d& corner,
		const Box& box2,
		const std::vector<Eigen::Vector2d>& corners,
		std::list<Contact>& contacts) const;
};

