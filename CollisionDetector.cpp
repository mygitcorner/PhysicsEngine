#include "CollisionDetector.h"
#include "PotentialContact.h"
#include "Sphere.h"
#include "Contact.h"
#include "HalfSpace.h"
#include "Box.h"
#include "RigidBody.h"
#include <vector>

void CollisionDetector::findContacts(const std::list<PotentialContact>& potentialContacts,
	std::list<Contact>& contacts) const
{
	for (auto& potentialContact : potentialContacts)
		for (auto& primitive1 : potentialContact.body1->primitives())
			for (auto& primitive2 : potentialContact.body2->primitives())
				findContactBetween(primitive1, primitive2, contacts);
}

void CollisionDetector::findContactBetween(Primitive* primitive1,
	Primitive* primitive2,
	std::list<Contact>& contacts) const
{
	Sphere* sphere1 = dynamic_cast<Sphere*>(primitive1);
	Sphere* sphere2 = dynamic_cast<Sphere*>(primitive2);

	if (sphere1 && sphere2) {
		sphereAndSphere(*sphere1, *sphere2, contacts);
		return;
	}

	HalfSpace* halfSpace1 = dynamic_cast<HalfSpace*>(primitive1);
	HalfSpace* halfSpace2 = dynamic_cast<HalfSpace*>(primitive2);

	if (sphere1 && halfSpace2) {
		sphereAndHalfSpace(*sphere1, *halfSpace2, contacts);
		return;
	}

	if (sphere2 && halfSpace1) {
		sphereAndHalfSpace(*sphere2, *halfSpace1, contacts);
		return;
	}

	Box* box1 = dynamic_cast<Box*>(primitive1);
	Box* box2 = dynamic_cast<Box*>(primitive2);

	if (box1 && halfSpace2) {
		halfSpaceAndBox(*halfSpace2, *box1, contacts);
		return;
	}

	if (box2 && halfSpace1) {
		halfSpaceAndBox(*halfSpace1, *box2, contacts);
		return;
	}

	if (sphere1 && box2) {
		sphereAndBox(*sphere1, *box2, contacts);
		return;
	}

	if (sphere2 && box1) {
		sphereAndBox(*sphere2, *box1, contacts);
		return;
	}

	if (box1 && box2) {
		boxAndBox(*box1, *box2, contacts);
		return;
	}
}

void CollisionDetector::sphereAndSphere(const Sphere& sphere1,
	const Sphere& sphere2,
	std::list<Contact>& contacts) const
{
	Eigen::Vector2d difference = sphere1.getGlobal(sphere1.offset) - sphere2.getGlobal(sphere2.offset);
	double separation = difference.norm();
	double penetration = sphere1.radius + sphere2.radius - separation;

	if (penetration < 0)
		return;

	Eigen::Vector2d contactPoint = sphere2.getGlobal(sphere2.offset) + 0.5 * difference;
	Eigen::Vector2d contactNormal = difference / separation;

	Contact contact = { contactPoint, contactNormal, penetration, 1, sphere1.body, sphere2.body };
	contacts.push_back(contact);
}

void CollisionDetector::sphereAndHalfSpace(const Sphere& sphere,
	const HalfSpace& halfSpace,
	std::list<Contact>& contacts) const
{
	double penetration = sphere.radius - (sphere.getGlobal(sphere.offset) 
		- halfSpace.getGlobal(halfSpace.offset)).dot(halfSpace.normal);

	if (penetration < 0)
		return;

	Eigen::Vector2d contactPoint = sphere.getGlobal(sphere.offset) - sphere.radius * halfSpace.normal;
	Contact contact = { contactPoint, halfSpace.normal, penetration, 1, sphere.body, nullptr };
	contacts.push_back(contact);
}

void CollisionDetector::halfSpaceAndBox(const HalfSpace& halfSpace,
	const Box& box,
	std::list<Contact>& contacts) const
{
	std::vector<Eigen::Vector2d> corners = {
		{ box.halfSize.x(), box.halfSize.y() },
		{ -box.halfSize.x(), box.halfSize.y() },
		{ box.halfSize.x(), -box.halfSize.y() },
		{ -box.halfSize.x(), -box.halfSize.y() }
	};

	for (auto& corner : corners)
		halfSpaceAndCorner(halfSpace, box, box.getGlobal(corner), contacts);
}

