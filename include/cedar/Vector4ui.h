//
// Created by masy on 08.02.20.
//

#ifndef CEDAR_VECTOR4UI_H
#define CEDAR_VECTOR4UI_H

#include "Vector3ui.h"

namespace cedar
{

	class Vector4ui
	{
	public:
		unsigned int x;
		unsigned int y;
		unsigned int z;
		unsigned int w;

		Vector4ui();

		explicit Vector4ui(unsigned int values);

		Vector4ui(const Vector3ui &xyz, unsigned int w);

		Vector4ui(const Vector2ui &xy, const Vector2ui &zw);

		Vector4ui(unsigned int x, unsigned int y, unsigned int z, unsigned int w);

		Vector4ui(const Vector4ui &copy);

	};

}

#endif //CEDAR_VECTOR4UI_H
