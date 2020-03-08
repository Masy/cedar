//
// Created by masy on 06.03.20.
//

#ifndef CEDAR_SCREEN_H
#define CEDAR_SCREEN_H

#include <vector>

#include "cedar/Element.h"

/**
 * Base namespace of the cedar engine.
 */
namespace cedar
{

	/**
	 * Base class for all screen related exceptions.
	 */
	class ScreenException : public XException
	{
	public:
		/**
		 * Creates a new screen exception.
		 *
		 * @param message The message of the exception.
		 */
		explicit ScreenException(const std::string &message);
	};

	/**
	 * Exception which is thrown when a screen could not be created.
	 */
	class ScreenCreationException : public ScreenException
	{
	public:
		/**
		 * Creates a new screen creation exception.
		 *
		 * @param message The message of the exception.
		 */
		explicit ScreenCreationException(const std::string &message);
	};

	/**
	 * Exception which is thrown when an element could not be added.
	 */
	class ElementAddException : public ScreenException
	{
	public:
		explicit ElementAddException(const std::string &message);
	};

	/**
	 * Class representing a graphical user interface.
	 */
	class Screen
	{
	protected:
		/**
		 * The name of the screen.
		 */
		std::string m_name;
		/**
		 * The z index of the screen.
		 *
		 * <p>If a screen receives an input event when the mouse is over an element of the screen, other
		 * screens will not be checked if they should receive an input event as well. The screen with the
		 * lowest z index will be checked first, and if no element was interacted with, the screen with
		 * the next lowest z index will be checked.</p>
		 */
		unsigned char m_zIndex;
		/**
		 * Whether the screen is enabled or disabled.
		 *
		 * <p>A <code>disabled</code> screen does not receive input events.</p>
		 */
		bool m_enabled;
		/**
		 * Whether the screen is visible or not.
		 *
		 * <p>An invisible screen is not rendered and does not receive input events.</p>
		 */
		bool m_visible;
		/**
		 * List with pointers to all elements inside the screen.
		 */
		std::vector<Element*> m_elements;

	public:
		/**
		 * A pointer to the element that is currently being hovered over.
		 */
		static Element *HOVERED_ELEMENT;
		/**
		 * A pointer to the element that is currently being pressed down.
		 */
		static Element *PRESSED_ELEMENT;
		/**
		 * A pointer to the element that is currently focused.
		 */
		static Element *FOCUSED_ELEMENT;

		/**
		 * Creates a new screen.
		 *
		 * <p>If there is a screen with the same z index already, the z index of the other screen
		 * will be increased by one. Then the screen with the next highest z index will be checked
		 * and the process repeats until there are no duplicate z indices.</p>
		 *
		 * @param name The name of the screen.
		 * @param zIndex The desired z index of the screen.
		 *               <p>It is not guaranteed that this will stay the z index of the screen.</p>
		 *
		 * @throws ScreenCreationException if the <code>name</code> is empty.
		 */
		Screen(const std::string &name, unsigned char zIndex);

		/**
		 * Method which is called when a mouse button is pressed down.
		 *
		 * @param cursorX The current x coordinate of the cursor.
		 * @param cursorY The current y coordinate of the cursor.
		 * @param mouseButton The mouse button which was pressed down.
		 * @param modifiers A bit mask containing information about which modifier keys were also pressed down.
		 * @return <code>true</code> if there was an element at the coordinates of the cursor.
		 */
		bool onMousePress(float cursorX, float cursorY, int mouseButton, unsigned int modifiers);

		/**
		 * Method which is called when a mouse button is released.
		 *
		 * @param cursorX The current x coordinate of the cursor.
		 * @param cursorY The current y coordinate of the cursor.
		 * @param mouseButton The mouse button which was released.
		 * @param modifiers A bit mask containing information about which modifier keys were also pressed down.
		 * @return <code>true</code> if there was an element at the coordinates of the cursor.
		 */
		bool onMouseRelease(float cursorX, float cursorY, int mouseButton, unsigned int modifiers);

		/**
		 * Method which is called when the mouse is moved.
		 *
		 * @param cursorX The new x coordinate of the cursor.
		 * @param cursorY The new y coordinate of the cursor.
		 * @return <code>true</code> if this screen has a focused element which handled the mouse move event.
		 */
		bool onMouseMove(float cursorX, float cursorY);

		/**
		 * Method which is called when the mouse wheel is scrolled.
		 *
		 * @param cursorX The current x coordinate of the cursor.
		 * @param cursorY The current y coordinate of the cursor.
		 * @param offsetX The scroll amount on the x axis.
		 * @param offsetY The scroll amount on the y axis.
		 * @param modifiers A bit mask containing information about which modifier keys were also pressed down.
		 * @return <code>true</code> if there was an element at the coordinates of the cursor.
		 */
		bool onScroll(float cursorX, float cursorY, float offsetX, float offsetY, unsigned int modifiers);

		/**
		 * Method which is called when the window is resized.
		 *
		 * @param width The new width of the window.
		 * @param height The new height of the window.
		 * @param deltaWidth The difference between the new and the old width.
		 * @param deltaHeight The difference between the new and the old height.
		 */
		void onResize(int width, int height, int deltaWidth, int deltaHeight);

		/**
		 * Method which updates all elements in the screen.
		 *
		 * @param currentTime The current time of the frame in microseconds.
		 * @param tickCount The current tick count.
		 */
		void onUpdate(unsigned long currentTime, unsigned long tickCount);

		/**
		 * Renders all elements of the screen that are visible.
		 *
		 * @param currentTime The current time of the frame in microseconds.
		 */
		virtual void render(unsigned long currentTime);

		/**
		 * Adds the element to the screen.
		 *
		 * @param element A pointer to the element that will be added to the screen.
		 *
		 * @throws ElementAddException if <code>element</code> is a <code>nullptr</code>.
		 */
		void addElement(Element *element);

		/**
		 * Gets the name of the screen.
		 *
		 * @return The name of the screen.
		 */
		[[nodiscard]] std::string getName() const;

		/**
		 * Gets the z index of the screen.
		 *
		 * @return The z index of the screen.
		 */
		[[nodiscard]] unsigned char getZIndex() const;

		/**
		 * Checks whether the screen is enabled or not.
		 *
		 * @return Whether the screen is enabled or not.
		 */
		[[nodiscard]] bool isEnabled() const;

		/**
		 * Enables or disabled the screen.
		 *
		 * @param enabled Whether the screen will be enabled or disabled.
		 */
		void setEnabled(bool enabled);

		/**
		 * Checks whether the screen is visible or not.
		 *
		 * @return Whether the screen is visible or not.
		 */
		[[nodiscard]] bool isVisible() const;

		/**
		 * Sets the visibility of the screen.
		 *
		 * @param visible Whether the screen will be visible or not.
		 */
		void setVisibility(bool visible);

		friend class ScreenRegistry;
	};
}

#endif //CEDAR_SCREEN_H
