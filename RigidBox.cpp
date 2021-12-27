#include "RigidBox.h"
#include "Box.h"

RigidBox::RigidBox(Eigen::Vector2d position, double width, double height) :
	RigidBody(position, { 0, 0 }, 1, 1),
	m_width(width),
	m_height(height) 
{
	Box* box = new Box;
	box->body = this;
	box->offset = { 0, 0 };
	box->angle = 0;
	box->halfSize = 0.5 * Eigen::Vector2d(width, height);

	primitives().push_back(box);
}

void RigidBox::draw(sf::RenderTarget& target, sf::RenderStates states) const {
	states.transform *= getTransform();

	sf::RectangleShape rect(sf::Vector2f(static_cast<float>(m_width), static_cast<float>(m_height)));
	rect.setPosition(static_cast<float>(-m_width / 2), static_cast<float>(-m_height / 2));
	rect.setOutlineColor(sf::Color::Black);
	rect.setFillColor(sf::Color(199, 70, 70));
	//rect.setOutlineThickness(1);

	target.draw(rect, states);
}

double RigidBox::radius() const
{
	double halfWidth = m_width / 2;
	double halfHeight = m_height / 2;
	return sqrt(halfWidth * halfWidth + halfHeight * halfHeight);
}
