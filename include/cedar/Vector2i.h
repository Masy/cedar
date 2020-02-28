//
// Created by masy on 08.02.20.
//

#ifndef CEDAR_VECTOR2I_H
#define CEDAR_VECTOR2I_H

namespace cedar
{

	class Vector2i
	{
	public:
		int x;
		int y;

		Vector2i();

		explicit Vector2i(int values);

		Vector2i(int x, int y);

		Vector2i(const Vector2i &copy);

	};

}

#endif //CEDAR_VECTOR2I_H
