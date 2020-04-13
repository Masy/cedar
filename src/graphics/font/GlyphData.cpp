//
// Created by masy on 03.03.20.
//

#include "cedar/GlyphData.hpp"

using namespace cedar;

GlyphData::GlyphData() : GlyphData(0, {0, 0}, {0, 0}, {0, 0}, 0, nullptr)
{}

GlyphData::GlyphData(const unsigned int unicode, const cedar::Vector2ui &offset, const cedar::Vector2i &size, const cedar::Vector2i &bearing,
					 const unsigned int advance, unsigned char *data)
{
	this->m_unicode = unicode;
	this->m_offset = offset;
	this->m_size = size;
	this->m_bearing = bearing;
	this->m_advance = advance;
	this->m_data = data;
}

GlyphData::~GlyphData()
{
	delete[] this->m_data;
}
