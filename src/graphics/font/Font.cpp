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

Font::Font(const std::string &name, unsigned int size, unsigned int renderingMode)
{
	this->m_name = name;
	this->m_size = size;
	this->m_renderingMode = renderingMode;
	this->m_atlasHeight = 128;
	this->m_glyphAtlas = new Texture2D(CEDAR_FONT_ATLAS_WIDTH, this->m_atlasHeight, CEDAR_R8, CEDAR_TEXTURE_2D);
	this->m_glyphAtlas->init(CEDAR_RED, CEDAR_UNSIGNED_BYTE, nullptr);
	// Since the glyph image data basically only represents the alpha value we need to adjust the way the texture is swizzled
	// The glyph atlas will therefore be set up to return it's RED component as alpha value, and RGB will return 1.0 (= 255).
	int swizzle[] = {CEDAR_ONE, CEDAR_ONE, CEDAR_ONE, CEDAR_RED};
	this->m_glyphAtlas->setParameteriv(CEDAR_TEXTURE_SWIZZLE_RGBA, swizzle);

	this->m_currentOffsetX = 0;
	this->m_currentOffsetY = 0;
	this->m_tallestCharacterInRow = 0;
	this->m_glyphs = std::map<unsigned int, Glyph *>();
	this->m_glyphData = nullptr;

}

Font::~Font()
= default;

const Glyph *Font::createGlyph(const unsigned int unicode, const unsigned int glyphWidth, const unsigned int glyphHeight,
							   const int bearingX, const int bearingY, const unsigned int advance, const unsigned char *imageData)
{
	// Check if the glyph fits on the glyph atlas vertically
	if (this->m_currentOffsetY + glyphHeight >= this->m_atlasHeight)
		this->resize();

	// Check if the glyph fits on the texture horizontally
	if (this->m_currentOffsetX + glyphWidth >= CEDAR_FONT_ATLAS_WIDTH)
	{
		this->m_currentOffsetY += this->m_tallestCharacterInRow;

		// Since we advanced the y offset we need to check for space again
		if (this->m_currentOffsetY + glyphHeight >= this->m_atlasHeight)
			this->resize();

		// Reset x offset to 0 because of new row
		this->m_currentOffsetX = 0;
		this->m_tallestCharacterInRow = glyphHeight;
	}
	else if (glyphHeight > this->m_tallestCharacterInRow)
	{
		this->m_tallestCharacterInRow = glyphHeight;
	}

	float pixelWidth = 1.0f / CEDAR_FONT_ATLAS_WIDTH;
	float pixelHeight = 1.0f / static_cast<float>(this->m_atlasHeight);
	Glyph *glyph = new Glyph(Vector2i(static_cast<int>(glyphWidth), static_cast<int>(glyphHeight)),
							 Vector2i(bearingX, bearingY),
							 advance,
							 Vector4f(pixelWidth * static_cast<float>(this->m_currentOffsetX),
									  pixelHeight * static_cast<float>(this->m_currentOffsetY),
									  pixelWidth * static_cast<float>(this->m_currentOffsetX + static_cast<int>(glyphWidth)),
									  pixelHeight * static_cast<float>(this->m_currentOffsetY + static_cast<int>(glyphHeight))
									 )
							);

	this->m_glyphAtlas->upload(this->m_currentOffsetX, this->m_currentOffsetY,
							   static_cast<int>(glyphWidth), static_cast<int>(glyphHeight),
							   CEDAR_RED, CEDAR_UNSIGNED_BYTE, imageData);

	this->m_currentOffsetX += glyphWidth;

	this->m_glyphs.insert(std::make_pair(unicode, glyph));
	return glyph;
}

void Font::resize()
{
	this->m_glyphAtlas->setSize(CEDAR_FONT_ATLAS_WIDTH, this->m_atlasHeight * 2);
	for (auto pair : this->m_glyphs)
	{
		pair.second->m_uvs.y *= 0.5f;
		pair.second->m_uvs.w *= 0.5f;
	}
}

void Font::stitchAtlas(unsigned int firstIndex, unsigned int lastIndex, const cedar::Vector4ui &region)
{
	float pixelWidth = 1.0f / CEDAR_FONT_ATLAS_WIDTH;
	float pixelHeight = 1.0f / static_cast<float>(this->m_atlasHeight);

	// Calculate region length
	unsigned int regionDataLength = region.z * region.w;
	// Allocate memory with calloc to avoid artifacts near the glyphs since we only write to the region where there are glyph images
	unsigned char *regionData = reinterpret_cast<unsigned char *>(calloc(regionDataLength, 1));

	// Stitch region together
	for (unsigned int n = firstIndex; n < lastIndex; n++)
	{
		GlyphData *glyphData = &this->m_glyphData[n];
		Glyph *glyph = new Glyph(glyphData->m_size,
								 glyphData->m_bearing,
								 glyphData->m_advance,
								 Vector4f(pixelWidth * static_cast<float>(glyphData->m_offset.x),
										  pixelHeight * static_cast<float>(glyphData->m_offset.y),
										  pixelWidth * static_cast<float>(glyphData->m_offset.x + glyphData->m_size.x),
										  pixelHeight * static_cast<float>(glyphData->m_offset.y + glyphData->m_size.y)
										 )
								);

		// Copy glyph image into region data
		for (int x = 0; x < glyphData->m_size.x; x++)
		{
			for (int y = 0; y < glyphData->m_size.y; y++)
			{
				unsigned int regionIndex = region.z * (glyphData->m_offset.y - region.y + y) + x + glyphData->m_offset.x;
				unsigned int dataIndex = glyphData->m_size.x * y + x;
				regionData[regionIndex] = glyphData->m_data[dataIndex];
			}
		}

		this->m_glyphs.insert(std::make_pair(glyphData->m_unicode, glyph));
	}

	// Upload region to texture
	this->m_glyphAtlas->upload(static_cast<int>(region.x), static_cast<int>(region.y),
							   static_cast<int>(region.z), static_cast<int>(region.w),
							   CEDAR_RED, CEDAR_UNSIGNED_BYTE, regionData);

	free(regionData);
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
