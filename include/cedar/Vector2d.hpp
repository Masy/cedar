//
// Created by masy on 08.02.20.
//

#ifndef CEDAR_VECTOR2D_HPP
#define CEDAR_VECTOR2D_HPP

/**
 * Base namespace of the cedar engine.
 */
namespace cedar
{

	/**
	 * 2 dimensional double vector implementation based on <a href="https://github.com/JOML-CI/JOML">JOML</a>.
	 */
	class Vector2d
	{
	public:
		double x;
		double y;

		Vector2d();

		explicit Vector2d(double values);

		Vector2d(double x, double y);

		Vector2d(const Vector2d &copy);

	};

}

#endif //CEDAR_VECTOR2D_HPP
