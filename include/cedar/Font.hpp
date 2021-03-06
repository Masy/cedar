//
// Created by masy on 03.03.20.
//

#ifndef CEDAR_FONT_HPP
#define CEDAR_FONT_HPP

#include <map>
#include "freetype2/ft2build.h"
#include FT_FREETYPE_H

#include "cedar/Texture2D.hpp"
#include "cedar/Glyph.hpp"
#include "cedar/GlyphData.hpp"
#include "cedar/Vector4ui.hpp"
#include "cedar/TextBuffer.hpp"
#include "cedar/GUIConstants.hpp"

#define CEDAR_FONT_ATLAS_WIDTH 4096

#define UTF8_ACCEPT 0
#define UTF8_REJECT 1

/**
 * Base namespace of the cedar engine.
 */
namespace cedar
{
	/**
	 * Base class for all font related exception.
	 */
	class FontException : public XException
	{
	public:
		/**
		 * Creates a new font exception.
		 *
		 * @param message The message of the exception.
		 */
		explicit FontException(const std::string &message);
	};

	/**
	 * Exception which is thrown when a font could not be created.
	 */
	class FontCreationException : public FontException
	{
	public:
		/**
		 * Creates a new font creation exception.
		 *
		 * @param message The message of the exception.
		 */
		explicit FontCreationException(const std::string &message);
	};

	/**
	 * Exception which is thrown when the file of a font could not be opened.
	 */
	class FontLoadException : public FontException
	{
	public:
		/**
		 * Creates a new font load exception.
		 *
		 * @param message The message of the exception.
		 */
		explicit FontLoadException(const std::string &message);
	};

	/**
	 * Class representing a font with a fixed size.
	 */
	class Font
	{
	protected:
		/**
		 * The name of the font.
		 */
		std::string m_name;
		/**
		 * The size of the font in pixel.
		 */
		unsigned int m_size;
		/**
		 * The rendering mode of the font.
		 *
		 * <p>Has to be one of the following values:
		 * <ul>
		 *   <li>{@link CEDAR_RENDERING_SHARP}<li>
		 *   <li>{@link CEDAR_RENDERING_SMOOTH}</li>
		 * </ul></p>
		 */
		unsigned int m_renderingMode;
		int m_internalFormat;
		/**
		 * A pointer to the glyph atlas of the font.
		 */
		Texture2D *m_glyphAtlas;

		/**
		 * The current offset in the glyph atlas on the x axis.
		 */
		unsigned int m_currentOffsetX;
		/**
		 * The current offset in the glyph atlas on the y axis.
		 */
		unsigned int m_currentOffsetY;
		/**
		 * The current height of the glyph atlas.
		 */
		int m_atlasHeight;
		/**
		 * The height of the tallest character in the current row of glyphs.
		 *
		 * <p>This is used to calculate the new y offset if the current row is full.</p>
		 */
		unsigned int m_tallestCharacterInRow;
		/**
		 * Map for storing glyphs for unicode characters.
		 */
		std::map<unsigned int, Glyph *> m_glyphs;
		/**
		 * Pointer to temporary storage that is used by {@link generate
		 */
		GlyphData *m_glyphData;

		/**
		 * Loads the glyph image of the given unicode code point if it does not exist and generates the glyph.
		 *
		 * @param unicode The unicode character of which the glyph will be generated.
		 * @return A constant pointer to the generated glyph.
		 */
		virtual const Glyph *loadGlyph(unsigned int unicode) = 0;

		/**
		 * Creates a glyph from the glyph data {@link #m_glyphData} is currently pointing to and copies it to the atlas.
		 *
		 * @return A constant pointer to the created glyph.
		 */
		virtual const Glyph *createGlyph() = 0;

		/**
		 * Resizes the glyph atlas.
		 *
		 * <p>This doubles the height of the glyph atlas and recalculates the uv coordinates of every
		 * currently loaded glyph.</p>
		 */
		void resize();

		/**
		 * Stitches the given glyphs from {@link #m_glyphData} into a single image and uploads it to the glyph atlas.
		 *
		 * @param firstIndex The first index of the glyphs to stitch.
		 * @param lastIndex The last (exclusive) index of the glyphs to stitch.
		 * @param region The coordinates and size of the region that is being uploaded to the glyph atlas.
		 */
		virtual void stitchAtlas(unsigned int firstIndex, unsigned int lastIndex, const Vector4ui &region) = 0;

	public:

		/**
		 *  Codepoint table used to calculate the correct UTF-8 codepoint.
		 */
		static constexpr uint8_t utf8d[] = {
				0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, // 00..1f
				0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, // 20..3f
				0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, // 40..5f
				0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, // 60..7f
				1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, // 80..9f
				7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, // a0..bf
				8, 8, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, // c0..df
				0xa, 0x3, 0x3, 0x3, 0x3, 0x3, 0x3, 0x3, 0x3, 0x3, 0x3, 0x3, 0x3, 0x4, 0x3, 0x3, // e0..ef
				0xb, 0x6, 0x6, 0x6, 0x5, 0x8, 0x8, 0x8, 0x8, 0x8, 0x8, 0x8, 0x8, 0x8, 0x8, 0x8, // f0..ff
				0x0, 0x1, 0x2, 0x3, 0x5, 0x8, 0x7, 0x1, 0x1, 0x1, 0x4, 0x6, 0x1, 0x1, 0x1, 0x1, // s0..s0
				1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 0, 1, 0, 1, 1, 1, 1, 1, 1, // s1..s2
				1, 2, 1, 1, 1, 1, 1, 2, 1, 2, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 2, 1, 1, 1, 1, 1, 1, 1, 1, // s3..s4
				1, 2, 1, 1, 1, 1, 1, 1, 1, 2, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 3, 1, 3, 1, 1, 1, 1, 1, 1, // s5..s6
				1, 3, 1, 1, 1, 1, 1, 3, 1, 3, 1, 1, 1, 1, 1, 1, 1, 3, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, // s7..s8
		};


		/**
		 * Decodes the given UTF-8 codepoint.
		 *
		 * Copyright (c) 2008-2009 Bjoern Hoehrmann <bjoern@hoehrmann.de>
		 * See http://bjoern.hoehrmann.de/utf-8/decoder/dfa/ for details.
		 *
		 * @param state A pointer to the state int.
		 * @param codepoint A pointer to where the decoded codepoint will be stored.
		 * @param byte The UTF-8 encoded character.
		 * @return The state of the decoder.
		 */
		static uint32_t inline
		decode(uint32_t *state, uint32_t *codepoint, uint32_t byte)
		{
			uint32_t type = utf8d[byte];

			*codepoint = (*state != UTF8_ACCEPT) ?
						 (byte & 0x3Fu) | (*codepoint << 6u) :
						 (0xFFu >> type) & (byte);

			*state = utf8d[256 + *state * 16 + type];
			return *state;
		}

		/**
		 * Creates a new font.
		 *
		 * <p>The <code>rendering mode</code> of the font should be one of the following:
		 * <ul>
		 *   <li>{@link CEDAR_RENDERING_SHARP}<li>
		 *   <li>{@link CEDAR_RENDERING_SMOOTH}</li>
		 * </ul></p>
		 *
		 * @param name The name of the font.
		 * @param size The size of the font in pixel.
		 * @param renderingMode The rendering mode of the font.
		 */
		Font(const std::string &name, unsigned int size, int internalFormat, unsigned int renderingMode = CEDAR_RENDERING_SMOOTH);

		/**
		 * Deletes the font.
		 */
		virtual ~Font();

		/**
		 * Generates the glyphs for the characters in the given range.
		 *
		 * @param firstCharacter The unicode of the first character that will be generated.
		 * @param lastCharacter The unicode of the last character that will be generated.
		 */
		virtual void generateGlyphs(unsigned int firstCharacter, unsigned int lastCharacter) = 0;

		/**
		 * Gets the size of the font in pixel.
		 *
		 * @return The size of the font in pixel.
		 */
		[[nodiscard]] unsigned int getSize() const;

		/**
		 * Gets the rendering mode of the font.
		 *
		 * @return The rendering mode of the font.
		 */
		[[nodiscard]] unsigned int getRenderingMode() const;

		/**
		 * Gets the glyph of the given unicode character.
		 *
		 * <p>If no glyph exists for the unicode character a new one will be generated.</p>
		 *
		 * @param unicode The unicode character.
		 * @return The glyph of the given unicode character.
		 */
		[[nodiscard]] const Glyph *getGlyph(unsigned int unicode);

		/**
		 * Gets the glyph atlas of the font.
		 *
		 * @return A constant pointer to the glyph atlas of the font.
		 */
		[[nodiscard]] const Texture2D *getGlyphAtlas() const;
	};
}

#endif //CEDAR_FONT_HPP
