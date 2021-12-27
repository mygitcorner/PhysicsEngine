#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>

class Vector2d
{
public:
	double x, y;

	Vector2d();
	Vector2d(double _x, double _y);

	double dot(const Vector2d& v) const;
	double cross(const Vector2d& v) const;

	double norm() const;
	double normSq() const;
	Vector2d& normalize();
	Vector2d normalized() const;

	Vector2d operator+(const Vector2d& v) const;
	Vector2d& operator+=(const Vector2d& v);

	Vector2d operator-(const Vector2d& v) const;
	Vector2d operator-() const;
	Vector2d& operator-=(const Vector2d& v);

	Vector2d operator*(double scalar) const;
	friend Vector2d operator*(double scalar, const Vector2d v);
	Vector2d& operator*=(double scalar);

	Vector2d operator/(double scalar) const;
	friend Vector2d operator/(double scalar, const Vector2d v);
	Vector2d& operator/=(double scalar);

	friend std::ostream& operator<<(std::ostream& out, const Vector2d& v);

	operator sf::Vector2f() const;
};

