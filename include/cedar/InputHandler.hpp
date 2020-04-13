//
// Created by masy on 09.02.20.
//

#ifndef CEDAR_INPUTHANDLER_HPP
#define CEDAR_INPUTHANDLER_HPP

#include "cedar/Vector2d.hpp"

/**
 * Base namespace of the cedar engine.
 */
namespace cedar
{
	/**
	 * Class for handling the states of keys.
	 */
	class InputHandler
	{
	private:
		/**
		 * The array where the state of each key is stored.
		 */
		unsigned char *m_keyStates;
		/**
		 * Whether the cursor is currently locked.
		 */
		bool m_cursorLocked;
		/**
		 * The x coordinate of the cursor.
		 */
		double m_cursorX;
		/**
		 * The y coordinate of the cursor.
		 */
		double m_cursorY;
		/**
		 * The offset of the cursors last x coordinate to the current x coordinate.
		 */
		double m_cursorOffsetX;
		/**
		 * The offset of the cursors last y coordinate to the current y coordinate.
		 */
		double m_cursorOffsetY;
		/**
		 * The scroll offset on the x axis.
		 */
		double m_scrollOffsetX;
		/**
		 * The scroll offset on the y axis.
		 */
		double m_scrollOffsetY;

	public:
		/**
		 * Creates a new input handler.
		 */
		InputHandler();

		/**
		 * Deletes the input handler.
		 */
		~InputHandler();

		/**
		 * Checks if the key with the given key code was released.
		 *
		 * @param keyCode The key code of the key that is checked.
		 * @return <code>true</code> if the key was released.
		 */
		[[nodiscard]] bool isKeyReleased(unsigned int keyCode) const;

		/**
		 * Checks if the key with the given key code was pressed.
		 *
		 * @param keyCode The key code of the key that is checked.
		 * @return <code>true</code> if the key was pressed.
		 */
		[[nodiscard]] bool isKeyPressed(unsigned int keyCode) const;

		/**
		 * Checks if the key with the given key code was either pressed or is held down.
		 *
		 * @param keyCode The key code of the key that is checked.
		 * @return <code>true</code> if the key was either pressed or is held down.
		 */
		[[nodiscard]] bool isKeyDown(unsigned int keyCode) const;

		/**
		 * Sets the state of the key with the given key code.
		 *
		 * @param keyCode The key code of the key that is updated.
		 * @param state The new state of the key.
		 */
		void setState(unsigned int keyCode, unsigned char state);

		/**
		 * Checks whether the cursor is locked or not.
		 *
		 * @return Whether the cursor is locked or not.
		 */
		[[nodiscard]] bool isCursorLocked() const;

		/**
		 * Sets whether the cursor is locked or not.
		 *
		 * @param locked Whether the cursor is locked or not.
		 */
		void setCursorLocked(bool locked);

		/**
		 * Gets the x coordinate of the cursor.
		 *
		 * @return The x coordinate of the cursor.
		 */
		[[nodiscard]] double getCursorX() const;

		/**
		 * Gets the y coordinate of the cursor.
		 *
		 * @return The y coordinate of the cursor.
		 */
		[[nodiscard]] double getCursorY() const;

		/**
		 * Gets the position of the cursor.
		 *
		 * @param storage A pointer to the vector the cursor position is stored in.
		 * @return A pointer to the storage vector.
		 */
		Vector2d *getCursorPos(Vector2d *storage) const;

		/**
		 * Sets the cursor position.
		 *
		 * @param cursorX The new x coordinate of the cursor.
		 * @param cursorY The new y coordinate of the cursor.
		 */
		void setCursorPos(double cursorX, double cursorY);

		/**
		 * Gets the offset of the cursor on the x axis.
		 *
		 * @return The offset of the cursor on the x axis.
		 */
		[[nodiscard]] double getCursorOffsetX() const;

		/**
		 * Gets the offset of the cursor on the y axis.
		 *
		 * @return The offset of the cursor on the y axis.
		 */
		[[nodiscard]] double getCursorOffsetY() const;

		/**
		 * Gets the offset of the cursor.
		 *
		 * @param storage A pointer to the vector where the offset is stored in.
		 * @return A pointer to the storage vector.
		 */
		Vector2d *getCursorOffset(Vector2d *storage) const;

		/**
		 * Adds the given offset the offset of the cursor.
		 *
		 * <p>This method is needed, because when the mouse is locked the cursor position does not change but we still
		 * need an offset to calculate camera rotation for example.</p>
		 *
		 * @param cursorOffsetX The offset which is added to the x axis.
		 * @param cursorOffsetY The offset which is added to the y axis.
		 */
		void addCursorOffset(double cursorOffsetX, double cursorOffsetY);

		/**
		 * Gets the scroll offset on the x axis.
		 *
		 * @return The scroll offset on the x axis.
		 */
		[[nodiscard]] double getScrollOffsetX() const;

		/**
		 * Gets the scroll offset on the y axis.
		 *
		 * @return The scroll offset on the y axis.
		 */
		[[nodiscard]] double getScrollOffsetY() const;

		/**
		 * Gets the scroll offset.
		 *
		 * @param storage A pointer to the vector where the scroll offset is stored in.
		 * @return A pointer to the storage vector.
		 */
		Vector2d *getScrollOffset(Vector2d *storage) const;

		/**
		 * Adds the given offset to the scroll offset.
		 *
		 * @param scrollOffsetX The offset which is added to the x axis.
		 * @param scrollOffsetY The offset which is added to the y axis.
		 */
		void addScrollOffset(double scrollOffsetX, double scrollOffsetY);

		/**
		 * Resets the cursor offset and scroll offset to 0.0 and all .
		 */
		void reset();
	};
}

#endif //CEDAR_INPUTHANDLER_HPP
