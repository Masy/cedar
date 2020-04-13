//
// Created by masy on 08.02.20.
//

#ifndef CEDAR_VECTOR2I_HPP
#define CEDAR_VECTOR2I_HPP

/**
 * Base namespace of the cedar engine.
 */
namespace cedar
{

	/**
	 * 2 dimensional integer vector implementation based on <a href="https://github.com/JOML-CI/JOML">JOML</a>.
	 */
	class Vector2i
	{
	public:
		int x;
		int y;

		Vector2i();

		explicit Vector2i(int values);

		Vector2i(int x, int y);

		Vector2i(const Vector2i &copy);

		Vector2i operator *(const Vector2i &rhs);

		Vector2i operator *(float rhs);

	};

}

#endif //CEDAR_VECTOR2I_HPP
