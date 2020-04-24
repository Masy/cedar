//
// Created by masy on 23.04.20.
//

#include "cedar/ImageButton.hpp"
#include "cedar/Renderer2D.hpp"

using namespace cedar;

ImageButton::ImageButton(const float originX, const float originY, const unsigned char zIndex, const float width, const float height,
						 const std::shared_ptr<Texture> &texture, const cedar::Vector4f &defaultUVs,
						 const cedar::Vector4f &hoveredUVs, const cedar::Vector4f &pressedUVs,
						 const std::string &caption, const std::shared_ptr<Font> &font, const cedar::Vector4f &captionColor,
						 const unsigned int alignment)
		: ImageButton(originX, originY, zIndex, width, height, texture, defaultUVs, hoveredUVs, pressedUVs,
					  caption, font, captionColor, captionColor, captionColor, alignment)
{}

ImageButton::ImageButton(const float originX, const float originY, const unsigned char zIndex, const float width, const float height,
						 const std::shared_ptr<Texture> &texture, const cedar::Vector4f &defaultUVs,
						 const cedar::Vector4f &hoveredUVs, const cedar::Vector4f &pressedUVs,
						 const std::string &caption, const std::shared_ptr<Font> &font, const cedar::Vector4f &defaultCaptionColor,
						 const Vector4f &hoveredCaptionColor, const Vector4f &pressedCaptionColor, const unsigned int alignment)
		: Element(originX, originY, zIndex, width, height, alignment)
{
	if (!dynamic_cast<Texture2D *>(texture.get()))
		throw ElementCreationException("Could not create image button. The provided texture must be a two dimensional texture!");

	if (!caption.empty() && !font)
		throw ElementCreationException("Could not create image button. If the caption is not empty a font must be provided!");

	this->m_interactable = true;

	this->m_texture = texture;
	this->m_defaultUVs = defaultUVs;
	this->m_hoveredUVs = hoveredUVs;
	this->m_pressedUVs = pressedUVs;
	this->m_caption = caption;
	this->m_font = font;
	this->m_defaultCaptionColor = defaultCaptionColor;
	this->m_hoveredCaptionColor = hoveredCaptionColor;
	this->m_pressedCaptionColor = pressedCaptionColor;

	if (!caption.empty())
		this->m_textBuffer = Renderer2D::generateTextBuffer(caption, font, CEDAR_ALIGNMENT_MIDDLE | CEDAR_ALIGNMENT_CENTER);
	else
		this->m_textBuffer = nullptr;
}

ImageButton::~ImageButton()
{
	delete this->m_textBuffer;
}

std::shared_ptr<Texture> ImageButton::getTexture() const {
	return this->m_texture;
}

std::string ImageButton::getCaption() const {
	return this->m_caption;
}

void ImageButton::setCaption(const std::string &newCaption) {
	if (!this->m_font)
		throw ElementUpdateException("Could not set caption of image button. The font is not set yet!");

	this->m_caption = newCaption;
	delete this->m_textBuffer;
	this->m_textBuffer = Renderer2D::generateTextBuffer(newCaption, this->m_font, CEDAR_ALIGNMENT_MIDDLE | CEDAR_ALIGNMENT_CENTER);
}

std::shared_ptr<Font> ImageButton::getFont() const {
	return this->m_font;
}

void ImageButton::setFont(const std::shared_ptr<Font> &newFont) {
	if (!newFont)
		throw ElementUpdateException("Could not set font of image button. The font can't be a nullptr!");

	this->m_font = newFont;
	delete this->m_textBuffer;
	this->m_textBuffer = Renderer2D::generateTextBuffer(this->m_caption, this->m_font, CEDAR_ALIGNMENT_MIDDLE | CEDAR_ALIGNMENT_CENTER);
}

Vector4f ImageButton::getDefaultCaptionColor() const {
	return this->m_defaultCaptionColor;
}

void ImageButton::setDefaultCaptionColor(const Vector4f &newColor) {
	this->m_defaultCaptionColor = newColor;
}

Vector4f ImageButton::getHoveredCaptionColor() const {
	return this->m_hoveredCaptionColor;
}

void ImageButton::setHoveredCaptionColor(const Vector4f &newColor) {
	this->m_hoveredCaptionColor = newColor;
}

Vector4f ImageButton::getPressedCaptionColor() const {
	return this->m_pressedCaptionColor;
}

void ImageButton::setPressedCaptionColor(const Vector4f &newColor) {
	this->m_pressedCaptionColor = newColor;
}

void ImageButton::render(const unsigned long currentTime)
{
	Vector4f tint(1.0f, 1.0f, 1.0f, 1.0f);
	Vector4f captionColor;
	Vector4f uvs;

	if (!this->m_enabled)
	{
		uvs = this->m_defaultUVs;
		tint = Vector4f(0.5f, 0.5f, 0.5f, 1.0f);
		captionColor = this->m_defaultCaptionColor * Vector4f(0.5f, 0.5f, 0.5f, 1.0f);
	}
	else if (this->m_pressed)
	{
		uvs = this->m_pressedUVs;
		captionColor = this->m_pressedCaptionColor;
	}
	else if (this->m_hovered)
	{
		uvs = this->m_hoveredUVs;
		captionColor = this->m_hoveredCaptionColor;
	}
	else
	{
		uvs = this->m_defaultUVs;
		captionColor = this->m_defaultCaptionColor;
	}

	Renderer2D::drawTexturedRect(this->m_posX, this->m_posY, this->m_zIndex, this->m_width, this->m_height, uvs, this->m_texture, tint);

	if (this->m_textBuffer)
		Renderer2D::drawText(this->m_posX + (this->m_width * 0.5f), this->m_posY + (this->m_height * 0.5f), this->m_zIndex, this->m_textBuffer, captionColor);
}
