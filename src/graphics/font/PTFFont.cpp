//
// Created by masy on 11.04.20.
//

#include <iostream>
#include "cedar/PTFFont.hpp"

using namespace cedar;

PTFFont::PTFFont(const std::string &name, const std::string &path, const unsigned int scale)
		: Font(name, 1, CEDAR_RGBA8, CEDAR_RENDERING_SHARP)
{
	this->m_scale = scale;
	this->m_paletteSize = 0;
	this->m_palette = nullptr;
	this->m_dictionary = std::map<unsigned int, unsigned int>();

	this->m_fontPath = path;
	this->m_fontFile = std::ifstream(path, std::ifstream::binary);
	if (!this->m_fontFile.is_open())
		throw FontCreationException("Could not create ptf font " + name + "! Could not open file from path " + path + "!");

	this->m_dictionaryPointer = 0;
	this->m_fontFile.read(reinterpret_cast<char *>(&this->m_dictionaryPointer), 4);
	this->m_fontFile.read(reinterpret_cast<char *>(&this->m_size), 4);
	this->m_size *= scale;

	this->loadPalette();
	this->loadDictionary();
	this->m_fontFile.close();

	this->m_glyphAtlas->setParameteri(CEDAR_TEXTURE_MIN_FILTER, CEDAR_NEAREST);
	this->m_glyphAtlas->setParameteri(CEDAR_TEXTURE_MAG_FILTER, CEDAR_NEAREST);
}

PTFFont::~PTFFont()
{
	delete[] this->m_palette;
	delete this->m_glyphAtlas;
	for (const auto &pair : this->m_glyphs)
	{
		delete pair.second;
	}
}

void PTFFont::loadPalette()
{
	if (!this->m_fontFile.is_open())
	{
		this->m_fontFile.open(this->m_fontPath, std::ifstream::binary);

		if (!this->m_fontFile.is_open())
			throw FontLoadException("Could not load palette of font " + this->m_name + "!");
	}

	this->m_fontFile.seekg(8);
	this->m_fontFile.read(reinterpret_cast<char *>(&this->m_paletteSize), 1);
	this->m_palette = new unsigned int[this->m_paletteSize];
	for (int n = 0; n < this->m_paletteSize; n++)
		this->m_fontFile.read(reinterpret_cast<char *>(this->m_palette + n), 4);
}

void PTFFont::loadDictionary()
{
	if (!this->m_fontFile.is_open())
	{
		this->m_fontFile.open(this->m_fontPath, std::ifstream::binary);

		if (!this->m_fontFile.is_open())
			throw FontLoadException("Could not load dictionary of font " + this->m_name + "!");
	}

	this->m_fontFile.seekg(this->m_dictionaryPointer);
	unsigned int dictionarySize;
	this->m_fontFile.read(reinterpret_cast<char *>(&dictionarySize), 4);
	for (int n = 0; n < dictionarySize; n++)
	{
		unsigned int unicode;
		unsigned int glyphPtr;
		this->m_fontFile.read(reinterpret_cast<char *>(&unicode), 4);
		this->m_fontFile.read(reinterpret_cast<char *>(&glyphPtr), 4);
		this->m_dictionary.insert(std::make_pair(unicode, glyphPtr));
	}
}

