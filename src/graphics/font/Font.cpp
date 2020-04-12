//
// Created by masy on 03.03.20.
//

#include <cedar/Cedar.h>
#include "cedar/Font.h"

#define STB_IMAGE_WRITE_STATIC
#define STB_IMAGE_WRITE_IMPLEMENTATION

using namespace cedar;

FontException::FontException(const std::string &message) : XException(message)
{}

FontCreationException::FontCreationException(const std::string &message) : FontException(message)
{}

FontLoadException::FontLoadException(const std::string &message) : FontException(message)
{}

Font::Font(const std::string &name, unsigned int size, int internalFormat, unsigned int renderingMode)
{
	this->m_name = name;
	this->m_size = size;
	this->m_renderingMode = renderingMode;
	this->m_atlasHeight = 128;
	this->m_internalFormat = internalFormat;

	this->m_glyphAtlas = new Texture2D(CEDAR_FONT_ATLAS_WIDTH, this->m_atlasHeight, internalFormat, CEDAR_TEXTURE_2D);
	this->m_glyphAtlas->init(Texture::sizedToUnsized(internalFormat), CEDAR_UNSIGNED_BYTE, nullptr);

	this->m_currentOffsetX = 0;
	this->m_currentOffsetY = 0;
	this->m_tallestCharacterInRow = 0;
	this->m_glyphs = std::map<unsigned int, Glyph *>();
	this->m_glyphData = nullptr;
}

Font::~Font()
= default;

void Font::resize()
{
	this->m_glyphAtlas->setSize(CEDAR_FONT_ATLAS_WIDTH, this->m_atlasHeight * 2);
	for (auto pair : this->m_glyphs)
	{
		pair.second->m_uvs.y *= 0.5f;
		pair.second->m_uvs.w *= 0.5f;
	}
}

unsigned int Font::getSize() const
{
	return this->m_size;
}

unsigned int Font::getRenderingMode() const
{
	return this->m_renderingMode;
}

const Glyph *Font::getGlyph(const unsigned int unicode)
{
	auto it = this->m_glyphs.find(unicode);
	if (it != this->m_glyphs.end())
	{
		return it->second;
	}
	else
	{
		return this->loadGlyph(unicode);
	}
}

const Texture2D *Font::getGlyphAtlas() const
{
	return this->m_glyphAtlas;
}
