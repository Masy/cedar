//
// Created by masy on 23.02.20.
//

#include "cedar/Texture.h"
#include "glad/glad.h"

using namespace cedar;

TextureException::TextureException(const std::string &message) : XException(message)
{}

TextureCreationException::TextureCreationException(const std::string &message) : TextureException(message)
{}

TextureInitException::TextureInitException(const std::string &message) : TextureException(message)
{}

TextureResizeException::TextureResizeException(const std::string &message) : TextureException(message)
{}

TextureUploadException::TextureUploadException(const std::string &message) : TextureException(message)
{}

TextureParameterException::TextureParameterException(const std::string &message) : TextureException(message)
{}

unsigned int Texture::sizedToUnsized(const unsigned int sizedInternalFormat)
{
	switch (sizedInternalFormat)
	{
		case CEDAR_R8:
		case CEDAR_R8_SNORM:
		case CEDAR_R16:
		case CEDAR_R16_SNORM:
		case CEDAR_R8UI:
		case CEDAR_R8I:
		case CEDAR_R16UI:
		case CEDAR_R16I:
		case CEDAR_R16F:
		case CEDAR_R32UI:
		case CEDAR_R32I:
		case CEDAR_R32F:
			return CEDAR_RED;

		case CEDAR_RG8:
		case CEDAR_RG8_SNORM:
		case CEDAR_RG16:
		case CEDAR_RG16_SNORM:
		case CEDAR_RG8UI:
		case CEDAR_RG8I:
		case CEDAR_RG16UI:
		case CEDAR_RG16I:
		case CEDAR_RG16F:
		case CEDAR_RG32UI:
		case CEDAR_RG32I:
		case CEDAR_RG32F:
			return CEDAR_RG;

		case CEDAR_RGB8:
		case CEDAR_RGB8_SNORM:
		case CEDAR_RGB16:
		case CEDAR_RGB16_SNORM:
		case CEDAR_RGB8UI:
		case CEDAR_RGB8I:
		case CEDAR_RGB16UI:
		case CEDAR_RGB16I:
		case CEDAR_RGB16F:
		case CEDAR_RGB32UI:
		case CEDAR_RGB32I:
		case CEDAR_RGB32F:
			return CEDAR_RGB;

		case CEDAR_RGBA8:
		case CEDAR_RGBA8_SNORM:
		case CEDAR_RGBA16:
		case CEDAR_RGBA16_SNORM:
		case CEDAR_RGBA8UI:
		case CEDAR_RGBA8I:
		case CEDAR_RGBA16UI:
		case CEDAR_RGBA16I:
		case CEDAR_RGBA16F:
		case CEDAR_RGBA32UI:
		case CEDAR_RGBA32I:
		case CEDAR_RGBA32F:
			return CEDAR_RGBA;

		case CEDAR_DEPTH_COMPONENT16:
		case CEDAR_DEPTH_COMPONENT24:
		case CEDAR_DEPTH_COMPONENT32:
		case CEDAR_DEPTH_COMPONENT32F:
		case CEDAR_DEPTH24_STENCIL8:
		case CEDAR_DEPTH32F_STENCIL8:
			return CEDAR_DEPTH_COMPONENT;

		case CEDAR_STENCIL_INDEX1:
		case CEDAR_STENCIL_INDEX4:
		case CEDAR_STENCIL_INDEX8:
		case CEDAR_STENCIL_INDEX16:
			return CEDAR_STENCIL_INDEX;

		default:
			return CEDAR_RGBA;
	}
}

Texture::Texture(const int internalFormat, const unsigned int target)
{
	this->m_textureId = 0;
	this->m_target = target;
	this->m_internalFormat = internalFormat;
	this->m_immutable = false;

	switch (internalFormat)
	{
		case CEDAR_DEPTH_COMPONENT:
		case CEDAR_DEPTH_COMPONENT16:
		case CEDAR_DEPTH_COMPONENT24:
		case CEDAR_DEPTH_COMPONENT32:
		case CEDAR_DEPTH_COMPONENT32F:
			this->m_depthTexture = true;
			this->m_stencilTexture = false;
			break;

		case CEDAR_DEPTH_STENCIL:
		case CEDAR_DEPTH24_STENCIL8:
		case CEDAR_DEPTH32F_STENCIL8:
			this->m_depthTexture = true;
			this->m_stencilTexture = true;
			break;

		case CEDAR_STENCIL_INDEX:
		case CEDAR_STENCIL_INDEX1:
		case CEDAR_STENCIL_INDEX4:
		case CEDAR_STENCIL_INDEX8:
		case CEDAR_STENCIL_INDEX16:
			this->m_depthTexture = false;
			this->m_stencilTexture = true;
			break;

		default:
			this->m_depthTexture = false;
			this->m_stencilTexture = false;
	}
}

Texture::~Texture()
{
	glDeleteTextures(1, &this->m_textureId);
}

unsigned int Texture::getId() const
{
	return this->m_textureId;
}

unsigned int Texture::getTarget() const
{
	return this->m_target;
}

int Texture::getInternalFormat() const
{
	return this->m_internalFormat;
}

bool Texture::isDepthTexture() const
{
	return this->m_depthTexture;
}

bool Texture::isStencilTexture() const
{
	return this->m_stencilTexture;
}

bool Texture::isDepthAndStencilTexture() const
{
	return this->m_depthTexture && this->m_stencilTexture;
}

bool Texture::isImmutable() const
{
	return this->m_immutable;
}

void Texture::setParameteri(const unsigned int parameter, const int value) const
{
	if (this->m_textureId == 0)
		throw TextureParameterException("Could not set parameter of texture. The texture is not initialized yet!");

	glTextureParameteri(this->m_textureId, parameter, value);
}

void Texture::setParameterf(const unsigned int parameter, const float value) const
{
	if (this->m_textureId == 0)
		throw TextureParameterException("Could not set parameter of texture. The texture is not initialized yet!");

	glTextureParameterf(this->m_textureId, parameter, value);
}

void Texture::setParameteriv(const unsigned int parameter, const int *values) const
{
	if (this->m_textureId == 0)
		throw TextureParameterException("Could not set parameter of texture. The texture is not initialized yet!");

	glTextureParameteriv(this->m_textureId, parameter, values);
}

void Texture::setParameterfv(const unsigned int parameter, const float *values) const
{
	if (this->m_textureId == 0)
		throw TextureParameterException("Could not set parameter of texture. The texture is not initialized yet!");

	glTextureParameterfv(this->m_textureId, parameter, values);
}

void Texture::setParameterIiv(const unsigned int parameter, const int *values) const
{
	if (this->m_textureId == 0)
		throw TextureParameterException("Could not set parameter of texture. The texture is not initialized yet!");

	glTextureParameterIiv(this->m_textureId, parameter, values);
}

void Texture::setParameterIuiv(const unsigned int parameter, const unsigned int *values) const
{
	if (this->m_textureId == 0)
		throw TextureParameterException("Could not set parameter of texture. The texture is not initialized yet!");

	glTextureParameterIuiv(this->m_textureId, parameter, values);
}

bool Texture::operator==(const Texture &other) const
{
	return this->m_textureId == other.m_textureId;
}
