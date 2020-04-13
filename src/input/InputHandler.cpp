//
// Created by masy on 09.02.20.
//

#include "cedar/InputHandler.hpp"
#include "cedar/Input.hpp"

using namespace cedar;

InputHandler::InputHandler()
{
	this->m_keyStates = new unsigned char[CEDAR_KEY_COUNT];
	for (unsigned int n = 0; n < CEDAR_KEY_COUNT; n++)
		this->m_keyStates[n] = CEDAR_STATE_UNPRESSED;

	this->m_cursorLocked = false;
	this->m_cursorX = 0.0;
	this->m_cursorY = 0.0;
	this->m_cursorOffsetX = 0.0;
	this->m_cursorOffsetY = 0.0;
	this->m_scrollOffsetX = 0.0;
	this->m_scrollOffsetY = 0.0;
}

InputHandler::~InputHandler()
{
	delete this->m_keyStates;
}

bool InputHandler::isKeyReleased(const unsigned int keyCode) const
{
	return keyCode < CEDAR_KEY_COUNT ? this->m_keyStates[keyCode] == CEDAR_STATE_RELEASE : false;
}

bool InputHandler::isKeyPressed(unsigned int keyCode) const
{
	return keyCode < CEDAR_KEY_COUNT ? this->m_keyStates[keyCode] == CEDAR_STATE_PRESS : false;
}

bool InputHandler::isKeyDown(const unsigned int keyCode) const
{
	return keyCode < CEDAR_KEY_COUNT ? this->m_keyStates[keyCode] == CEDAR_STATE_PRESS || this->m_keyStates[keyCode] == CEDAR_STATE_DOWN : false;
}

void InputHandler::setState(const unsigned int keyCode, const unsigned char state)
{
	if (keyCode < CEDAR_KEY_COUNT)
		this->m_keyStates[keyCode] = state;
}

bool InputHandler::isCursorLocked() const
{
	return this->m_cursorLocked;
}

void InputHandler::setCursorLocked(const bool locked)
{
	this->m_cursorLocked = locked;
}

double InputHandler::getCursorX() const
{
	return this->m_cursorX;
}

double InputHandler::getCursorY() const
{
	return this->m_cursorY;
}

Vector2d *InputHandler::getCursorPos(Vector2d *storage) const
{
	*storage = Vector2d(this->m_cursorX, this->m_cursorY);
	return storage;
}

void InputHandler::setCursorPos(const double cursorX, const double cursorY)
{
	this->m_cursorOffsetX += cursorX - this->m_cursorX;
	this->m_cursorOffsetY += cursorY - this->m_cursorY;
	this->m_cursorX = cursorX;
	this->m_cursorY = cursorY;
}

double InputHandler::getCursorOffsetX() const
{
	return this->m_cursorOffsetX;
}

double InputHandler::getCursorOffsetY() const
{
	return this->m_cursorOffsetY;
}

Vector2d *InputHandler::getCursorOffset(Vector2d *storage) const
{
	*storage = Vector2d(this->m_cursorOffsetX, this->m_cursorOffsetY);
	return storage;
}

void InputHandler::addCursorOffset(const double cursorOffsetX, const double cursorOffsetY) {
	this->m_cursorOffsetX += cursorOffsetX;
	this->m_cursorOffsetY += cursorOffsetY;
}

double InputHandler::getScrollOffsetX() const
{
	return this->m_scrollOffsetX;
}

double InputHandler::getScrollOffsetY() const
{
	return this->m_scrollOffsetY;
}

Vector2d *InputHandler::getScrollOffset(cedar::Vector2d *storage) const
{
	*storage = Vector2d(this->m_scrollOffsetX, this->m_scrollOffsetY);
	return storage;
}

void InputHandler::addScrollOffset(const double scrollOffsetX, const double scrollOffsetY)
{
	this->m_scrollOffsetX += scrollOffsetX;
	this->m_scrollOffsetY += scrollOffsetY;
}

void InputHandler::reset()
{
	this->m_cursorOffsetX = 0.0;
	this->m_cursorOffsetY = 0.0;
	this->m_scrollOffsetX = 0.0;
	this->m_scrollOffsetY = 0.0;

	for (unsigned int n = 0; n < CEDAR_KEY_COUNT; n++)
	{
		if (this->m_keyStates[n] == CEDAR_STATE_PRESS)
			this->m_keyStates[n] = static_cast<unsigned char>(CEDAR_STATE_DOWN);
		else if (this->m_keyStates[n] == CEDAR_STATE_RELEASE)
			this->m_keyStates[n] = static_cast<unsigned char>(CEDAR_STATE_UNPRESSED);
	}
}