const Glyph *PTFFont::loadGlyph(const unsigned int unicode)
{
	if (!this->m_fontFile.is_open())
	{
		this->m_fontFile.open(this->m_fontPath, std::ifstream::binary);
		if (!this->m_fontFile.is_open())
			throw FontLoadException("Could not generate glyphs of font " + this->m_name + "! Could not open font file!");
	}

	this->m_glyphData = new GlyphData();

	unsigned long glyphDataPointer;
	auto dictionaryIt = this->m_dictionary.find(unicode);
	if (dictionaryIt == this->m_dictionary.end())
	{
		dictionaryIt = this->m_dictionary.find(0);
		if (dictionaryIt == this->m_dictionary.end())
			throw FontLoadException("Could not generate glyph for code point " + std::to_string(unicode) + "!");
		else
			glyphDataPointer = dictionaryIt->second;
	}
	else
	{
		glyphDataPointer = dictionaryIt->second;
	}

	unsigned int width;
	unsigned int height;
	unsigned int glyphSize;
	int bearingX;
	int bearingY;
	int advance;

	this->m_fontFile.seekg(glyphDataPointer);
	this->m_fontFile.read(reinterpret_cast<char *>(&width), 4);
	this->m_fontFile.read(reinterpret_cast<char *>(&height), 4);
	this->m_fontFile.read(reinterpret_cast<char *>(&bearingX), 4);
	this->m_fontFile.read(reinterpret_cast<char *>(&bearingY), 4);
	this->m_fontFile.read(reinterpret_cast<char *>(&advance), 4);

	glyphSize = width * height;
	auto *glyphPaletteData = new unsigned char[glyphSize];
	this->m_fontFile.read(reinterpret_cast<char *>(glyphPaletteData), glyphSize);

	auto *glyphImageData = new unsigned char[glyphSize * 4];
	auto *intData = reinterpret_cast<unsigned char*>(glyphImageData);
	for (unsigned int n = 0; n < glyphSize; n++)
	{
		intData[n] = this->m_palette[glyphPaletteData[n]];
	}

	delete[] glyphPaletteData;

	this->m_glyphData->m_unicode = unicode;
	this->m_glyphData->m_size = Vector2i(static_cast<int>(width), static_cast<int>(height));
	this->m_glyphData->m_bearing = Vector2i(static_cast<int>(bearingX * this->m_scale), static_cast<int>(bearingY * this->m_scale));
	this->m_glyphData->m_advance = advance * this->m_scale;
	this->m_glyphData->m_data = reinterpret_cast<unsigned char*>(glyphImageData);

	auto glyph = this->createGlyph();
	delete this->m_glyphData;
	return glyph;
}

