//
// Created by masy on 08.02.20.
//

#ifndef CEDAR_VECTOR2UI_H
#define CEDAR_VECTOR2UI_H

namespace cedar
{

	class Vector2ui
	{
	public:
		unsigned int x;
		unsigned int y;

		Vector2ui();

		explicit Vector2ui(unsigned int values);

		Vector2ui(unsigned int x, unsigned int y);

		Vector2ui(const Vector2ui &copy);

	};

}

#endif //CEDAR_VECTOR2UI_H
