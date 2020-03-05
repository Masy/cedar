//
// Created by masy on 05.03.20.
//

#include "cedar/TextBuffer.h"

using namespace cedar;

TextBuffer::TextBuffer(const unsigned int glyphAtlasId, const unsigned int glyphCount, cedar::Quad *quads)
{
	this->m_glyphAtlasId = glyphAtlasId;
	this->m_glyphCount = glyphCount;
	this->m_quads = quads;
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
