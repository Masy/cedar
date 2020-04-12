//
// Created by masy on 11.04.20.
//

#ifndef CEDAR_PTFFONT_HPP
#define CEDAR_PTFFONT_HPP

#include "cedar/Font.h"
#include <fstream>

/**
 * Base namespace of the cedar engine.
 */
namespace cedar
{

	/**
	 * Class representing a PTF (Pixel Type Format) Font.
	 */
	class PTFFont : public Font
	{
	private:
		/**
		 * The scale of the ptf font.
		 */
		unsigned int m_scale;
		/**
		 * The number of colors in the palette.
		 */
		unsigned int m_paletteSize;
		/**
		 * The array of colors the ptf font uses.
		 */
		unsigned int *m_palette;
		/**
		 * The pointer to the dictionary in the ptf font file.
		 */
		unsigned int m_dictionaryPointer;
		/**
		 * The dictionary of the ptf font.
		 */
		std::map<unsigned int, unsigned int> m_dictionary;
		/**
		 * The path to the font file of ptf font.
		 */
		std::string m_fontPath;
		/**
		 * The input file stream of the ptf font.
		 */
		std::ifstream m_fontFile;

		/**
		 * Loads the palette of the ptf font.
		 */
		void loadPalette();

		/**
		 * Loads the dictionary of the ptf font.
		 */
		void loadDictionary();

		/**
		 * Loads the glyph image of the given unicode code point if it does not exist and generates the glyph.
		 *
		 * @param unicode The unicode character of which the glyph will be generated.
		 * @return A constant pointer to the generated glyph.
		 */
		const Glyph *loadGlyph(unsigned int unicode) override;

		/**
		 * Creates a glyph from the glyph data {@link #m_glyphData} is currently pointing to and copies it to the atlas.
		 *
		 * @return A constant pointer to the created glyph.
		 */
		const Glyph *createGlyph() override;

		/**
		 * Stitches the given glyphs from {@link #m_glyphData} into a single image and uploads it to the glyph atlas.
		 *
		 * @param firstIndex The first index of the glyphs to stitch.
		 * @param lastIndex The last (exclusive) index of the glyphs to stitch.
		 * @param region The coordinates and size of the region that is being uploaded to the glyph atlas.
		 */
		void stitchAtlas(unsigned int firstIndex, unsigned int lastIndex, const Vector4ui &region) override;

	public:
		/**
		 * Creates a new PTF font.
		 *
		 * @param name The name of the font.
		 * @param path The path to the font file.
		 * @param scale The scale by which the size of the PTF font will be scaled.
		 */
		PTFFont(const std::string &name, const std::string &path, unsigned int scale);

		/**
		 * Deletes the font.
		 */
		~PTFFont() override;

		/**
		 * Generates the glyphs for the characters in the given range.
		 *
		 * @param firstCharacter The unicode of the first character that will be generated.
		 * @param lastCharacter The unicode of the last character that will be generated.
		 */
		void generateGlyphs(unsigned int firstCharacter, unsigned int lastCharacter);
	};

}

#endif //CEDAR_PTFFONT_HPP
