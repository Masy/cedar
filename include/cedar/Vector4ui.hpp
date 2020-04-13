//
// Created by masy on 08.02.20.
//

#ifndef CEDAR_VECTOR4UI_HPP
#define CEDAR_VECTOR4UI_HPP

#include "Vector3ui.hpp"

/**
 * Base namespace of the cedar engine.
 */
namespace cedar
{

	/**
	 * 4 dimensional unsigned integer vector implementation based on <a href="https://github.com/JOML-CI/JOML">JOML</a>.
	 */
	class Vector4ui
	{
	public:
		unsigned int x;
		unsigned int y;
		unsigned int z;
		unsigned int w;

		Vector4ui();

		explicit Vector4ui(unsigned int values);

		Vector4ui(const Vector3ui &xyz, unsigned int w);

		Vector4ui(const Vector2ui &xy, const Vector2ui &zw);

		Vector4ui(unsigned int x, unsigned int y, unsigned int z, unsigned int w);

		Vector4ui(const Vector4ui &copy);

	};

}

#endif //CEDAR_VECTOR4UI_HPP
