//
// Created by masy on 03.03.20.
//

#include <cedar/Cedar.h>
#include "cedar/GlyphData.h"
#include "cedar/Vector4ui.h"
#include "cedar/Font.h"

#define STB_IMAGE_WRITE_STATIC
#define STB_IMAGE_WRITE_IMPLEMENTATION

#include "stb_image_write.h"

using namespace cedar;

FontException::FontException(const std::string &message) : XException(message)
{}

FreetypeInitException::FreetypeInitException(const std::string &message) : FontException(message)
{}

FontCreationException::FontCreationException(const std::string &message) : FontException(message)
{}

FT_Library &Font::getFontLibrary()
{
	static FT_Library library;
	static bool initialized = false;
	if (!initialized)
	{
		if (FT_Init_FreeType(&library))
			throw FreetypeInitException("Could not initialize FreeType!");

		initialized = true;
	}

	return library;
}

Font::Font(const std::string &name, const std::string &path, unsigned int size, unsigned int firstCharacter, unsigned int lastCharacter,
		   unsigned int renderingMode)
{
	this->m_name = name;
	this->m_size = size;
	this->m_renderingMode = renderingMode;
	this->m_glyphAtlas = new Texture2D(4096, 1024, CEDAR_R8, CEDAR_TEXTURE_2D);
	this->m_glyphAtlas->init();
	// Since the glyph image data basically only represents the alpha value we need to adjust the way the texture is swizzled
	// The glyph atlas will therefore be set up to return it's RED component as alpha value, and RGB will return 1.0 (= 255).
	int swizzle[] = {CEDAR_ONE, CEDAR_ONE, CEDAR_ONE, CEDAR_RED};
	this->m_glyphAtlas->setParameteriv(CEDAR_TEXTURE_SWIZZLE_RGBA, swizzle);

	this->m_face = FT_Face();
	if (FT_New_Face(getFontLibrary(), path.c_str(), 0, &this->m_face))
	{
		std::string message = "Could not load font \"";
		message.append(name);
		message.append("\" from file \"");
		message.append(path);
		message.append("\"!");
		throw FontCreationException(message);
	}

	this->m_currentOffsetX = 0;
	this->m_currentOffsetY = 0;
	this->m_atlasHeight = 1024;
	this->m_tallestCharacterInRow = 0;
	this->m_glyphs = std::map<unsigned int, Glyph*>();

	this->generateGlyphs(firstCharacter, lastCharacter);
}

Font::~Font()
{
	FT_Done_Face(this->m_face);
	delete this->m_glyphAtlas;
	for (const auto &pair : this->m_glyphs)
	{
		delete pair.second;
	}
}

const Glyph *Font::generateGlyph(const unsigned int unicode)
{
	return nullptr;
}

