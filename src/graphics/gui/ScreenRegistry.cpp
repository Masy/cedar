//
// Created by masy on 07.03.20.
//

#include "cedar/ScreenRegistry.hpp"

using namespace cedar;

std::vector<Screen *> LOADED_SCREENS = std::vector<Screen *>();

const std::vector<Screen *> *ScreenRegistry::getLoadedScreens()
{
	return &LOADED_SCREENS;
}

bool ScreenRegistry::registerScreen(Screen *screen)
{
	auto lastSmallerIt = LOADED_SCREENS.begin();
	for (auto it = LOADED_SCREENS.begin(); it != LOADED_SCREENS.end(); it++)
	{
		if ((*it)->m_name == screen->m_name)
			return false;

		if (lastSmallerIt == LOADED_SCREENS.begin() && screen->getZIndex() <= (*it)->getZIndex())
			lastSmallerIt = it;
	}

	auto insertedPos = LOADED_SCREENS.insert(lastSmallerIt, screen);
	insertedPos++;
	unsigned char currentIndex = screen->getZIndex();
	while (insertedPos != LOADED_SCREENS.end())
	{
		if ((*insertedPos)->getZIndex() == currentIndex)
			(*insertedPos)->m_zIndex = ++currentIndex;

		insertedPos++;
	}
	return true;
}

void ScreenRegistry::unregisterScreen(const std::string &name)
{
	for (auto it = LOADED_SCREENS.begin(); it != LOADED_SCREENS.end(); it++)
	{
		if ((*it)->m_name == name)
		{
			LOADED_SCREENS.erase(it);
			return;
		}
	}
}

void ScreenRegistry::unregisterScreen(Screen *screen) {
	for (auto it = LOADED_SCREENS.begin(); it != LOADED_SCREENS.end(); it++)
	{
		if ((*it) == screen)
		{
			LOADED_SCREENS.erase(it);
			return;
		}
	}
}

Screen *ScreenRegistry::getScreen(const std::string &name) {
	for (auto & it : LOADED_SCREENS)
	{
		if (it->m_name == name)
		{
			return it;
		}
	}

	return nullptr;
}

void ScreenRegistry::cleanup()
{
	for (auto & it : LOADED_SCREENS)
	{
		delete it;
	}
	LOADED_SCREENS.clear();
}
