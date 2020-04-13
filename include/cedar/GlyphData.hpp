//
// Created by masy on 03.03.20.
//

#ifndef CEDAR_GLYPHDATA_HPP
#define CEDAR_GLYPHDATA_HPP

#include "cedar/Vector2i.hpp"
#include "cedar/Vector2ui.hpp"

/**
 * Base namespace of the cedar engine.
 */
namespace cedar
{
	/**
	 * Class for temporarily storing data about a glyph.
	 */
	class GlyphData
	{
	public:
		/**
		 * The unicode of the character this is the glyph of.
		 */
		unsigned int m_unicode;
		/**
		 * The offset of the glyph in the glyph atlas in pixel.
		 */
		Vector2ui m_offset;
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
		 * A pointer to the image data of the glyph.
		 */
		unsigned char *m_data;

		/**
		 * Creates a new glyph data placeholder.
		 */
		GlyphData();

		/**
		 * Creates a new glyph data object.
		 *
		 * @param unicode The unicode of the character this is the glyph of.
		 * @param offset The offset of the glyph in the glyph atlas in pixel.
		 * @param size The size of the glyph in pixel.
		 * @param bearing The bearing of the glyph in pixel.
		 * @param advance The advance of the glyph in pixel.
		 * @param data A pointer to the image data of the glyph.
		 */
		GlyphData(unsigned int unicode, const Vector2ui &offset, const Vector2i &size, const Vector2i &bearing, unsigned int advance,
				  unsigned char *data);

		/**
		 * Destroys the glyph data.
		 */
		~GlyphData();
	};
}

#endif //CEDAR_GLYPHDATA_HPP
