//
// Created by masy on 08.02.20.
//

#ifndef CEDAR_VECTOR2UI_H
#define CEDAR_VECTOR2UI_H

/**
 * Base namespace of the cedar engine.
 */
namespace cedar
{

	/**
	 * 2 dimensional unsigned int vector implementation based on <a href="https://github.com/JOML-CI/JOML">JOML</a>.
	 */
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
