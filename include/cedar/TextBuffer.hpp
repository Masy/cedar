//
// Created by masy on 05.03.20.
//

#ifndef CEDAR_TEXTBUFFER_HPP
#define CEDAR_TEXTBUFFER_HPP

#include "cedar/Quad.hpp"

/**
 * Base namespace of the cedar engine.
 */
namespace cedar
{
	/**
	 * Class storing quads of a text model.
	 *
	 * <p>Since when rendering a string the method has to loop over all codepoints and find the
	 * corresponding glyph models, this is a fast alternative for static strings that need to
	 * be rendered a lot without changing the text itself.</p>
	 */
	class TextBuffer
	{
	private:
		/**
		 * The texture id of the glyph atlas this text buffer uses.
		 */
		unsigned int m_glyphAtlasId;
		/**
		 * The number of glyphs stored in this text buffer.
		 */
		unsigned int m_glyphCount;
		/**
		 * A pointer to the quads of the glyphs.
		 */
		Quad *m_quads;
		/**
		 * The size of the text in pixel.
		 */
		Vector2f m_size;

	public:
		/**
		 * Creates a new text buffer.
		 *
		 * @param glyphAtlasId The texture id of the glyph atlas this buffer uses.
		 * @param glyphCount The number of glyphs stored in this buffer.
		 * @param quads A pointer to the array of quads stored in this buffer.
		 * @param size The size of the text in this buffer in pixel.
		 */
		TextBuffer(unsigned int glyphAtlasId, unsigned int glyphCount, Quad *quads, const Vector2f &size);

		/**
		 * Destroys the text buffer.
		 */
		~TextBuffer();

		/**
		 * Gets the texture id of the glyph atlas of this buffer.
		 *
		 * @return The texture id of the glyph atlas of this buffer.
		 */
		[[nodiscard]] unsigned int getGlyphAtlas() const;

		/**
		 * Gets the number of glyphs stored in this buffer.
		 *
		 * @return The number of glyphs stored in this buffer.
		 */
		[[nodiscard]] unsigned int getGlyphCount() const;

		/**
		 * Gets the quads of this buffer.
		 *
		 * @return A pointer to the quads of this buffer.
		 */
		[[nodiscard]] const Quad *getQuads() const;

		/**
		 * Gets the size of the text in this buffer.
		 *
		 * @return The size of the text in pixel.
		 */
		[[nodiscard]] Vector2f getSize() const;
	};
}

#endif //CEDAR_TEXTBUFFER_HPP
