//
// Created by masy on 03.03.20.
//

#include "cedar/Vector4ui.hpp"

using namespace cedar;

Vector4ui::Vector4ui() : Vector4ui(0, 0, 0, 0)
{}

Vector4ui::Vector4ui(const unsigned int values) : Vector4ui(values, values, values, values)
{}

Vector4ui::Vector4ui(const cedar::Vector3ui &xyz, const unsigned int w) : Vector4ui(xyz.x, xyz.y, xyz.z, w)
{}

Vector4ui::Vector4ui(const cedar::Vector2ui &xy, const cedar::Vector2ui &zw) : Vector4ui(xy.x, xy.y, zw.x, zw.y)
{}

Vector4ui::Vector4ui(const unsigned int x, const unsigned int y, const unsigned int z, const unsigned int w)
{
	this->x = x;
	this->y = y;
	this->z = z;
	this->w = w;
}

Vector4ui::Vector4ui(const cedar::Vector4ui &copy)
{
	this->x = copy.x;
	this->y = copy.y;
	this->z = copy.z;
	this->w = copy.w;
}
