//
// Created by masy on 13.04.20.
//

#ifndef CEDAR_IMAGELOADER_HPP
#define CEDAR_IMAGELOADER_HPP

#include "Texture2D.hpp"

/**
 * Base namespace of the cedar engine.
 */
namespace cedar
{

	/**
	 * Exception which is thrown when a texture could not be loaded.
	 */
	class TextureLoadException : public XException
	{
	public:
		/**
		 * Creates a new texture load exception.
		 *
		 * @param message The message of the exception.
		 */
		explicit TextureLoadException(const std::string &message);
	};

	/**
	 * Class for loading images.
	 */
	class ImageLoader
	{
	private:
		/**
		 * Creates a new image loader.
		 */
		ImageLoader();

	public:
		/**
		 * Loads a texture from the given file.
		 *
		 * @param path The path to the texture file.
		 * @param forceComposition The number of forced color channels.
		 *                         <p>If 0, the number of color channels will be determined by the file.</p>
		 * @return A pointer to the loaded texture.
		 * @throws TextureLoadException when the texture could not be loaded.
		 */
		static Texture2D *loadTexture(const std::string &path, int forceComposition = 0);
	};
}

#endif //CEDAR_IMAGELOADER_HPP
