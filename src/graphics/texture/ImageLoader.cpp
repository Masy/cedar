//
// Created by masy on 13.04.20.
//

#include "cedar/ImageLoader.hpp"

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

using namespace cedar;

TextureLoadException::TextureLoadException(const std::string &message) : XException(message)
{}

ImageLoader::ImageLoader()
= default;

Texture2D *ImageLoader::loadTexture(const std::string &path, const int forceComposition) {
	int width;
	int height;
	int composition;

	unsigned char * imageData = stbi_load(path.c_str(), &width, &height, &composition, forceComposition);

	if (!imageData)
		throw TextureLoadException("Could not load texture from file " + path + ". Does the file even exist?");

	int internalFormat;
	switch (composition)
	{
		case 1:
			internalFormat = CEDAR_R8;
			break;

		case 2:
			internalFormat = CEDAR_RG8;
			break;

		case 3:
			internalFormat = CEDAR_RGB8;
			break;

		case 4:
			internalFormat = CEDAR_RGBA8;
			break;

		default:
			stbi_image_free(imageData);
			throw TextureLoadException("Could not load texture from file " + path + ". Invalid composition! " + std::to_string(composition));
	}

	Texture2D *texture = new Texture2D(width, height, internalFormat, CEDAR_TEXTURE_2D);
	texture->init(Texture::sizedToUnsized(internalFormat), CEDAR_UNSIGNED_BYTE, imageData);
	stbi_image_free(imageData);
	return texture;
}
