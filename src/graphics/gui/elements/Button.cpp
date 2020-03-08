//
// Created by masy on 08.03.20.
//

#include "cedar/Button.h"
#include "cedar/Renderer2D.h"
#include "cedar/Cedar.h"

using namespace cedar;

Button::Button(const float originX, const float originY, const unsigned char zIndex,
			   const float width, const float height, const std::string &text, Font *font,
			   const Vector4f &color, const unsigned int alignment)
		: Element(originX, originY, zIndex, width, height, alignment)
{
	if (!text.empty() && !font)
		throw ElementCreationException("Could not create button. If the text is not empty a font must be provided!");

	this->m_interactable = true;

	this->m_text = text;
	this->m_font = font;
	this->m_textColor = color;
	this->m_hoveredTextColor = color;
	this->m_pressedTextColor = color;

	if (!text.empty())
		this->m_textBuffer = Renderer2D::generateTextBuffer(text, font, CEDAR_ALIGNMENT_CENTER | CEDAR_ALIGNMENT_MIDDLE);
}

Button::~Button()
{
	delete this->m_textBuffer;
}

void Button::render(unsigned long currentTime)
{
	Vector4f bgColor;
	Vector4f textColor;

	if (this->m_pressed)
	{
		bgColor = this->m_pressedBackgroundColor;
		textColor = this->m_pressedTextColor;
	}
	else if (this->m_hovered)
	{
		bgColor = this->m_hoveredBackgroundColor;
		textColor = this->m_hoveredTextColor;
	}
	else
	{
		bgColor = this->m_backgroundColor;
		textColor = this->m_textColor;
	}

	Renderer2D::drawRect(this->m_posX, this->m_posY, this->m_zIndex, this->m_width, this->m_height, &bgColor);
	if (this->m_textBuffer)
		Renderer2D::drawText(this->m_posX + (this->m_width * 0.5f), this->m_posY + (this->m_height * 0.5f), this->m_zIndex, this->m_textBuffer, &textColor);
}

void Button::setBackgroundColor(const Vector4f &color) {
	this->m_backgroundColor = color;
}

void Button::setHoveredBackgroundColor(const Vector4f &color) {
	this->m_hoveredBackgroundColor = color;
}

void Button::setPressedBackgroundColor(const Vector4f &color) {
	this->m_pressedBackgroundColor = color;
}

void Button::setTextColor(const Vector4f &color) {
	this->m_textColor = color;
}

void Button::setHoveredTextColor(const Vector4f &color) {
	this->m_hoveredTextColor = color;
}

void Button::setPressedTextColor(const Vector4f &color) {
	this->m_pressedTextColor = color;
}

std::string Button::getText() const {
	return this->m_text;
}

void Button::setText(const std::string &text) {
	if (!text.empty() && !this->m_font)
		throw ElementUpdateException("Could not set text of button. There has to be a font for the button to have text!");

	this->m_text = text;
	delete this->m_textBuffer;
	this->m_textBuffer = Renderer2D::generateTextBuffer(text, this->m_font, CEDAR_ALIGNMENT_CENTER | CEDAR_ALIGNMENT_MIDDLE);
}

Font *Button::getFont() const {
	return this->m_font;
}

void Button::setFont(Font *newFont) {
	if (!newFont)
		throw ElementUpdateException("Could not set font of button. The new font can't be a nullptr!");

	this->m_font = newFont;
	if (!this->m_text.empty())
		this->setText(this->m_text);
}
