//
// Created by masy on 04.02.20.
//

#include "cedar/Vector4f.h"
#include <cmath>

// Normally i wouldn't do this, but i guess in the implementation file of a class its's ok.
using namespace cedar;

Vector4f::Vector4f() : Vector4f(0.0f, 0.0f, 0.0f, 0.0f)
{}

Vector4f::Vector4f(const float value) : Vector4f(value, value, value, value)
{}

Vector4f::Vector4f(const Vector3f &xyz, const float w) : Vector4f(xyz.x, xyz.y, xyz.z, w)
{}

Vector4f::Vector4f(const Vector2f &xy, const Vector2f &zw) : Vector4f(xy.x, xy.y, zw.x, zw.y)
{}

Vector4f::Vector4f(const float x, const float y, const float z, const float w)
{
	this->x = x;
	this->y = y;
	this->z = z;
	this->w = w;
}

Vector4f::Vector4f(const Vector4f &copy)
{
	this->x = copy.x;
	this->y = copy.y;
	this->z = copy.z;
	this->w = copy.w;
}

float Vector4f::length() const {
	return std::sqrt(this->x * this->x + this->y * this->y + this->z * this->z + this->w * this->w);
}

float Vector4f::lengthSquared() const {
	return this->x * this->x + this->y * this->y + this->z * this->z + this->w * this->w;
}

void Vector4f::normalize() {
	float length = this->length();
	this->x /= length;
	this->y /= length;
	this->z /= length;
	this->w /= length;
}

float Vector4f::distance(const Vector4f &other) const {
	float _x = other.x - this->x;
	float _y = other.y - this->y;
	float _z = other.z - this->z;
	float _w = other.w - this->w;
	return std::sqrt(_x * _x + _y * _y + _z * _z + _w * _w);
}

float Vector4f::distanceSquared(const Vector4f &other) const {
	float _x = other.x - this->x;
	float _y = other.y - this->y;
	float _z = other.z - this->z;
	float _w = other.w - this->w;
	return _x * _x + _y * _y + _z * _z + _w * _w;
}

float Vector4f::dot(const Vector4f &other) const {
	return this->x * other.x + this->y * other.y + this->z * other.z + this->w * other.w;
}

Vector4f &Vector4f::operator=(const Vector4f &other) = default;

Vector4f &Vector4f::operator+=(const Vector4f &other)
{
	this->x += other.x;
	this->y += other.y;
	this->z += other.z;
	this->w += other.w;
	return *this;
}

Vector4f &Vector4f::operator-=(const Vector4f &other)
{
	this->x -= other.x;
	this->y -= other.y;
	this->z -= other.z;
	this->w -= other.w;
	return *this;
}

Vector4f &Vector4f::operator*=(const Vector4f &other)
{
	this->x *= other.x;
	this->y *= other.y;
	this->z *= other.z;
	this->w *= other.w;
	return *this;
}

Vector4f &Vector4f::operator/=(const Vector4f &other)
{
	this->x /= other.x;
	this->y /= other.y;
	this->z /= other.z;
	this->w /= other.w;
	return *this;
}
