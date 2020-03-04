//
// Created by masy on 03.03.20.
//

#include "cedar/Vector2ui.h"

using namespace cedar;

Vector2ui::Vector2ui() : Vector2ui(0, 0)
{}

Vector2ui::Vector2ui(const unsigned values) : Vector2ui(values, values)
{}

Vector2ui::Vector2ui(const unsigned int x, const unsigned int y)
{
	this->x = x;
	this->y = y;
}

Vector2ui::Vector2ui(const cedar::Vector2ui &copy)
{
	this->x = copy.x;
	this->y = copy.y;
}