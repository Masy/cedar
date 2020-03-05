//
// Created by masy on 03.03.20.
//

#ifndef TALESOFCATVENTURE_GLYPH_H
#define TALESOFCATVENTURE_GLYPH_H

#include "cedar/Vector2i.h"
#include "cedar/Vector4f.h"

/**
 * Base namespace of the cedar engine.
 */
namespace cedar
{
	/**
	 * Class representing a glyph of a character.
	 */
	class Glyph
	{
	public:
		/**
		 * The size of the glyph in pixel.
		 */
		Vector2i m_size;
		/**
		 * The bearing of the glyph in pixel.
		 *
		 * <p>The bearing is the offset of the glyph image from the origin of the character</p>
		 */
		Vector2i m_bearing;
		/**
		 * The advance of the glyph in pixel.
		 *
		 * <p>The advance is the offset from the origin where the origin of the next character should be.</p>
		 */
		unsigned int m_advance;
		/**
		 * The top-left and bottom-right corner of the glyph in the glyph atlas.
		 *
		 * <p>The uv coordinate are normalized coordinates where 1.0 is the size of the texture.</p>
		 */
		Vector4f m_uvs;

		/**
		 * Creates a glyph placeholder.
		 */
		Glyph();

		/**
		 * Creates a new glyph.
		 *
		 * @param size The size of the glyph in pixel.
		 * @param bearing The bearing of the glyph in pixel.
		 * @param advance The advance of the glyph in pixel.
		 * @param uvs The top-left and bottom-right uv coordinates of the glyph.
		 */
		Glyph(const Vector2i &size, const Vector2i &bearing, unsigned int advance, const Vector4f &uvs);
	};
}

#endif //TALESOFCATVENTURE_GLYPH_H
