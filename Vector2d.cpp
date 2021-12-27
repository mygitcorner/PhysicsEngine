#include "Vector2d.h"
#include <cmath>

Vector2d::Vector2d() :
	Vector2d(0.0, 0.0) {
}

Vector2d::Vector2d(double _x, double _y) :
	x(_x), y(_y) {
}

double Vector2d::dot(const Vector2d& v) const {
	return x * v.x + y * v.y;
}

double Vector2d::cross(const Vector2d& v) const {
	return x * v.y - y * v.x;
}

double Vector2d::norm() const {
	return sqrt(x * x + y * y);
}

double Vector2d::normSq() const {
	return x * x + y * y;
}

Vector2d& Vector2d::normalize() {
	double inverseNorm = 1 / norm();
	x *= inverseNorm;
	y *= inverseNorm;
	return *this;
}

Vector2d Vector2d::normalized() const
{
	return *this * (1 / norm());
}

Vector2d Vector2d::operator+(const Vector2d& v) const {
	return Vector2d(x + v.x, y + v.y);
}

Vector2d Vector2d::operator-(const Vector2d& v) const {
	return operator+(-v);
}

Vector2d Vector2d::operator-() const {
	return Vector2d(-x, -y);
}

Vector2d& Vector2d::operator+=(const Vector2d& v) {
	x += v.x;
	y += v.y;
	return *this;
}

Vector2d& Vector2d::operator-=(const Vector2d& v) {
	return operator+=(-v);
}

Vector2d Vector2d::operator*(double scalar) const {
	return Vector2d(x * scalar, y * scalar);
}

Vector2d operator*(double scalar, const Vector2d v) {
	return v * scalar;
}

Vector2d& Vector2d::operator*=(double scalar) {
	x *= scalar;
	y *= scalar;
	return *this;
}

Vector2d Vector2d::operator/(double scalar) const {
	return Vector2d(x / scalar, y / scalar);
}

Vector2d& Vector2d::operator/=(double scalar) {
	x /= scalar;
	y /= scalar;
	return *this;
}

Vector2d operator/(double scalar, const Vector2d v) {
	return v / scalar;
}

std::ostream& operator<<(std::ostream& out, const Vector2d& v) {
	out << '(' << v.x << ',' << v.y << ')';
	return out;
}

Vector2d::operator sf::Vector2f() const
{
	return sf::Vector2f(static_cast<float>(x), static_cast<float>(y));
}
