//
// Created by masy on 23.02.20.
//

#include "cedar/Texture2D.hpp"
#include "glad/glad.h"

using namespace cedar;

Texture2D::Texture2D(const int width, const int height, const int internalFormat, const unsigned int target)
		: Texture(internalFormat, target)
{
	switch (target)
	{
		case CEDAR_TEXTURE_2D:
		case CEDAR_TEXTURE_1D_ARRAY:
		case CEDAR_TEXTURE_RECTANGLE:
		case CEDAR_PROXY_TEXTURE_2D:
		case CEDAR_PROXY_TEXTURE_1D_ARRAY:
		case CEDAR_PROXY_TEXTURE_RECTANGLE:
			break;

		default:
			throw TextureCreationException("Could not create Texture2D. Unsupported target!");
	}

	this->m_width = width;
	this->m_height = height;
	this->m_samples = 1;
	this->m_reservedLevels = 0;
}

void Texture2D::reserve(const int levels)
{
	if (this->m_textureId != 0)
		throw TextureInitException("Could not reserve storage for Texture2D. Texture is already initialized!");

	glGenTextures(1, &this->m_textureId);

	if (this->m_textureId == 0)
		throw TextureInitException("Could not reserve storage for Texture2D. Could not generate texture ID!");

	glBindTexture(this->m_target, this->m_textureId);
	glTexStorage2D(this->m_target, levels, this->m_internalFormat, this->m_width, this->m_height);

	glTexParameteri(this->m_target, CEDAR_TEXTURE_WRAP_S, CEDAR_REPEAT);
	glTexParameteri(this->m_target, CEDAR_TEXTURE_WRAP_T, CEDAR_REPEAT);
	glTexParameteri(this->m_target, CEDAR_TEXTURE_MIN_FILTER, CEDAR_LINEAR);
	glTexParameteri(this->m_target, CEDAR_TEXTURE_MAG_FILTER, CEDAR_LINEAR);

	this->m_reservedLevels = levels;
	this->m_immutable = true;
}

void Texture2D::reserveMultisample(const int samples, bool fixedSampleLocations)
{
	if (this->m_textureId != 0)
		throw TextureInitException("Could not reserve storage for Texture2D. Texture is already initialized!");

	if (samples <= 1)
		throw TextureInitException("Could not reserve storage for multisample Texture2D. Sample count must be greater than 1!");

	glGenTextures(1, &this->m_textureId);

	if (this->m_textureId == 0)
		throw TextureInitException("Could not reserve storage for Texture2D. Could not generate texture ID!");

	glBindTexture(this->m_target, this->m_textureId);
	glTexStorage2DMultisample(this->m_target, samples, this->m_internalFormat, this->m_width, this->m_height, fixedSampleLocations);

	glTexParameteri(this->m_target, CEDAR_TEXTURE_WRAP_S, CEDAR_REPEAT);
	glTexParameteri(this->m_target, CEDAR_TEXTURE_WRAP_T, CEDAR_REPEAT);
	glTexParameteri(this->m_target, CEDAR_TEXTURE_MIN_FILTER, CEDAR_LINEAR);
	glTexParameteri(this->m_target, CEDAR_TEXTURE_MAG_FILTER, CEDAR_LINEAR);

	this->m_samples = samples;
	this->m_reservedLevels = 1;
	this->m_immutable = true;
}

void Texture2D::init(const unsigned int format, const unsigned int type, const void *data)
{
	if (this->m_textureId != 0)
		throw TextureInitException("Could not initialize Texture2D. Texture is already initialized!");

	glGenTextures(1, &this->m_textureId);

	if (this->m_textureId == 0)
		throw TextureInitException("Could not initialize Texture2D. Could not generate texture ID!");

	glBindTexture(this->m_target, this->m_textureId);

	glTexImage2D(this->m_target, 0, this->m_internalFormat, this->m_width, this->m_height, 0, format, type, data);

	glTexParameteri(this->m_target, CEDAR_TEXTURE_WRAP_S, CEDAR_REPEAT);
	glTexParameteri(this->m_target, CEDAR_TEXTURE_WRAP_T, CEDAR_REPEAT);
	glTexParameteri(this->m_target, CEDAR_TEXTURE_MIN_FILTER, CEDAR_LINEAR);
	glTexParameteri(this->m_target, CEDAR_TEXTURE_MAG_FILTER, CEDAR_LINEAR);
}

void Texture2D::initMultisample(const int samples, const bool fixedSampleLocations)
{
	if (this->m_textureId != 0)
		throw TextureInitException("Could not initialize multisample Texture2D. Texture is already initialized!");

	if (samples <= 1)
		throw TextureInitException("Could not initialize multisample Texture2D. Sample count must be greater than 1!");

	glGenTextures(1, &this->m_textureId);

	if (this->m_textureId == 0)
		throw TextureInitException("Could not initialize Texture2D. Could not generate texture ID!");

	glBindTexture(this->m_target, this->m_textureId);
	glTexImage2DMultisample(this->m_target, samples, this->m_internalFormat, this->m_width, this->m_height, fixedSampleLocations);

	glTexParameteri(this->m_target, CEDAR_TEXTURE_WRAP_S, CEDAR_REPEAT);
	glTexParameteri(this->m_target, CEDAR_TEXTURE_WRAP_T, CEDAR_REPEAT);
	glTexParameteri(this->m_target, CEDAR_TEXTURE_MIN_FILTER, CEDAR_LINEAR);
	glTexParameteri(this->m_target, CEDAR_TEXTURE_MAG_FILTER, CEDAR_LINEAR);
	this->m_reservedLevels = 1;
	this->m_samples = samples;
}

