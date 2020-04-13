//
// Created by masy on 05.03.20.
//

#include "cedar/TextBuffer.hpp"

using namespace cedar;

TextBuffer::TextBuffer(const unsigned int glyphAtlasId, const unsigned int glyphCount, cedar::Quad *quads, const Vector2f &size)
{
	this->m_glyphAtlasId = glyphAtlasId;
	this->m_glyphCount = glyphCount;
	this->m_quads = quads;
	this->m_size = size;
}

TextBuffer::~TextBuffer()
{
	delete[] this->m_quads;
}

unsigned int TextBuffer::getGlyphAtlas() const
{
	return this->m_glyphAtlasId;
}

unsigned int TextBuffer::getGlyphCount() const
{
	return this->m_glyphCount;
}

const Quad *TextBuffer::getQuads() const
{
	return this->m_quads;
}

Vector2f TextBuffer::getSize() const {
	return this->m_size;
}
