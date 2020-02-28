//
// Created by masy on 08.02.20.
//

#ifndef CEDAR_VECTOR4D_H
#define CEDAR_VECTOR4D_H

#include "Vector3d.h"

namespace cedar
{

	class Vector4d
	{
	public:
		double x;
		double y;
		double z;
		double w;

		Vector4d();

		explicit Vector4d(double values);

		Vector4d(const Vector3d &xyz, double z);

		Vector4d(const Vector2d &xy, const Vector2d &zw);

		Vector4d(double x, double y, double z, double w);

		Vector4d(const Vector4d &copy);

	};

}

#endif //CEDAR_VECTOR4D_H