void CollisionDetector::halfSpaceAndCorner(const HalfSpace& halfSpace,
	const Box& box,
	const Eigen::Vector2d& corner,
	std::list<Contact>& contacts) const
{
	double penetration = (halfSpace.getGlobal(halfSpace.offset) - corner).dot(halfSpace.normal);

	if (penetration < 0)
		return;

	Contact contact = { corner, halfSpace.normal, penetration, 1, box.body, nullptr };
	contacts.push_back(contact);
}

void CollisionDetector::sphereAndBox(const Sphere& sphere,
	const Box& box,
	std::list<Contact>& contacts) const
{
	Eigen::Vector2d sphereCenter = sphere.getGlobal(sphere.offset);

	std::vector<Eigen::Vector2d> corners = {
		{ box.halfSize.x(), box.halfSize.y() },
		{ -box.halfSize.x(), box.halfSize.y() },
		{ -box.halfSize.x(), -box.halfSize.y() },
		{ box.halfSize.x(), -box.halfSize.y() }
	};

	for (int i = 0; i < corners.size(); i++) {
		Eigen::Vector2d corner1 = box.getGlobal(corners[i]);
		Eigen::Vector2d corner2 = box.getGlobal(corners[(i + 1) % corners.size()]);

		Eigen::Vector2d parallel = (corner2 - corner1).normalized();
		Eigen::Vector2d normal(parallel.y(), -parallel.x());

		double normalDistance = (sphereCenter - corner1).dot(normal);
		if (normalDistance < 0)
			continue;

		Eigen::Vector2d closestPoint = sphereCenter - normalDistance * normal;
		if ((closestPoint - corner1).dot(parallel) < 0)
			closestPoint = corner1;
		else if ((closestPoint - corner2).dot(parallel) > 0)
			closestPoint = corner2;

		Eigen::Vector2d separation = sphereCenter - closestPoint;
		double distance = separation.norm();

		double penetration = sphere.radius - distance;
		if (penetration < 0)
			continue;
			
		Eigen::Vector2d contactNormal = separation / distance;

		Contact contact = { closestPoint, contactNormal, penetration, 1, sphere.body, box.body };
		contacts.push_back(contact);
		return;
	}
}

void CollisionDetector::boxAndBox(const Box& box1,
	const Box& box2,
	std::list<Contact>& contacts) const
{
	std::vector<Eigen::Vector2d> corners1 = {
		{ box1.halfSize.x(), box1.halfSize.y() },
		{ -box1.halfSize.x(), box1.halfSize.y() },
		{ -box1.halfSize.x(), -box1.halfSize.y() },
		{ box1.halfSize.x(), -box1.halfSize.y() }
	};

	std::vector<Eigen::Vector2d> corners2 = {
		{ box2.halfSize.x(), box2.halfSize.y() },
		{ -box2.halfSize.x(), box2.halfSize.y() },
		{ -box2.halfSize.x(), -box2.halfSize.y() },
		{ box2.halfSize.x(), -box2.halfSize.y() }
	};

	for (Eigen::Vector2d corner : corners1)
		cornerAndBox(box1, box1.getGlobal(corner), box2, corners2, contacts);

	for (Eigen::Vector2d corner : corners2)
		cornerAndBox(box2, box2.getGlobal(corner), box1, corners1, contacts);
}

void CollisionDetector::cornerAndBox(const Box& box1,
	const Eigen::Vector2d& corner,
	const Box& box2,
	const std::vector<Eigen::Vector2d>& localCorners,
	std::list<Contact>& contacts) const
{
	for (int i = 0; i < localCorners.size(); i++) {
		Eigen::Vector2d corner1 = box2.getGlobal(localCorners[i]);
		Eigen::Vector2d corner2 = box2.getGlobal(localCorners[(i + 1) % localCorners.size()]);

		Eigen::Vector2d parallel = (corner2 - corner1).normalized();
		Eigen::Vector2d normal(parallel.y(), -parallel.x());

		if ((box1.getGlobal(box1.offset) - corner1).dot(normal) < 0)
			continue;

		double penetration = (corner1 - corner).dot(normal);
		if (penetration < 0)
			continue;

		Eigen::Vector2d closestPoint = corner + penetration * normal;
		if ((closestPoint - corner1).dot(parallel) < 0
			|| (closestPoint - corner2).dot(parallel) > 0)
			continue;

		Contact contact = { closestPoint, normal, penetration, 1, box1.body, box2.body };
		contacts.push_back(contact);
		return;
	}
}
