//
// Created by masy on 08.03.20.
//

#include "cedar/Element.hpp"

using namespace cedar;

ElementException::ElementException(const std::string &message) : XException(message)
{}

ElementCreationException::ElementCreationException(const std::string &message) : ElementException(message)
{}

ElementUpdateException::ElementUpdateException(const std::string &message) : ElementException(message)
{}

Element::Element(const float originX, const float originY, const unsigned char zIndex, const float width, const float height,
				 const unsigned int alignment)
{
	this->m_originX = originX;
	this->m_originY = originY;
	this->m_zIndex = zIndex;
	this->m_width = width;
	this->m_height = height;
	this->m_alignment = alignment;
	this->m_enabled = true;
	this->m_visible = true;
	this->m_interactable = false;
	this->m_hovered = false;
	this->m_pressed = false;
	this->m_focused = false;

	if (width != 0.0f)
	{
		unsigned int horizontalAlignment = alignment & 0x03u;
		switch (horizontalAlignment)
		{
			case CEDAR_ALIGNMENT_CENTER:
				this->m_posX = originX - (width * 0.5f);
				break;

			case CEDAR_ALIGNMENT_RIGHT:
				this->m_posX = originX - width;
				break;

			default:
				this->m_posX = originX;
				break;
		}
	}

	if (height != 0.0f)
	{
		unsigned int verticalAlignment = alignment & 0x0Cu;
		switch (verticalAlignment)
		{
			case CEDAR_ALIGNMENT_MIDDLE:
				this->m_posY = originY - (height * 0.5f);
				break;

			case CEDAR_ALIGNMENT_BOTTOM:
				this->m_posY = originY - height;
				break;

			default:
				this->m_posY = originY;
				break;
		}
	}
}

Element::~Element()
= default;

float Element::getOriginX() const
{
	return this->m_originX;
}

void Element::setOriginX(const float newOriginX)
{
	float offset = newOriginX - this->m_originX;
	this->m_originX = newOriginX;
	this->m_posX += offset;
}

float Element::getOriginY() const
{
	return this->m_originY;
}

void Element::setOriginY(const float newOriginY)
{
	float offset = newOriginY - this->m_originY;
	this->m_originY = newOriginY;
	this->m_posY += offset;
}

void Element::setOrigin(float newOriginX, float newOriginY)
{
	float offsetX = newOriginX - this->m_originX;
	float offsetY = newOriginY - this->m_originY;
	this->m_originX = newOriginX;
	this->m_originY = newOriginY;
	this->m_posX += offsetX;
	this->m_posY += offsetY;

}

float Element::getPosX() const
{
	return this->m_posX;
}

void Element::setPosX(const float newPosX)
{
	float offset = newPosX - this->m_posX;
	this->m_posX = newPosX;
	this->m_originX += offset;
}

float Element::getPosY() const
{
	return this->m_posY;
}

void Element::setPosY(const float newPosY)
{
	float offset = newPosY - this->m_posY;
	this->m_posY = newPosY;
	this->m_originY += offset;
}

void Element::setPosition(const float newPosX, const float newPosY)
{
	float offsetX = newPosX - this->m_posX;
	float offsetY = newPosY - this->m_posY;
	this->m_posX = newPosX;
	this->m_posY = newPosY;
	this->m_originX += offsetX;
	this->m_originY += offsetY;
}

unsigned char Element::getZIndex() const
{
	return this->m_zIndex;
}

float Element::getWidth() const
{
	return this->m_width;
}

void Element::setWidth(const float newWidth)
{
	this->m_width = newWidth;
}

float Element::getHeight() const
{
	return this->m_height;
}

void Element::setHeight(const float newHeight)
{
	this->m_height = newHeight;
}

void Element::setSize(const float newWidth, const float newHeight)
{
	this->m_width = newWidth;
	this->m_height = newHeight;
}

unsigned int Element::getAlignment() const
{
	return this->m_alignment;
}

bool Element::isEnabled() const
{
	return this->m_enabled;
}

void Element::setEnabled(const bool enabled)
{
	this->m_enabled = enabled;
}

bool Element::isVisible() const
{
	return this->m_visible;
}

void Element::setVisibility(const bool visible)
{
	this->m_visible = visible;
}

bool Element::isInteractable() const
{
	return this->m_interactable;
}

void Element::setInteractable(const bool interactable)
{
	this->m_interactable = interactable;
}

bool Element::isHovered() const
{
	return this->m_hovered;
}

void Element::setHovered(const bool hovered)
{
	this->m_hovered = hovered;
}

bool Element::isPressed() const
{
	return this->m_pressed;
}

void Element::setPressed(const bool pressed)
{
	this->m_pressed = pressed;
}

bool Element::isFocused() const
{
	return this->m_focused;
}

void Element::setFocused(const bool focused)
{
	this->m_focused = focused;
}

std::function<void(Element *, int, unsigned int)> Element::getMousePressCallback() const
{
	return this->m_mousePressCallback;
}

void Element::setMousePressCallback(const std::function<void(Element *, int, unsigned int)> &callback)
{
	this->m_mousePressCallback = callback;
}

std::function<void(Element *, int, unsigned int)> Element::getMouseReleaseCallback() const
{
	return this->m_mouseReleaseCallback;
}

void Element::setMouseReleaseCallback(const std::function<void(Element *, int, unsigned int)> &callback)
{
	this->m_mouseReleaseCallback = callback;
}

std::function<void(Element *, float, float)> Element::getMouseMoveCallback() const
{
	return this->m_mouseMoveCallback;
}

void Element::setMouseMoveCallback(const std::function<void(Element *, float, float)> &callback)
{
	this->m_mouseMoveCallback = callback;
}

std::function<void(Element *, bool)> Element::getMouseEnterCallback() const
{
	return this->m_mouseEnterCallback;
}

void Element::setMouseEnterCallback(const std::function<void(Element *, bool)> &callback)
{
	this->m_mouseEnterCallback = callback;
}

std::function<void(Element *, float, float, unsigned int)> Element::getScrollCallback() const
{
	return this->m_scrollCallback;
}

void Element::setScrollCallback(const std::function<void(Element *, float, float, unsigned int)> &callback)
{
	this->m_scrollCallback = callback;
}

std::function<void(Element *)> Element::getInteractCallback() const
{
	return this->m_interactCallback;
}

void Element::setInteractCallback(const std::function<void(Element *)> &callback)
{
	this->m_interactCallback = callback;
}

std::function<void(Element *, int, unsigned int)> Element::getKeyPressCallback() const
{
	return this->m_keyPressCallback;
}

void Element::setKeyPressCallback(const std::function<void(Element *, int, unsigned int)> &callback)
{
	this->m_keyPressCallback = callback;
}

std::function<void(Element *, int, unsigned int)> Element::getKeyReleaseCallback() const
{
	return this->m_keyReleaseCallback;
}

void Element::setKeyReleaseCallback(const std::function<void(Element *, int, unsigned int)> &callback)
{
	this->m_keyReleaseCallback = callback;
}

std::function<void(Element *, unsigned int)> Element::getCharCallback() const
{
	return this->m_charCallback;
}

void Element::setCharCallback(const std::function<void(Element *, unsigned int)> &callback)
{
	this->m_charCallback = callback;
}

std::function<void(Element *, unsigned long, unsigned long)> Element::getUpdateCallback() const
{
	return this->m_updateCallback;
}

void Element::setUpdateCallback(const std::function<void(Element *, unsigned long, unsigned long)> &callback)
{
	this->m_updateCallback = callback;
}
