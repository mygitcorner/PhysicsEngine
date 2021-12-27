#pragma once
#include <SFML/Graphics.hpp>
#include <list>
#include <Eigen/Dense>
#include "PotentialContact.h"
#include "BoundingSphere.h"


class BVHNode : public sf::Drawable, public sf::Transformable {
public:
	BVHNode* parent = nullptr;
	BVHNode* leftChild = nullptr;
	BVHNode* rightChild = nullptr;

	BoundingSphere boundingSphere;
	RigidBody* body = nullptr;

	BVHNode() {
	}

	BVHNode(BVHNode* parent,
		BVHNode* leftChild,
		BVHNode* rightChild,
		BoundingSphere boundingSphere,
		RigidBody* body) 
	{
		this->parent = parent;
		this->leftChild = leftChild;
		this->rightChild = rightChild;
		this->boundingSphere = boundingSphere;
		this->body = body;
	}

	bool isLeaf() const { return !leftChild && !rightChild; }

	bool overlaps(BVHNode* other) {
		return boundingSphere.overlaps(other->boundingSphere);
	}

	void findPotentialContacts(std::list<PotentialContact>& contacts) {
		if (isLeaf())
			return;

		leftChild->findPotentialContacts(contacts);
		rightChild->findPotentialContacts(contacts);
		leftChild->findPotentialContactsWith(contacts, rightChild);
	}

	void recalculateBoundingVolume() {
		BVHNode* node = this;
		while (node) {
			node->boundingSphere = BoundingSphere(
				node->leftChild->boundingSphere,
				node->rightChild->boundingSphere);
			node = node->parent;
		}
	}

	void insert(RigidBody* newBody, const BoundingSphere& newVolume) {
		if (isLeaf()) {
			if (body) {
				leftChild = new BVHNode(this, nullptr, nullptr, boundingSphere, body);
				rightChild = new BVHNode(this, nullptr, nullptr, newVolume, newBody);
				body = nullptr;
				recalculateBoundingVolume();
			}
			else {
				body = newBody;
				boundingSphere = newVolume;
			}
		}
		else {
			if (leftChild->boundingSphere.growth(newVolume) < rightChild->boundingSphere.growth(newVolume))
				leftChild->insert(newBody, newVolume);
			else
				rightChild->insert(newBody, newVolume);
		}
	}

	virtual ~BVHNode() {
		if (parent) {
			BVHNode* sibling = (this == parent->leftChild ? parent->rightChild : parent->leftChild);

			parent->leftChild = sibling->leftChild;
			parent->rightChild = sibling->rightChild;
			parent->boundingSphere = sibling->boundingSphere;
			parent->body = sibling->body;

			if (!sibling->isLeaf()) {
				sibling->leftChild->parent = parent;
				sibling->rightChild->parent = parent;
			}

			sibling->parent = nullptr;
			sibling->leftChild = nullptr;
			sibling->rightChild = nullptr;
			delete sibling;

			parent->recalculateBoundingVolume();
		}

		if (!isLeaf()) {
			leftChild->parent = nullptr;
			delete leftChild;
			rightChild->parent = nullptr;
			delete rightChild;
		}
	}

private:
	void findPotentialContactsWith(std::list<PotentialContact>& contacts,
		BVHNode* other) {
		if (!overlaps(other))
			return;

		if (isLeaf() && other->isLeaf())
			contacts.push_back({ body, other->body });
		else if (isLeaf() && !other->isLeaf()) {
			other->leftChild->findPotentialContactsWith(contacts, this);
			other->rightChild->findPotentialContactsWith(contacts, this);
		}
		else if (!isLeaf() && other->isLeaf()) {
			this->leftChild->findPotentialContactsWith(contacts, other);
			this->rightChild->findPotentialContactsWith(contacts, other);
		}
		else {
			double size = boundingSphere.size();
			double otherSize = other->boundingSphere.size();

			BVHNode* largerNode = (size > otherSize ? this : other);
			BVHNode* smallerNode = (largerNode == other ? this : other);

			largerNode->leftChild->findPotentialContactsWith(contacts, smallerNode);
			largerNode->rightChild->findPotentialContactsWith(contacts, smallerNode);
		}
	}

public:
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override {
		states.transform *= getTransform();

		Eigen::Vector2d center = boundingSphere.center();
		double radius = boundingSphere.radius();

		sf::CircleShape circle;
		circle.setPointCount(100);
		circle.setPosition(static_cast<float>(center.x() - radius), static_cast<float>(center.y() - radius));
		circle.setRadius(static_cast<float>(radius));
		circle.setOutlineColor(sf::Color::Black);
		circle.setOutlineThickness(1);

		target.draw(circle, states);

		if (!isLeaf()) {
			leftChild->draw(target, states);
			rightChild->draw(target, states);
		}
	}
};