const Glyph *PTFFont::createGlyph()
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
	auto glyph = new Glyph(this->m_glyphData->m_size * this->m_scale,
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

void PTFFont::stitchAtlas(unsigned int firstIndex, unsigned int lastIndex, const cedar::Vector4ui &region)
{
	float pixelWidth = 1.0f / CEDAR_FONT_ATLAS_WIDTH;
	float pixelHeight = 1.0f / static_cast<float>(this->m_atlasHeight);

	// Calculate region length
	unsigned int regionDataLength = region.z * region.w * 4;
	// Allocate memory with calloc to avoid artifacts near the glyphs since we only write to the region where there are glyph images
	unsigned char *regionData = reinterpret_cast<unsigned char *>(calloc(regionDataLength, 1));

	// Stitch region together
	for (unsigned int n = firstIndex; n < lastIndex; n++)
	{
		GlyphData *glyphData = &this->m_glyphData[n];
		Glyph *glyph = new Glyph(glyphData->m_size * this->m_scale,
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
				unsigned int regionIndex = (region.z * (glyphData->m_offset.y - region.y + y) + x + glyphData->m_offset.x) * 4;
				unsigned int dataIndex = (glyphData->m_size.x * y + x) * 4;

				regionData[regionIndex] = glyphData->m_data[dataIndex];
				regionData[regionIndex + 1] = glyphData->m_data[dataIndex + 1];
				regionData[regionIndex + 2] = glyphData->m_data[dataIndex + 2];
				regionData[regionIndex + 3] = glyphData->m_data[dataIndex + 3];
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

void PTFFont::generateGlyphs(const unsigned int firstCharacter, const unsigned int lastCharacter)
{
	if (!this->m_fontFile.is_open())
	{
		this->m_fontFile.open(this->m_fontPath, std::ifstream::binary);
		if (!this->m_fontFile.is_open())
			throw FontLoadException("Could not generate glyphs of font " + this->m_name + "! Could not open font file!");
	}


	unsigned int glyphCount = lastCharacter - firstCharacter + 1;
	this->m_glyphData = new GlyphData[glyphCount];

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
		auto glyphIt = this->m_glyphs.find(unicode);
		if (glyphIt != this->m_glyphs.end())
		{
			// Also reduce the glyph count since we didn't generate data for this one.
			glyphCount--;
			continue;
		}

		unsigned int glyphDataPointer;


		auto dictionaryIt = this->m_dictionary.find(unicode);
		if (dictionaryIt == this->m_dictionary.end())
		{
			dictionaryIt = this->m_dictionary.find(0u);
			if (dictionaryIt == this->m_dictionary.end())
				throw FontLoadException("Could not generate glyph for code point " + std::to_string(unicode) + "!");
			else
				glyphDataPointer = dictionaryIt->second;
		}
		else
		{
			glyphDataPointer = dictionaryIt->second;
		}

		unsigned int width;
		unsigned int height;
		unsigned int glyphSize;
		int bearingX;
		int bearingY;
		int advance;

		this->m_fontFile.seekg(glyphDataPointer);
		this->m_fontFile.read(reinterpret_cast<char *>(&width), 4);
		this->m_fontFile.read(reinterpret_cast<char *>(&height), 4);
		this->m_fontFile.read(reinterpret_cast<char *>(&bearingX), 4);
		this->m_fontFile.read(reinterpret_cast<char *>(&bearingY), 4);
		this->m_fontFile.read(reinterpret_cast<char *>(&advance), 4);

		bearingX *= this->m_scale;
		bearingY *= this->m_scale;
		advance *= this->m_scale;

		if (width == 0 || height == 0)
		{
			Glyph *glyph = new Glyph(Vector2i(static_cast<int>(width * this->m_scale), static_cast<int>(height * this->m_scale)),
									 Vector2i(bearingX, bearingY),
									 advance,
									 Vector4f(0.0f, 0.0f, 0.0f, 0.0f)
									);
			this->m_glyphs.insert(std::make_pair(unicode, glyph));
			glyphCount--;
			continue;
		}

		glyphSize = width * height;
		auto *glyphPaletteData = new unsigned char[glyphSize];
		this->m_fontFile.read(reinterpret_cast<char *>(glyphPaletteData), glyphSize);

		auto *glyphImageData = new unsigned char[glyphSize * 4];
		auto *intData = reinterpret_cast<unsigned int*>(glyphImageData);
		for (int n = 0; n < glyphSize; n++)
		{
			intData[n] = this->m_palette[glyphPaletteData[n]];
		}

		delete[] glyphPaletteData;

		// Check if the glyph fits on the glyph atlas vertically
		if (this->m_currentOffsetY + height >= this->m_atlasHeight)
			this->resize();

		// Check if the glyph fits on the texture horizontally
		if (this->m_currentOffsetX + width >= CEDAR_FONT_ATLAS_WIDTH)
		{
			this->m_currentOffsetY += this->m_tallestCharacterInRow;

			// Since we advanced the y offset we need to check for space again
			if (this->m_currentOffsetY + height >= this->m_atlasHeight)
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
			this->m_tallestCharacterInRow = height;
		}
		else if (height > this->m_tallestCharacterInRow)
		{
			this->m_tallestCharacterInRow = height;
			// Also update height of the first region if we are still in it
			if (!needsTwoRegions)
				firstRegion.w = height;
		}

		// Set data of the glyph
		this->m_glyphData[glyphDataIndex].m_unicode = unicode;
		this->m_glyphData[glyphDataIndex].m_offset = Vector2ui(this->m_currentOffsetX, this->m_currentOffsetY);
		this->m_glyphData[glyphDataIndex].m_size = Vector2i(static_cast<int>(width), static_cast<int>(height));
		this->m_glyphData[glyphDataIndex].m_bearing = Vector2i(bearingX, bearingY);
		this->m_glyphData[glyphDataIndex].m_advance = advance;
		this->m_glyphData[glyphDataIndex].m_data = reinterpret_cast<unsigned char*>(glyphImageData);

		if (!needsTwoRegions)
			glyphsInFirstRegion++;

		this->m_currentOffsetX += width;
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