void Texture2D::upload(const unsigned int format, const unsigned int type, const void *data, const int level) {
	if (this->m_textureId == 0)
		throw TextureUploadException("Could not upload data to Texture2D. Texture is not initialized!");

	if (this->m_samples > 1)
		throw TextureUploadException("Could not upload data to Texture2D. Multisampled textures can only be used as render targets!");

	if (level < 0)
		throw TextureUploadException("Could not upload data to Texture2D. The level must be positive!");

	if (this->m_reservedLevels != 0 && level >= this->m_reservedLevels)
		throw TextureUploadException("Could not upload data to Texture2D. The given level is greater than the reserved number of levels!");

	glBindTexture(this->m_target, this->m_textureId);
	glTexImage2D(this->m_target, level, this->m_internalFormat, this->m_width, this->m_height, 0, format, type, data);
}

void Texture2D::upload(int offsetX, int offsetY, int width, int height, unsigned int format, unsigned int type, const void *data, int level) {
	if (this->m_textureId == 0)
		throw TextureUploadException("Could not upload data to Texture2D. Texture is not initialized!");

	if (this->m_samples > 1)
		throw TextureUploadException("Could not upload data to Texture2D. Multisampled textures can only be used as render targets!");

	if (width <= 0 || height <= 0)
		throw TextureUploadException("Could not upload data to Texture2D. The width and height must be greater than 0!");

	if (level < 0)
		throw TextureUploadException("Could not upload data to Texture2D. The level must be positive!");

	if (this->m_reservedLevels != 0 && level < this->m_reservedLevels)
		throw TextureUploadException("Could not upload data to Texture2D. The given level is greater than the reserved number of levels!");

	int alignment;
	switch (format)
	{

		case CEDAR_RG:
			alignment = 2;
			break;

		case CEDAR_RGB:
			alignment = 3;
			break;

		case CEDAR_RGBA:
			alignment = 4;
			break;

		default:
			alignment = 1;
			break;
	}
	glPixelStorei(GL_UNPACK_ALIGNMENT, alignment);
	glBindTexture(this->m_target, this->m_textureId);
	glTexSubImage2D(this->m_target, level, offsetX, offsetY, width, height, format, type, data);
	glPixelStorei(GL_UNPACK_ALIGNMENT, 4);
}

int Texture2D::getWidth() const
{
	return this->m_width;
}

int Texture2D::getHeight() const
{
	return this->m_height;
}

void Texture2D::setSize(int newWidth, int newHeight, bool keepData)
{
	if (this->m_textureId != 0)
	{
		if (this->m_immutable)
			throw TextureResizeException("Could not set size of texture. The texture is immutable!");

		unsigned int format = sizedToUnsized(this->m_internalFormat);
		if (keepData)
		{
			switch (this->m_target)
			{
				case CEDAR_TEXTURE_2D:
				case CEDAR_TEXTURE_1D_ARRAY:
				case CEDAR_TEXTURE_RECTANGLE:
					break;

				default:
					std::string message = "Could not resize Texture2D. The data of the texture could not be copied due to the target (";
					message.append(std::to_string(this->m_target));
					message.append(") not being supported!");
					throw TextureCreationException(message);
			}

			int bufferWidth = std::min(newWidth, this->m_width);
			int bufferHeight = std::min(newHeight, this->m_height);
			unsigned int bufferSize = bufferWidth * bufferHeight;
			int alignment;
			switch (format)
			{
				case CEDAR_RG:
					bufferSize *= 2;
					alignment = 2;
					break;

				case CEDAR_RGB:
					bufferSize *= 3;
					alignment = 3;
					break;

				case CEDAR_RGBA:
					bufferSize *= 4;
					alignment = 4;
					break;

				default:
					alignment = 1;
					break;
			}

			unsigned char *buffer = new unsigned char[bufferSize];

			glPixelStorei(GL_PACK_ALIGNMENT, 1);
			glGetTextureSubImage(this->m_textureId, 0, 0, 0, 0, bufferWidth, bufferHeight, 0, format, CEDAR_UNSIGNED_BYTE, bufferSize, buffer);
			glPixelStorei(GL_PACK_ALIGNMENT, 4);

			glBindTexture(this->m_target, this->m_textureId);

			glPixelStorei(GL_UNPACK_ALIGNMENT, alignment);
			if (newWidth > this->m_width || newHeight > this->m_height)
			{
				glTexImage2D(this->m_target, 0, this->m_internalFormat, newWidth, newHeight, 0, format, CEDAR_UNSIGNED_BYTE, nullptr);
				glTexSubImage2D(this->m_target, 0, 0, 0, bufferWidth, bufferHeight, format, CEDAR_UNSIGNED_BYTE, buffer);
			}
			else
			{
				glTexImage2D(this->m_target, 0, this->m_internalFormat, bufferWidth, bufferHeight, 0, format, CEDAR_UNSIGNED_BYTE, buffer);
			}
			glPixelStorei(GL_UNPACK_ALIGNMENT, 4);

			delete[] buffer;
		}
		else
		{
			glBindTexture(this->m_target, this->m_textureId);
			glTexImage2D(this->m_target, 0, this->m_internalFormat, newWidth, newHeight, 0, format, CEDAR_UNSIGNED_BYTE, nullptr);
		}
	}

	this->m_width = newWidth;
	this->m_height = newHeight;
}

bool Texture2D::isMultisample() const
{
	return this->m_samples > 1;
}

int Texture2D::getSamples() const
{
	return this->m_samples;
}

int Texture2D::getReservedLevels() const
{
	return this->m_reservedLevels;
}
