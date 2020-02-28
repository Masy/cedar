//
// Created by masy on 09.02.20.
//

#include "cedar/InputHandler.h"

using namespace cedar;

//---------------------------------------------------------------------------//
//                          Combination State Class                          //
//---------------------------------------------------------------------------//

KeyCombination::KeyCombination() : KeyCombination(0, nullptr)
{}

KeyCombination::KeyCombination(const unsigned int count, int *keyCodes)
{
	this->m_keyCount = count;
	this->m_keys = keyCodes;
	this->m_pressed = false;
	this->m_released = false;
	this->m_down = false;
}

KeyCombination::~KeyCombination()
{
	delete[] this->m_keys;
}

unsigned int KeyCombination::getKeyCount() const
{
	return this->m_keyCount;
}

const int *KeyCombination::getKeys() const
{
	return this->m_keys;
}

bool KeyCombination::isPressed()
{
	return this->m_pressed;
}

bool KeyCombination::isReleased()
{
	return this->m_released;
}

bool KeyCombination::isDown() const
{
	return this->m_down;
}


//---------------------------------------------------------------------------//
//                            Input Handler Class                            //
//---------------------------------------------------------------------------//

InputHandler::InputHandler(Window *window)
{
	this->m_window = window;
	this->m_combinations = std::vector<KeyCombination *>();
}

void InputHandler::update()
{
	for (KeyCombination *combination : this->m_combinations)
	{
		this->updateCombination(combination);
	}
}

void InputHandler::updateCombination(cedar::KeyCombination *combination)
{
	for (unsigned int n = 0; n < combination->getKeyCount(); n++)
	{
		if (!this->m_window->isKeyPressed(combination->m_keys[n]))
		{
			combination->m_pressed = false;
			if (combination->m_down)
				combination->m_released = true;

			combination->m_down = false;
			return;
		}
	}

	if (!combination->isDown())
	{
		combination->m_pressed = true;
		combination->m_released = false;
		combination->m_down = true;
	}
}

bool InputHandler::registerKeyCombination(KeyCombination *combination)
{
	for (KeyCombination *comb : this->m_combinations)
	{
		if (comb == combination)
		{
			return false;
		}
	}

	this->m_combinations.push_back(combination);
	return true;
}

void InputHandler::registerKeyCombinations(const unsigned int count, KeyCombination *combinations)
{
	for (unsigned int n = 0; n < count; n++)
		this->registerKeyCombination(combinations++);
}

void InputHandler::unregisterKeyCombination(const KeyCombination *combination)
{
	for (auto it = this->m_combinations.begin(); it != this->m_combinations.end(); it++)
	{
		if (*it == combination)
		{
			this->m_combinations.erase(it);
			return;
		}
	}
}
