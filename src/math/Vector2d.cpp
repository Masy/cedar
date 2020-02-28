//
// Created by masy on 10.02.20.
//
#include "cedar/Vector2d.h"
#include <cmath>

using namespace cedar;

Vector2d::Vector2d() : Vector2d(0.0, 0.0)
{}

Vector2d::Vector2d(const double value) : Vector2d(value, value)
{}

Vector2d::Vector2d(const double x, const double y)
{
	this->x = x;
	this->y = y;
}

Vector2d::Vector2d(const cedar::Vector2d &copy)
{
	this->x = copy.x;
	this->y = copy.y;
}
