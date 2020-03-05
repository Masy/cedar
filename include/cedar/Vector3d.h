//
// Created by masy on 08.02.20.
//

#ifndef CEDAR_VECTOR3D_H
#define CEDAR_VECTOR3D_H

#include "Vector2d.h"

/**
 * Base namespace of the cedar engine.
 */
namespace cedar
{

	/**
	 * 3 dimensional double vector implementation based on <a href="https://github.com/JOML-CI/JOML">JOML</a>.
	 */
	class Vector3d
	{
	public:
		double x;
		double y;
		double z;

		Vector3d();

		explicit Vector3d(double values);

		Vector3d(const Vector2d &xy, double z);

		Vector3d(double x, double y, double z);

		Vector3d(const Vector3d &copy);

	};

}

#endif //CEDAR_VECTOR3D_H
