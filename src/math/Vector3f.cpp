//
// Created by masy on 04.02.20.
//

#include "cedar/Vector3f.h"
#include "cedar/Math.h"
#include <cmath>

// Normally i wouldn't do this, but i guess in the implementation file of a class its's ok.
using namespace cedar;

Vector3f::Vector3f() : Vector3f(0.0f, 0.0f, 0.0f)
{}

Vector3f::Vector3f(const float value) : Vector3f(value, value, value)
{}

Vector3f::Vector3f(const Vector2f &xy, const float z) : Vector3f(xy.x, xy.y, z)
{}

Vector3f::Vector3f(const float x, const float y, const float z)
{
	this->x = x;
	this->y = y;
	this->z = z;
}

Vector3f::Vector3f(const Vector3f &other)
{
	this->x = other.x;
	this->y = other.y;
	this->z = other.z;
}

float Vector3f::length() const
{
	return std::sqrt(std::fmaf(this->x, this->x, std::fmaf(this->y, this->y, this->z * this->z)));
}

float Vector3f::lengthSquared() const
{
	return std::fmaf(this->x, this->x, std::fmaf(this->y, this->y, this->z * this->z));
}

void Vector3f::normalize()
{
	float length = this->length();
	if (length != 0.0)
	{
		this->x /= length;
		this->y /= length;
		this->z /= length;
	}
}

float Vector3f::distance(const Vector3f &other) const
{
	float _x = other.x - this->x;
	float _y = other.y - this->y;
	float _z = other.z - this->z;
	return std::sqrt(std::fmaf(_x, _x, std::fmaf(_y, _y, _z * _z)));
}

float Vector3f::distanceSquared(const Vector3f &other) const
{
	float _x = other.x - this->x;
	float _y = other.y - this->y;
	float _z = other.z - this->z;
	return std::fmaf(_x, _x, std::fmaf(_y, _y, _z * _z));
}

float Vector3f::dot(const Vector3f &other) const
{
	return this->x * other.x + this->y * other.y + this->z + other.z;
}

Vector3f *Vector3f::lerp(const Vector3f *other, Vector3f *result, const float t) const
{
	result->x = cedar::lerp(this->x, other->x, t);
	result->y = cedar::lerp(this->y, other->y, t);
	result->z = cedar::lerp(this->z, other->z, t);
	return result;
}

void Vector3f::crossP(const Vector3f &other, Vector3f *result) const
{
	result->x = std::fmaf(this->y, other.z, this->z * other.y);
	result->y = std::fmaf(this->z, other.x, this->x * other.z);
	result->z = std::fmaf(this->x, other.y, this->y * other.x);
}

void Vector3f::rotateX(const float angle)
{
	float sin = std::sin(angle);
	float cos = std::cos(angle);

	float _y = this->y * cos - this->z * sin;
	float _z = this->y * sin + this->z * cos;

	this->y = _y;
	this->z = _z;
}

void Vector3f::rotateY(const float angle)
{
	float sin = std::sin(angle);
	float cos = std::cos(angle);

	float _x = this->x * cos + this->z * sin;
	float _z = -this->x * sin + this->z * cos;

	this->x = _x;
	this->z = _z;
}

void Vector3f::rotateZ(const float angle)
{
	float sin = std::sin(angle);
	float cos = std::cos(angle);

	float _x = this->x * cos - this->y * sin;
	float _y = this->x * sin + this->y * cos;

	this->x = _x;
	this->y = _y;
}

Vector3f &Vector3f::operator=(const Vector3f &other) = default;

Vector3f &Vector3f::operator+=(const Vector3f &other)
{
	this->x += other.x;
	this->y += other.y;
	this->z += other.z;
	return *this;
}

Vector3f &Vector3f::operator+=(const float value)
{
	this->x += value;
	this->y += value;
	this->z += value;
	return *this;
}

Vector3f &Vector3f::operator-=(const Vector3f &other)
{
	this->x -= other.x;
	this->y -= other.y;
	this->z -= other.z;
	return *this;
}

Vector3f &Vector3f::operator-=(const float value)
{
	this->x -= value;
	this->y -= value;
	this->z -= value;
	return *this;
}

Vector3f &Vector3f::operator*=(const Vector3f &other)
{
	this->x *= other.x;
	this->y *= other.y;
	this->z *= other.z;
	return *this;
}

Vector3f &Vector3f::operator*=(const float value)
{
	this->x *= value;
	this->y *= value;
	this->z *= value;
	return *this;
}

Vector3f &Vector3f::operator/=(const Vector3f &other)
{
	this->x /= other.x;
	this->y /= other.y;
	this->z /= other.z;
	return *this;
}

Vector3f &Vector3f::operator/=(const float value)
{
	this->x /= value;
	this->y /= value;
	this->z /= value;
	return *this;
}
