//
// Created by masy on 08.02.20.
//

#ifndef CEDAR_VECTOR3I_H
#define CEDAR_VECTOR3I_H

#include "Vector2i.h"

namespace cedar
{

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

#endif //CEDAR_VECTOR3I_H
