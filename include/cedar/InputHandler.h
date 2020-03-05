//
// Created by masy on 09.02.20.
//

#ifndef CEDAR_INPUTHANDLER_H
#define CEDAR_INPUTHANDLER_H

#include "Window.h"
#include <vector>

/**
 * Base namespace of the cedar engine.
 */
namespace cedar
{
	/**
	 * Class for mapping multiple keys into one key combination.
	 */
	class KeyCombination
	{
	private:
		/**
		 * The number of keys of the key combination.
		 */
		unsigned int m_keyCount;
		/**
		 * A pointer to the key codes of the key combination.
		 */
		int *m_keys;
		/**
		 * Whether the key combination was pressed.
		 */
		bool m_pressed;
		/**
		 * Whether the key combination was released.
		 */
		bool m_released;
		/**
		 * Whether the key combination was held down.
		 */
		bool m_down;

	public:
		/**
		 * Creates a new empty key combination.
		 */
		KeyCombination();
		/**
		 * Creates a new key combination.
		 *
		 * @param count The number of the keys of the key combination.
		 * @param keyCodes A pointer to the array of key codes.
		 */
		explicit KeyCombination(unsigned int count, int *keyCodes);
		/**
		 * Destroys the key combination.
		 */
		~KeyCombination();

		/**
		 * Gets the number of keys of the key combination.
		 *
		 * @return the number of keys of the key combination.
		 */
		[[nodiscard]] unsigned int getKeyCount() const;
		/**
		 * Gets the key codes of the key combination.
		 *
		 * @return a constant pointer to the key codes of the key combination.
		 */
		[[nodiscard]] const int *getKeys() const;
		/**
		 * Checks whether the key combination was pressed.
		 *
		 * @return <code>true</code> if the key combination was just pressed down.
		 */
		[[nodiscard]] bool isPressed();
		/**
		 * Checks whether the key combination was released.
		 *
		 * <p>Don't mix this up with the key not being pressed. This will only return <code>true</code> if a pressed key combination was released
		 * and then return false again after the state has been polled.</p>
		 *
		 * @return <code>true</code> if the key combination was just released.
		 */
		[[nodiscard]] bool isReleased();
		/**
		 * Checks whether the key combination is held down.
		 *
		 * @return <code>true</code> if the key combination is held down.
		 */
		[[nodiscard]] bool isDown() const;

		friend class InputHandler;
	};

	/**
	 * Class for handling the states of key combinations.
	 */
	class InputHandler
	{
	private:
		/**
		 * A pointer to the window.
		 */
		Window *m_window;
		/**
		 * A vector storing all key combinations that are updated.
		 */
		std::vector<KeyCombination*> m_combinations;

		/**
		 * Updates the states of the given key combination.
		 *
		 * @param combination A pointer to the key combination that will be updated.
		 */
		void updateCombination(KeyCombination *combination);
	public:
		/**
		 * Creates a new input handler.
		 *
		 * @param window A pointer to the window.
		 */
		explicit InputHandler(Window *window);

		/**
		 * Updates all currently registered key combinations.
		 */
		void update();

		/**
		 * Registers a new key combination.
		 *
		 * @param combination A pointer to the key combination that will be registered.
		 * @return <code>true</code> if the key combination was successfully registered.
		 */
		bool registerKeyCombination(KeyCombination *combination);
		/**
		 * Registers multiple key combinations at once.
		 *
		 * @param count The number of key combinations in the provided array.
		 * @param combinations A pointer to the array of key combinations that will be registered.
		 */
		void registerKeyCombinations(unsigned int count, KeyCombination *combinations);
		/**
		 * Unregisters a key combinations.
		 *
		 * @param combination A pointer to the key combination that will be unregistered.
		 */
		void unregisterKeyCombination(const KeyCombination *combination);
	};
}

#endif //CEDAR_INPUTHANDLER_H
