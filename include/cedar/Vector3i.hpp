//
// Created by masy on 08.02.20.
//

#ifndef CEDAR_VECTOR3I_HPP
#define CEDAR_VECTOR3I_HPP

#include "Vector2i.hpp"

/**
 * Base namespace of the cedar engine.
 */
namespace cedar
{

	/**
	 * 3 dimensional integer vector implementation based on <a href="https://github.com/JOML-CI/JOML">JOML</a>.
	 */
	class Vector3i
	{
	public:
		int x;
		int y;
		int z;

		Vector3i();

		explicit Vector3i(int values);

		Vector3i(const Vector2i &xy, int z);

		Vector3i(int x, int y, int z);

		Vector3i(const Vector3i &copy);

	};

}

#endif //CEDAR_VECTOR3I_HPP