void Font::generateGlyphs(const unsigned int firstCharacter, const unsigned int lastCharacter)
{
	// Set the size of all glyphs.
	FT_Set_Pixel_Sizes(this->m_face, 0, this->m_size);

	// Count glyphs and allocate memory for them.
	unsigned int glyphCount = lastCharacter - firstCharacter + 1;
	GlyphData *glyphsData = new GlyphData[glyphCount];

	FT_Render_Mode ftRenderMode = this->m_renderingMode ? FT_RENDER_MODE_NORMAL : FT_RENDER_MODE_MONO;

	// We split the glyphs into two regions to avoid uploading every single glyph with a call to the graphics card,
	// but since we might generate glyphs for multiple rows and the first could start somewhere in the middle
	// of the texture we need two separate regions. If the row does not change while generating glyphs only the first
	// region is needed.
	Vector4ui firstRegion(this->m_currentOffsetX, this->m_currentOffsetY, 0, 0);
	int glyphsInFirstRegion = 0;
	Vector4ui secondRegion(0, 0, CEDAR_FONT_ATLAS_WIDTH, 0);
	bool needsTwoRegions = false;

	unsigned int glyphDataIndex = 0;
	for (unsigned int unicode = firstCharacter; unicode <= lastCharacter; unicode++)
	{
		// skip already generated glyphs
		auto it = this->m_glyphs.find(unicode);
		if (it != this->m_glyphs.end())
		{
			// Also reduce the glyph count since we didn't generate data for this one.
			glyphCount--;
			continue;
		}

		// Render glyph image
		unsigned int glyphIndex = FT_Get_Char_Index(this->m_face, unicode);
		FT_Load_Glyph(this->m_face, glyphIndex, FT_LOAD_DEFAULT);
		FT_GlyphSlot glyphSlot = this->m_face->glyph;
		FT_Render_Glyph(glyphSlot, ftRenderMode);

		// Get glyph metrics
		unsigned int glyphWidth = glyphSlot->bitmap.width;
		unsigned int glyphHeight = glyphSlot->bitmap.rows;
		unsigned int glyphSize = glyphWidth * glyphHeight;

		// Allocate memory for the image data
		glyphsData[glyphDataIndex].m_data = new unsigned char[glyphSize];

		// Freetype stores mono rendered glyphs in bits, so it requires special handling
		if (glyphSlot->bitmap.pixel_mode == FT_PIXEL_MODE_MONO)
		{
			// The pitch defines the number of bytes in one row of the bitmap.
			// Since the image buffer is in bits, there are multiple pixel per byte
			unsigned int glyphPitch = std::abs(glyphSlot->bitmap.pitch);
			unsigned int dataIndex = 0;
			for (unsigned int y = 0; y < glyphHeight; y++)
			{
				// Set the number of pixels that need to be read.
				int pixelLeft = static_cast<int>(glyphWidth);
				for (int x = 0; x < glyphPitch; x++)
				{
					unsigned int byte = glyphSlot->bitmap.buffer[y * glyphPitch + x];

					// Check how many bits need to be read from the byte.
					// Since the bits are stored left-to-right this is actually the lower boundary.
					unsigned int boundary = std::max(8 - pixelLeft, 0);
					for (unsigned int m = 7; m >= boundary; m--)
					{
						glyphsData[glyphDataIndex].m_data[dataIndex++] = ((byte >> m) & 0x1U) ? 255 : 0;
					}
					// Update the amount of bits left
					pixelLeft -= 8;
				}
			}
		}
		else
		{
			for (unsigned int n = 0; n < glyphSize; n++)
			{
				glyphsData[glyphDataIndex].m_data[n] = glyphSlot->bitmap.buffer[n];
			}
		}

		// Check if the glyph fits on the glyph atlas vertically
		if (this->m_currentOffsetY + glyphHeight >= this->m_atlasHeight)
			this->m_glyphAtlas->setSize(CEDAR_FONT_ATLAS_WIDTH, this->m_atlasHeight * 2);

		// Check if the glyph fits on the texture horizontally
		if (this->m_currentOffsetX + glyphWidth >= CEDAR_FONT_ATLAS_WIDTH)
		{
			this->m_currentOffsetY += this->m_tallestCharacterInRow;

			// Since we advanced the y offset we need to check for space again
			if (this->m_currentOffsetY + glyphHeight >= this->m_atlasHeight)
				this->m_glyphAtlas->setSize(CEDAR_FONT_ATLAS_WIDTH, this->m_atlasHeight * 2);

			if (!needsTwoRegions)
			{
				// Set the width and height of the first region
				firstRegion.z = this->m_currentOffsetX - firstRegion.x;
				firstRegion.w = this->m_tallestCharacterInRow;
				// Set the y coordinate of the second region
				secondRegion.y = this->m_currentOffsetY;
				needsTwoRegions = true;
			}
			else
			{
				secondRegion.w += this->m_tallestCharacterInRow;
			}
			// Reset x offset to 0 because of new row
			this->m_currentOffsetX = 0;
			this->m_tallestCharacterInRow = glyphHeight;
		}
		else if (glyphHeight > this->m_tallestCharacterInRow)
		{
			this->m_tallestCharacterInRow = glyphHeight;
			// Also update height of the first region if we are still in it
			if (!needsTwoRegions)
				firstRegion.w = glyphHeight;
		}

		// Set data of the glyph
		glyphsData[glyphDataIndex].m_unicode = unicode;
		glyphsData[glyphDataIndex].m_offset = Vector2ui(this->m_currentOffsetX, this->m_currentOffsetY);
		glyphsData[glyphDataIndex].m_size = Vector2i(static_cast<int>(glyphWidth), static_cast<int>(glyphHeight));
		glyphsData[glyphDataIndex].m_bearing = Vector2i(glyphSlot->bitmap_left, glyphSlot->bitmap_top);
		glyphsData[glyphDataIndex].m_advance = static_cast<unsigned int>(glyphSlot->advance.x) >> 6U;

		if (!needsTwoRegions)
			glyphsInFirstRegion++;

		this->m_currentOffsetX += glyphWidth;
		glyphDataIndex++;
	}

	// If we only need the first region the width and height hasn't been set yet.
	if (!needsTwoRegions)
	{
		// Set the width and height of the first region
		firstRegion.z = this->m_currentOffsetX;
		firstRegion.w = this->m_tallestCharacterInRow;
	}

	float pixelWidth = 1.0f / CEDAR_FONT_ATLAS_WIDTH;
	float pixelHeight = 1.0f / static_cast<float>(this->m_atlasHeight);

	// allocate memory for the first region
	unsigned int regionDataLength = firstRegion.z * firstRegion.w;
	unsigned char *regionData = new unsigned char[regionDataLength];

	// Stitch first region together
	for (int n = 0; n < glyphsInFirstRegion; n++)
	{
		GlyphData *glyphData = &glyphsData[n];
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
				unsigned int regionIndex = firstRegion.z * (glyphData->m_offset.y - firstRegion.y + y) + x + glyphData->m_offset.x;
				unsigned int dataIndex = glyphData->m_size.x * y + x;
				regionData[regionIndex] = glyphData->m_data[dataIndex];
			}
		}

		this->m_glyphs.insert(std::make_pair(glyphData->m_unicode, glyph));
	}

	// Upload first region to texture
	this->m_glyphAtlas->upload(static_cast<int>(firstRegion.x), static_cast<int>(firstRegion.y),
							   static_cast<int>(firstRegion.z), static_cast<int>(firstRegion.w),
							   CEDAR_RED, CEDAR_UNSIGNED_BYTE, regionData);

	delete[] regionData;

	if (needsTwoRegions)
	{
		// Update the height of the region once more since we only add up the height of the last row if we start a new one
		secondRegion.w += this->m_tallestCharacterInRow;

		// allocate memory for the second region
		regionData = new unsigned char[secondRegion.z * secondRegion.w];

		// Stitch second region together
		for (int n = glyphsInFirstRegion; n < glyphCount; n++)
		{
			GlyphData *glyphData = &glyphsData[n];
			Glyph *glyph = new Glyph(glyphData->m_size,
									 glyphData->m_bearing,
									 glyphData->m_advance,
									 Vector4f(pixelWidth * static_cast<float>(glyphData->m_offset.x),
											  pixelHeight * static_cast<float>(glyphData->m_offset.y),
											  pixelWidth * static_cast<float>(glyphData->m_offset.x + glyphData->m_size.x),
											  pixelWidth * static_cast<float>(glyphData->m_offset.y + glyphData->m_size.y))
									);

			// Copy glyph image into region data
			for (int x = 0; x < glyphData->m_size.x; x++)
			{
				for (int y = 0; y < glyphData->m_size.y; y++)
				{
					unsigned int regionIndex = firstRegion.z * (glyphData->m_offset.y - firstRegion.y + y) + x + glyphData->m_offset.x;
					unsigned int dataIndex = glyphData->m_size.x * y + x;
					regionData[regionIndex] = glyphData->m_data[dataIndex];
				}
			}

			std::pair<unsigned int, Glyph*> pair = std::make_pair(glyphData->m_unicode, glyph);
			this->m_glyphs.insert(pair);
		}

		// Upload second region to texture
		this->m_glyphAtlas->upload(static_cast<int>(secondRegion.x), static_cast<int>(secondRegion.y),
								   static_cast<int>(secondRegion.z), static_cast<int>(secondRegion.w),
								   CEDAR_RED, CEDAR_UNSIGNED_BYTE, regionData);

		delete[] regionData;
	}

	delete[] glyphsData;
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
		return this->generateGlyph(unicode);
	}
}

const Texture2D *Font::getGlyphAtlas() const
{
	return this->m_glyphAtlas;
}
