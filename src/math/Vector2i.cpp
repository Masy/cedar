//
// Created by masy on 03.03.20.
//

#include "cedar/Vector2i.hpp"

using namespace cedar;

Vector2i::Vector2i() : Vector2i(0, 0)
{}

Vector2i::Vector2i(const int values) : Vector2i(values, values)
{}

Vector2i::Vector2i(const int x, const int y)
{
	this->x = x;
	this->y = y;
}

Vector2i::Vector2i(const cedar::Vector2i &copy)
{
	this->x = copy.x;
	this->y = copy.y;
}

Vector2i Vector2i::operator*(const cedar::Vector2i &rhs)
{
	return Vector2i(this->x *rhs.x, this->y * rhs.y);
}

Vector2i Vector2i::operator*(const float rhs)
{
	return Vector2i(this->x *rhs, this->y * rhs);
}
