//
// Created by masy on 11.04.20.
//

#include "cedar/FreeTypeFont.hpp"

using namespace cedar;



FreeTypeInitException::FreeTypeInitException(const std::string &message) : FontException(message)
{}



FT_Library &FreeTypeFont::getFontLibrary()
{
	static FT_Library library;
	static bool initialized = false;
	if (!initialized)
	{
		if (FT_Init_FreeType(&library))
			throw FreeTypeInitException("Could not initialize FreeType!");

		initialized = true;
	}

	return library;
}

FreeTypeFont::FreeTypeFont(const std::string &name, const std::string &path, unsigned int size, unsigned int renderingMode)
						   : Font(name, size, renderingMode)
{
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
}

FreeTypeFont::~FreeTypeFont()
{
	FT_Done_Face(this->m_face);
	delete this->m_glyphAtlas;
	for (const auto &pair : this->m_glyphs)
	{
		delete pair.second;
	}
}

const Glyph *FreeTypeFont::loadGlyph(const unsigned int unicode)
{
	// Set the size of all glyphs.
	FT_Set_Pixel_Sizes(this->m_face, 0, this->m_size);

	FT_Render_Mode ftRenderMode = this->m_renderingMode ? FT_RENDER_MODE_NORMAL : FT_RENDER_MODE_MONO;

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
	unsigned char glyphImageData[glyphSize];

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
				int boundary = std::max(8 - pixelLeft, 0);
				for (int m = 7; m >= boundary; m--)
				{
					glyphImageData[dataIndex++] = ((byte >> m) & 0x1U) ? 255 : 0;
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
			glyphImageData[n] = glyphSlot->bitmap.buffer[n];
		}
	}

	return this->createGlyph(unicode, glyphWidth, glyphHeight, glyphSlot->bitmap_left, glyphSlot->bitmap_top, static_cast<unsigned int>(glyphSlot->advance.x) >> 6U, glyphImageData);
}



void FreeTypeFont::generateGlyphs(const unsigned int firstCharacter, const unsigned int lastCharacter)
{
	// Set the size of all glyphs.
	FT_Set_Pixel_Sizes(this->m_face, 0, this->m_size);

	// Count glyphs and allocate memory for them.
	unsigned int glyphCount = lastCharacter - firstCharacter + 1;
	this->m_glyphData = new GlyphData[glyphCount];

	FT_Render_Mode ftRenderMode = this->m_renderingMode ? FT_RENDER_MODE_NORMAL : FT_RENDER_MODE_MONO;

	// We split the glyphs into two regions to avoid uploading every single glyph with a call to the graphics card,
	// but since we might generate glyphs for multiple rows and the first could start somewhere in the middle
	// of the texture we need two separate regions. If the row does not change while generating glyphs only the first
	// region is needed.
	Vector4ui firstRegion(this->m_currentOffsetX, this->m_currentOffsetY, 0, 0);
	int glyphsInFirstRegion = 0;
	Vector4ui secondRegion(0, 0, 0, 0);
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
		this->m_glyphData[glyphDataIndex].m_data = new unsigned char[glyphSize];

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
					int boundary = std::max(8 - pixelLeft, 0);
					for (int m = 7; m >= boundary; m--)
					{
						this->m_glyphData[glyphDataIndex].m_data[dataIndex++] = ((byte >> m) & 0x1U) ? 255 : 0;
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
				this->m_glyphData[glyphDataIndex].m_data[n] = glyphSlot->bitmap.buffer[n];
			}
		}

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
				secondRegion.z = std::max(secondRegion.z, this->m_currentOffsetX);
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
		this->m_glyphData[glyphDataIndex].m_unicode = unicode;
		this->m_glyphData[glyphDataIndex].m_offset = Vector2ui(this->m_currentOffsetX, this->m_currentOffsetY);
		this->m_glyphData[glyphDataIndex].m_size = Vector2i(static_cast<int>(glyphWidth), static_cast<int>(glyphHeight));
		this->m_glyphData[glyphDataIndex].m_bearing = Vector2i(glyphSlot->bitmap_left, glyphSlot->bitmap_top);
		this->m_glyphData[glyphDataIndex].m_advance = static_cast<unsigned int>(glyphSlot->advance.x) >> 6U; // freetype stores the advance as 1/64th pixel

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

	// Stitch the image data of the first region together and upload it to the graphics card
	this->stitchAtlas(0, glyphsInFirstRegion, firstRegion);

	if (needsTwoRegions)
	{
		// Update the size of the region once more since we only update if we start a new one
		secondRegion.w += this->m_tallestCharacterInRow;
		secondRegion.z = std::max(secondRegion.z, this->m_currentOffsetX);

		// Stitch the image data of the second region together and upload it to the graphics card
		this->stitchAtlas(glyphsInFirstRegion, glyphCount, secondRegion);
	}

	// Free the allocated memory for the glyphs data
	delete[] this->m_glyphData;
}
