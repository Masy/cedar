//
// Created by masy on 08.02.20.
//

#ifndef CEDAR_VECTOR4I_HPP
#define CEDAR_VECTOR4I_HPP

#include "Vector3i.hpp"

/**
 * Base namespace of the cedar engine.
 */
namespace cedar
{

	/**
	 * 4 dimensional integer vector implementation based on <a href="https://github.com/JOML-CI/JOML">JOML</a>.
	 */
	class Vector4i
	{
	public:
		int x;
		int y;
		int z;
		int w;

		Vector4i();

		explicit Vector4i(int values);

		Vector4i(const Vector3i &xyz, int z);

		Vector4i(const Vector2i &xy, const Vector2i &zw);

		Vector4i(int x, int y, int z, int w);

		Vector4i(const Vector4i &copy);

	};

}

#endif //CEDAR_VECTOR4I_HPP
