//
// Created by masy on 04.02.20.
//

#include "cedar/Vector2f.hpp"
#include <cmath>

// Normally i wouldn't do this, but i guess in the implementation file of a class its's ok.
using namespace cedar;

Vector2f::Vector2f() : Vector2f(0.0f, 0.0f)
{}

Vector2f::Vector2f(const float value) : Vector2f(value, value)
{}

Vector2f::Vector2f(const float x, const float y)
{
	this->x = x;
	this->y = y;
}

Vector2f::Vector2f(const Vector2f &copy)
{
	this->x = copy.x;
	this->y = copy.y;
}

float Vector2f::length() const
{
	return std::sqrt(x * x + y * y);
}

float Vector2f::lengthSquared() const
{
	return x * x + y * y;
}

void Vector2f::normalize()
{
	float length = this->length();
	this->x /= length;
	this->y /= length;
}

float Vector2f::distance(const Vector2f &other) const
{
	float _x = other.x - this->x;
	float _y = other.y - this->y;
	return std::sqrt(_x * _x + _y * _y);
}

float Vector2f::distanceSquared(const Vector2f &other) const
{
	float _x = other.x - this->x;
	float _y = other.y - this->y;
	return _x * _x + _y * _y;
}

float Vector2f::dot(const Vector2f &other) const
{
	return this->x * other.x + this->y * other.y;
}

Vector2f &Vector2f::operator=(const Vector2f &other) = default;

Vector2f &Vector2f::operator+=(const Vector2f &other)
{
	this->x += other.x;
	this->y += other.y;
	return *this;
}

Vector2f &Vector2f::operator-=(const Vector2f &other)
{
	this->x -= other.x;
	this->y -= other.y;
	return *this;
}

Vector2f &Vector2f::operator*=(const Vector2f &other)
{
	this->x *= other.x;
	this->y *= other.y;
	return *this;
}

Vector2f &Vector2f::operator/=(const Vector2f &other)
{
	this->x /= other.x;
	this->y /= other.y;
	return *this;
}
