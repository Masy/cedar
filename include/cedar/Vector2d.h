//
// Created by masy on 08.02.20.
//

#ifndef CEDAR_VECTOR2D_H
#define CEDAR_VECTOR2D_H

/**
 * Base namespace of the cedar engine.
 */
namespace cedar
{

	/**
	 * Column Major 4x4 Matrix implementation based on <a href="https://github.com/JOML-CI/JOML">JOML</a>.
	 *
	 * Since OpenGL is column major this will make it easier to upload the data to the graphics card.
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

#endif //CEDAR_VECTOR2D_H
