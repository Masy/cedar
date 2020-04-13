//
// Created by masy on 13.04.20.
//

#ifndef CEDAR_TEXTUREREGISTRY_HPP
#define CEDAR_TEXTUREREGISTRY_HPP

#include <map>
#include <memory>
#include "Texture2D.hpp"
#include "XException.hpp"

/**
 * Base namespace of the cedar engine.
 */
namespace cedar
{

	/**
	 * Exception which is thrown when a texture could not be registered.
	 */
	class TextureRegisterException : public XException
	{
	public:
		/**
		 * Creates a new texture register exception.
		 *
		 * @param message The message of the exception.
		 */
		explicit TextureRegisterException(const std::string &message);
	};

	/**
	 * Class for creating and handling textures.
	 */
	class TextureRegistry
	{
	private:
		/**
		 * The map of all loaded textures.
		 */
		static std::map<std::string, std::shared_ptr<Texture>> m_loadedTextures;

		/**
		 * Creates a new texture registry.
		 */
		TextureRegistry();

	public:
		/**
		 * Registers the given texture under the given name.
		 *
		 * @param name The name of the texture.
		 * @param texture A pointer to the texture that will be registered.
		 * @return A shared pointer to the registered texture.
		 *
		 * @throws TextureRegisterException when a texture with the same name is already registered or the name is invalid.
		 */
		static std::shared_ptr<Texture> registerTexture(const std::string &name, Texture *texture);

		/**
		 * Loads a texture and registers it under the given name.
		 *
		 * @param name The name of the texture.
		 * @param path The path to the texture file that will be loaded and registered.
		 * @return A shared pointer to the registered texture.
		 *
		 * @throws TextureRegisterException when a texture with the same name is already registered or the name is invalid.
		 * @throws TextureLoadException if the texture file could not be loaded.
		 *
		 * @see ImageLoader#loadTexture(const std::string &, int)
		 */
		static std::shared_ptr<Texture> loadTexture(const std::string &name, const std::string &path);

		/**
		 * Gets the texture with the given name.
		 *
		 * @param name The name of the texture.
		 * @return A shared pointer to the texture with the given name or <code>nullptr</code> if no texture is registered under that name.
		 */
		static std::shared_ptr<Texture> getTexture(const std::string &name);

		/**
		 * Deletes the texture with the given name from the registry.
		 *
		 * @param name The name of the texture that will be deleted from the registry.
		 */
		static void cleanup(const std::string &name);

		/**
		 * Clears the registry.
		 */
		static void cleanup();
	};
}

#endif //CEDAR_TEXTUREREGISTRY_HPP
