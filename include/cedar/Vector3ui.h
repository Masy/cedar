//
// Created by masy on 08.02.20.
//

#ifndef CEDAR_VECTOR3UI_H
#define CEDAR_VECTOR3UI_H

#include "Vector2ui.h"

namespace cedar
{

	class Vector3ui
	{
	public:
		unsigned int x;
		unsigned int y;
		unsigned int z;

		Vector3ui();

		explicit Vector3ui(unsigned int values);

		Vector3ui(const Vector2ui &xy, unsigned int z);

		Vector3ui(unsigned int x, unsigned int y, unsigned int z);

		Vector3ui(const Vector3ui &copy);

	};

}

#endif //CEDAR_VECTOR3UI_H
