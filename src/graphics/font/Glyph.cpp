//
// Created by masy on 03.03.20.
//

#include "cedar/Glyph.h"

using namespace cedar;

Glyph::Glyph() : Glyph({0, 0}, {0, 0}, 0, {0.0f, 0.0f, 0.0f, 0.0f})
{}

Glyph::Glyph(const cedar::Vector2i &size, const cedar::Vector2i &bearing, const unsigned int advance, const cedar::Vector4f &uvs)
{
	this->m_size = size;
	this->m_bearing = bearing;
	this->m_advance = advance;
	this->m_uvs = uvs;
}