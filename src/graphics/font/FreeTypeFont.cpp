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
						   : Font(name, size, CEDAR_R8, renderingMode)
{
	int swizzle[] = {CEDAR_ONE, CEDAR_ONE, CEDAR_ONE, CEDAR_RED};
	this->m_glyphAtlas->setParameteriv(CEDAR_TEXTURE_SWIZZLE_RGBA, swizzle);

	this->m_face = FT_Face();
	if (FT_New_Face(getFontLibrary(), path.c_str(), 0, &this->m_face))
	{
		std::string message = "Could not load FreeType font \"";
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

	this->m_glyphData = new GlyphData();

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
	this->m_glyphData->m_data = new unsigned char[glyphSize];

	// FreeType stores mono rendered glyphs in bits, so it requires special handling
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
					this->m_glyphData->m_data[dataIndex++] = ((byte >> m) & 0x1U) ? 255 : 0;
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
			this->m_glyphData->m_data[n] = glyphSlot->bitmap.buffer[n];
		}
	}

	this->m_glyphData->m_unicode = unicode;
	this->m_glyphData->m_size = Vector2i(static_cast<int>(glyphWidth), static_cast<int>(glyphHeight));
	this->m_glyphData->m_bearing = Vector2i(glyphSlot->bitmap_left, glyphSlot->bitmap_top);
	this->m_glyphData->m_advance = static_cast<unsigned int>(glyphSlot->advance.x) >> 6U; // freetype stores the advance as 1/64th pixel

	auto glyph = this->createGlyph();
	delete this->m_glyphData;
	return glyph;
}

const Glyph *FreeTypeFont::createGlyph()
{
	// Check if the glyph fits on the glyph atlas vertically
	if (this->m_currentOffsetY + this->m_glyphData->m_size.y >= this->m_atlasHeight)
		this->resize();

	// Check if the glyph fits on the texture horizontally
	if (this->m_currentOffsetX + this->m_glyphData->m_size.x >= CEDAR_FONT_ATLAS_WIDTH)
	{
		this->m_currentOffsetY += this->m_tallestCharacterInRow;

		// Since we advanced the y offset we need to check for space again
		if (this->m_currentOffsetY + this->m_glyphData->m_size.y >= this->m_atlasHeight)
			this->resize();

		// Reset x offset to 0 because of new row
		this->m_currentOffsetX = 0;
		this->m_tallestCharacterInRow = this->m_glyphData->m_size.y;
	}
	else if (this->m_glyphData->m_size.y > this->m_tallestCharacterInRow)
	{
		this->m_tallestCharacterInRow = this->m_glyphData->m_size.y;
	}

	float pixelWidth = 1.0f / CEDAR_FONT_ATLAS_WIDTH;
	float pixelHeight = 1.0f / static_cast<float>(this->m_atlasHeight);
	auto glyph = new Glyph(this->m_glyphData->m_size,
						   this->m_glyphData->m_bearing,
						   this->m_glyphData->m_advance,
						   Vector4f(pixelWidth * static_cast<float>(this->m_currentOffsetX),
									pixelHeight * static_cast<float>(this->m_currentOffsetY),
									pixelWidth * static_cast<float>(this->m_currentOffsetX + static_cast<int>(this->m_glyphData->m_size.x)),
									pixelHeight * static_cast<float>(this->m_currentOffsetY + static_cast<int>(this->m_glyphData->m_size.y))
								   )
						  );

	this->m_glyphAtlas->upload(static_cast<int>(this->m_currentOffsetX), static_cast<int>(this->m_currentOffsetY),
							   static_cast<int>(this->m_glyphData->m_size.x), static_cast<int>(this->m_glyphData->m_size.y),
							   Texture::sizedToUnsized(this->m_internalFormat), CEDAR_UNSIGNED_BYTE, this->m_glyphData->m_data);

	this->m_currentOffsetX += this->m_glyphData->m_size.x;

	this->m_glyphs.insert(std::make_pair(this->m_glyphData->m_unicode, glyph));
	return glyph;
}

void FreeTypeFont::stitchAtlas(unsigned int firstIndex, unsigned int lastIndex, const cedar::Vector4ui &region)
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
							   Texture::sizedToUnsized(this->m_internalFormat), CEDAR_UNSIGNED_BYTE, regionData);

	free(regionData);
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
