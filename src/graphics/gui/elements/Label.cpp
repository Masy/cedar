//
// Created by masy on 08.03.20.
//

#include "cedar/Label.hpp"
#include "cedar/Renderer2D.hpp"

using namespace cedar;

Label::Label(float originX, float originY, unsigned char zIndex, const std::string &text, cedar::Font *font, const cedar::Vector4f &textColor,
			 unsigned int alignment)
		: Element(originX, originY, zIndex, 0.0f, 0.0f, alignment)
{
	if (text.empty())
		throw ElementCreationException("Could not create label. The text of the label can't be empty!");

	if (!font)
		throw ElementCreationException("Could not create label. The label must have a font!");

	this->m_text = text;
	this->m_font = font;
	this->m_textColor = textColor;
	this->m_textBuffer = nullptr;

	this->setText(text);
}

Label::~Label()
{
	delete this->m_textBuffer;
}

void Label::render(unsigned long currentTime)
{
	Renderer2D::drawText(this->m_posX, this->m_posY, this->m_zIndex, this->m_textBuffer, &this->m_textColor);
}

std::string Label::getText() const {
	return this->m_text;
}

void Label::setText(const std::string &text) {
	if (text.empty())
		throw ElementUpdateException("Could not set text of label. The text can't be empty!");

	this->m_text = text;
	delete this->m_textBuffer;

	this->m_textBuffer = Renderer2D::generateTextBuffer(text, this->m_font, this->m_alignment);
	this->m_width = this->m_textBuffer->getSize().x;
	this->m_height = this->m_textBuffer->getSize().y;

	unsigned int horizontalAlignment = this->m_alignment & 0x03u;
	switch (horizontalAlignment)
	{
		case CEDAR_ALIGNMENT_CENTER:
			this->m_posX = this->m_originX - (this->m_width * 0.5f);
			break;

		case CEDAR_ALIGNMENT_RIGHT:
			this->m_posX = this->m_originX - this->m_width;
			break;

		default:
			this->m_posX = this->m_originX;
			break;
	}

	unsigned int verticalAlignment = this->m_alignment & 0x0Cu;
	switch (verticalAlignment)
	{
		case CEDAR_ALIGNMENT_MIDDLE:
			this->m_posY = this->m_originY - (this->m_height * 0.5f);
			break;

		case CEDAR_ALIGNMENT_BOTTOM:
			this->m_posY = this->m_originY - this->m_height;
			break;

		default:
			this->m_posY = this->m_originY;
			break;
	}
}

Font *Label::getFont() const {
	return this->m_font;
}

void Label::setFont(Font *newFont) {
	if (!newFont)
		throw ElementUpdateException("Could not set font of label. The new font can't be a nullptr!");

	this->m_font = newFont;
	this->setText(this->m_text);
}

void Label::setTextColor(const Vector4f &color) {
	this->m_textColor = color;
}

void Label::setWidth(const float newWidth) {
	throw UnsupportedOperationException("Setting the width of a label is not allowed as the width is defined by the text.");
}

void Label::setHeight(const float newHeight) {
	throw UnsupportedOperationException("Setting the height of a label is not allowed as the height is defined by the text.");
}

void Label::setSize(const float newWidth, const float newHeight) {
	throw UnsupportedOperationException("Setting the size of a label is not allowed as the size is defined by the text.");
}


