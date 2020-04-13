//
// Created by masy on 08.03.20.
//

#include "cedar/Screen.hpp"
#include "cedar/Intersection.hpp"
#include "cedar/Input.hpp"

using namespace cedar;

ScreenException::ScreenException(const std::string &message) : XException(message)
{}

ScreenCreationException::ScreenCreationException(const std::string &message) : ScreenException(message)
{}

ElementAddException::ElementAddException(const std::string &message) : ScreenException(message)
{}

Element *Screen::HOVERED_ELEMENT = nullptr;
Element *Screen::PRESSED_ELEMENT = nullptr;
Element *Screen::FOCUSED_ELEMENT = nullptr;

Screen::Screen(const std::string &name, const unsigned char zIndex)
{
	if (name.empty())
		throw ScreenCreationException("Could not create screen. The name can't be empty!");

	this->m_name = name;
	this->m_zIndex = zIndex;
	this->m_enabled = true;
	this->m_visible = false;
}

bool Screen::onMousePress(const float cursorX, const float cursorY, const int mouseButton, const unsigned int modifiers)
{
	for (Element *currElement : this->m_elements)
	{
		// If the element is not visible it can't be interacted with (who would have guessed? not me!)
		if (currElement->isInteractable() && currElement->isVisible()
			&& intersection::isPointInsideRectangle2Df(currElement->getPosX(), currElement->getPosY(),
													   currElement->getPosX() + currElement->getWidth(),
													   currElement->getPosY() + currElement->getHeight(),
													   cursorX, cursorY))
		{
			// If the element is disabled it can't be interacted with but still blocks element behind it to be interacted with
			if (currElement->isEnabled())
			{
				if (mouseButton == CEDAR_MOUSE_BUTTON_LEFT)
				{
					PRESSED_ELEMENT = currElement;
					currElement->setPressed(true);
				}

				if (currElement->getMousePressCallback())
					currElement->getMousePressCallback()(currElement, mouseButton, modifiers);

				return true;
			}
			else
			{
				return false;
			}
		}
	}

	return false;
}

bool Screen::onMouseRelease(const float cursorX, const float cursorY, const int mouseButton, const unsigned int modifiers)
{
	for (Element *currElement : this->m_elements)
	{
		// If the element is not visible it can't be interacted with (who would have guessed? not me!)
		if (currElement->isInteractable() && currElement->isVisible()
			&& intersection::isPointInsideRectangle2Df(currElement->getPosX(), currElement->getPosY(),
													   currElement->getPosX() + currElement->getWidth(),
													   currElement->getPosY() + currElement->getHeight(),
													   cursorX, cursorY))
		{
			// If the element is disabled it can't be interacted with but still blocks element behind it to be interacted with
			if (currElement->isEnabled())
			{
				if (mouseButton == CEDAR_MOUSE_BUTTON_LEFT && PRESSED_ELEMENT == currElement)
				{
					currElement->setPressed(false);
					FOCUSED_ELEMENT = currElement;

					if (currElement->getInteractCallback())
						currElement->getInteractCallback()(currElement);
				}

				if (currElement->getMouseReleaseCallback())
					currElement->getMouseReleaseCallback()(currElement, mouseButton, modifiers);

				return true;
			}
			else
			{
				if (PRESSED_ELEMENT)
				{
					PRESSED_ELEMENT->setPressed(false);
					PRESSED_ELEMENT = nullptr;
				}
				return false;
			}
		}
	}

	if (PRESSED_ELEMENT)
	{
		PRESSED_ELEMENT->setPressed(false);
		PRESSED_ELEMENT = nullptr;
	}

	FOCUSED_ELEMENT = nullptr;
	return false;
}

bool Screen::onMouseMove(const float cursorX, const float cursorY)
{
	Element *newHovered = nullptr;

	for (Element *currElement : this->m_elements)
	{
		// If the element is not visible it can't be interacted with (who would have guessed? not me!)
		if (currElement->isInteractable() && currElement->isVisible()
			&& intersection::isPointInsideRectangle2Df(currElement->getPosX(), currElement->getPosY(),
													   currElement->getPosX() + currElement->getWidth(),
													   currElement->getPosY() + currElement->getHeight(),
													   cursorX, cursorY))
		{
			// If the element is disabled it can't be interacted with but still blocks element behind it to be interacted with
			if (currElement->isEnabled())
			{
				newHovered = currElement;

				if (newHovered != HOVERED_ELEMENT)
				{
					if (HOVERED_ELEMENT)
					{
						HOVERED_ELEMENT->setHovered(false);
						if (HOVERED_ELEMENT->getMouseEnterCallback())
							HOVERED_ELEMENT->getMouseEnterCallback()(HOVERED_ELEMENT, false);
					}

					currElement->setHovered(true);
					if (currElement->getMouseEnterCallback())
						currElement->getMouseEnterCallback()(currElement, true);

					HOVERED_ELEMENT = newHovered;
				}

				return true;
			}
			else
			{
				return false;
			}
		}
	}

	if (HOVERED_ELEMENT)
	{
		HOVERED_ELEMENT->setHovered(false);
		if (HOVERED_ELEMENT->getMouseEnterCallback())
			HOVERED_ELEMENT->getMouseEnterCallback()(HOVERED_ELEMENT, false);

		HOVERED_ELEMENT = nullptr;
	}

	// Only the pressed element receives move events
	return false;
}

