//
// Created by masy on 07.03.20.
//

#ifndef CEDAR_SCREENREGISTRY_HPP
#define CEDAR_SCREENREGISTRY_HPP

#include <vector>

#include "cedar/Screen.hpp"

/**
 * Base namespace of the cedar engine.
 */
namespace cedar
{
	/**
	 * Class for handling screens.
	 */
	class ScreenRegistry
	{
	public:
		/**
		 * Gets the list of currently loaded screens.
		 *
		 * @return A constant pointer to the list of currently loaded screens.
		 */
		static const std::vector<Screen *> *getLoadedScreens();

		/**
		 * Registers the given screen.
		 *
		 * @param screen A pointer to the screen that will be registered.
		 * @return <code>true</code> if the screen was successfully registered.
		 */
		static bool registerScreen(Screen *screen);

		/**
		 * Unregisters the screen with the given name.
		 *
		 * @param name The name of the screen that will be unregistered.
		 */
		static void unregisterScreen(const std::string &name);

		/**
		 * Unregisters the given screen.
		 *
		 * @param screen A pointer to the screen that will be unregistered.
		 */
		static void unregisterScreen(Screen *screen);

		/**
		 * Gets the screen with the given name.
		 *
		 * @param name The name of the screen.
		 * @return A pointer to the screen with the given name or <code>nullptr</code> if the is no screen registered with that name.
		 */
		static Screen *getScreen(const std::string &name);

		/**
		 * Deletes all screens.
		 */
		static void cleanup();
	};
}

#endif //CEDAR_SCREENREGISTRY_HPP
