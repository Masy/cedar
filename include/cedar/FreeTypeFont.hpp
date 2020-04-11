//
// Created by masy on 11.04.20.
//

#ifndef CEDAR_FREETYPEFONT_HPP
#define CEDAR_FREETYPEFONT_HPP

#include "Font.h"
#include "freetype2/ft2build.h"
#include FT_FREETYPE_H

namespace cedar
{

	/**
	 * Exception which is thrown when FreeType could not be initialized.
	 */
	class FreeTypeInitException : public FontException
	{
	public:
		/**
		 * Creates a new FreeType init exception.
		 *
		 * @param message The message of the exception.
		 */
		explicit FreeTypeInitException(const std::string &message);
	};

	class FreeTypeFont : public Font
	{
	private:
		/**
		 * Gets the singleton instance of the freetype library.
		 *
		 * @return The singleton instance of the freetype libary.
		 *
		 * @throws FreetypeInitException if freetype could not be initialized.
		 */
		static FT_Library &getFontLibrary();

		/**
		 * The FreeType face of the font.
		 */
		FT_Face m_face;

		/**
		 * Generates the glyph with the given unicode if it does not exist.
		 *
		 * @param unicode The unicode character of which the glyph will be generated.
		 * @return A constant pointer to the generated glyph.
		 */
		const Glyph *loadGlyph(unsigned int unicode) override;


	public:
		/**
		 * Creates a new FreeType font.
		 *
		 * <p>The <code>rendering mode</code> of the font should be one of the following:
		 * <ul>
		 *   <li>{@link CEDAR_RENDERING_SHARP}<li>
		 *   <li>{@link CEDAR_RENDERING_SMOOTH}</li>
		 * </ul></p>
		 *
		 * @param name The name of the font.
		 * @param path The path to the font file.
		 * @param size The size of the font in pixel.
		 * @param renderingMode The rendering mode of the font.
		 */
		FreeTypeFont(const std::string &name, const std::string &path, unsigned int size, unsigned int renderingMode = CEDAR_RENDERING_SMOOTH);

		/**
		 * Deletes the font.
		 */
		~FreeTypeFont() override;


		/**
		 * Generates the glyphs for the characters in the given range.
		 *
		 * @param firstCharacter The unicode of the first character that will be generated.
		 * @param lastCharacter The unicode of the last character that will be generated.
		 */
		void generateGlyphs(unsigned int firstCharacter, unsigned int lastCharacter) override;
	};

}

#endif //CEDAR_FREETYPEFONT_HPP
