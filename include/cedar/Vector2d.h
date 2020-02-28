//
// Created by masy on 08.02.20.
//

#ifndef CEDAR_VECTOR2D_H
#define CEDAR_VECTOR2D_H

namespace cedar
{

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