bool Screen::onScroll(const float cursorX, const float cursorY, const float offsetX, const float offsetY, const unsigned int modifiers)
{
	for (Element *currElement : this->m_elements)
	{
		// If the element is not visible it can't be interacted with (who would have guessed? not me!)
		if (currElement->isInteractable() && currElement->isVisible()
			&& intersection::isPointInsideRectangle2Df(currElement->getPosX(), currElement->getPosY(),
													   currElement->getPosX() + currElement->getWidth(),
													   currElement->getPosY() + currElement->getHeight(),
													   cursorX, cursorY))
		{
			// If the element is disabled it can't be interacted with but still blocks element behind it to be interacted with
			if (currElement->isEnabled())
			{
				if (currElement->getScrollCallback())
					currElement->getScrollCallback()(currElement, offsetX, offsetY, modifiers);

				return true;
			}
			else
			{
				return false;
			}
		}
	}

	return false;
}

void Screen::onResize(const int width, const int height, const int deltaWidth, const int deltaHeight)
{
	float halfDeltaWidth = static_cast<float>(deltaWidth) * 0.5f;
	float halfDeltaHeight = static_cast<float>(deltaHeight) * 0.5f;
	for (Element *currElement : this->m_elements)
	{
		unsigned int horizontalAlignment = currElement->getAlignment() & 0x03u;
		unsigned int verticalAlignment = currElement->getAlignment() & 0x0Cu;

		float newPosX;
		float newPosY;

		switch (horizontalAlignment)
		{
			case CEDAR_ALIGNMENT_CENTER:
				newPosX = currElement->getPosX() + halfDeltaWidth;
				break;

			case CEDAR_ALIGNMENT_RIGHT:
				newPosX = currElement->getPosX() + static_cast<float>(deltaWidth);
				break;

			default:
				newPosX = currElement->getPosX();
				break;
		}

		switch (verticalAlignment)
		{
			case CEDAR_ALIGNMENT_MIDDLE:
				newPosY = currElement->getPosY() + halfDeltaHeight;
				break;

			case CEDAR_ALIGNMENT_BOTTOM:
				newPosY = currElement->getPosY() + static_cast<float>(deltaHeight);
				break;

			default:
				newPosY = currElement->getPosY();
				break;
		}

		currElement->setPosition(newPosX, newPosY);
	}
}

void Screen::onUpdate(unsigned long currentTime, unsigned long tickCount) {
	for (Element *element : this->m_elements)
	{
		if (element->getUpdateCallback())
			element->getUpdateCallback()(element, currentTime, tickCount);
	}
}

void Screen::render(const unsigned long currentTime)
{
	for (auto it = this->m_elements.rbegin(); it != this->m_elements.rend(); it++)
	{
		if ((*it)->isVisible())
		{
			(*it)->render(currentTime);
		}
	}
}

void Screen::addElement(Element *element) {
	if (!element)
		throw ElementAddException("Could not add element to the screen. The element can't be a nullptr!");

	auto lastSmallerIt = this->m_elements.begin();
	for (auto it = this->m_elements.begin(); it != this->m_elements.end(); it++)
	{
		if ((*it) == element)
			return;

		if (lastSmallerIt == this->m_elements.begin() && element->getZIndex() <= (*it)->getZIndex())
			lastSmallerIt = it;
	}

	this->m_elements.insert(lastSmallerIt, element);
}

std::string Screen::getName() const
{
	return this->m_name;
}

unsigned char Screen::getZIndex() const
{
	return this->m_zIndex;
}

bool Screen::isEnabled() const
{
	return this->m_enabled;
}

void Screen::setEnabled(const bool enabled)
{
	this->m_enabled = enabled;
	if (!enabled)
	{
		for (Element *element : this->m_elements)
		{
			element->setHovered(false);
			element->setPressed(false);
			element->setFocused(false);

			if (HOVERED_ELEMENT == element)
				HOVERED_ELEMENT = nullptr;

			if (PRESSED_ELEMENT == element)
				PRESSED_ELEMENT = nullptr;

			if (FOCUSED_ELEMENT == element)
				FOCUSED_ELEMENT = nullptr;
		}
	}
}

bool Screen::isVisible() const
{
	return this->m_visible;
}

void Screen::setVisibility(const bool visible)
{
	this->m_visible = visible;

	if (!visible)
	{
		for (Element *element : this->m_elements)
		{
			element->setHovered(false);
			element->setPressed(false);
			element->setFocused(false);

			if (HOVERED_ELEMENT == element)
				HOVERED_ELEMENT = nullptr;

			if (PRESSED_ELEMENT == element)
				PRESSED_ELEMENT = nullptr;

			if (FOCUSED_ELEMENT == element)
				FOCUSED_ELEMENT = nullptr;
		}
	}
}
