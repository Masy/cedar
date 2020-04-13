//
// Created by masy on 03.03.20.
//

#ifndef CEDAR_FONTREGISTRY_H
#define CEDAR_FONTREGISTRY_H

#include "cedar/Font.h"

/**
 * Base namespace of the cedar engine.
 */
namespace cedar
{
	/**
	 * Class for creating and handling fonts.
	 */
	class FontRegistry
	{
	public:
		/**
		 * Loads the given font.
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
		 *             <p>If the font is a ptf font the size will be the scale by which the ptf font size will be multiplied.</p>
		 * @param firstCharacter The unicode of the first character to pre-generate.
		 * @param lastCharacter The unicode of the last character to pre-generate.
		 * @param renderingMode The rendering mode of the font.
		 * @return A pointer to the loaded font.
		 *
		 * @see Font
		 * @throws FontCreationException if the font could not be loaded.
		 */
		static Font *loadFont(const std::string &name, const std::string &path, unsigned int size, unsigned int firstCharacter = 0, unsigned int lastCharacter = 255, unsigned int renderingMode = CEDAR_RENDERING_SMOOTH);

		/**
		 * Gets the loaded font with the given name.
		 *
		 * @param name The name of the font.
		 * @return A pointer to the font or <code>nullptr</code> if no font with that name is loaded.
		 */
		static Font *getFont(const std::string &name);

		/**
		 * Deletes all fonts.
		 */
		static void cleanup();

		/**
		 * Deletes the font with the given name.
		 *
		 * @param name The name of the font that will be deleted.
		 */
		static void cleanup(const std::string &name);
	};
}

#endif //CEDAR_FONTREGISTRY_H
