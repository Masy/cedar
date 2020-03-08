//
// Created by masy on 06.03.20.
//

#ifndef CEDAR_ELEMENT_H
#define CEDAR_ELEMENT_H

#include <functional>

#include "cedar/InputHandler.h"
#include "cedar/GUIConstants.h"
#include "cedar/XException.h"

/**
 * Base namespace of the cedar engine.
 */
namespace cedar
{

	/**
	 * Base class for all element related exceptions.
	 */
	class ElementException : public XException
	{
	public:
		/**
		 * Creates a new element exception.
		 *
		 * @param message The message of the exception.
		 */
		explicit ElementException(const std::string &message);
	};

	/**
	 * Exception which is thrown when an element could not be created.
	 */
	class ElementCreationException : public ElementException
	{
	public:
		/**
		 * Creates a new element creation exception.
		 *
		 * @param message The message of the exception.
		 */
		explicit ElementCreationException(const std::string &message);
	};

	/**
	 * Exception which is thrown when a parameter of an element could not be updated.
	 */
	class ElementUpdateException : public ElementException
	{
	public:
		/**
		 * Creates a new element update exception.
		 *
		 * @param message The message of the exception.
		 */
		explicit ElementUpdateException(const std::string &message);
	};

	/**
	 * Base class for all gui elements.
	 *
	 * <p>The origin of the element can be in 9 positions:
	 * <ul>
	 *   <li>Top-Left</li>
	 *   <li>Top-Center</li>
	 *   <li>Top-Right</li>
	 *   <li>Middle-Left</li>
	 *   <li>Middle-Center</li>
	 *   <li>Middle-Right</li>
	 *   <li>Bottom-Left</li>
	 *   <li>Bottom-Center</li>
	 *   <li>Bottom-Right</li>
	 * </ul>
	 * Which of these the position of the origin is is defined by the {@link #m_alignment} of the element.
	 *
	 * However, the actual position of the element will always be the top-left corner.</p>
	 */
	class Element
	{
	protected:
		/**
		 * The x coordinate of the origin of the element.
		 */
		float m_originX;
		/**
		 * The y coordinate of the element.
		 */
		float m_originY;
		/**
		 * The x coordinate of the top-left corner of the element in pixel.
		 */
		float m_posX;
		/**
		 * The y coordinate of the top-left corner of the element in pixel.
		 */
		float m_posY;
		/**
		 * The z index of the element.
		 */
		unsigned char m_zIndex;
		/**
		 * The width of the element in pixel.
		 */
		float m_width;
		/**
		 * The height of the element in pixel.
		 */
		float m_height;
		/**
		 * The alignment of the element.
		 *
		 * <p>The alignment defines where it is repositioned if the size of the window changes.</p>
		 */
		unsigned int m_alignment;
		/**
		 * Whether the element is enabled or disabled.
		 *
		 * <p>A <code>disabled</code> element does not receive input events.</p>
		 */
		bool m_enabled;
		/**
		 * Whether the element is visible or not.
		 *
		 * <p>An invisible element is nor rendered and does not receive input events.</p>
		 */
		bool m_visible;
		/**
		 * Whether the element can be interacted with.
		 *
		 * <p>This will be checked before {@link #m_enabled} and does not affect how the element is rendered.</p>
		 */
		bool m_interactable;
		/**
		 * Whether the element is being hovered over.
		 */
		bool m_hovered;
		/**
		 * Whether the element is pressed down.
		 */
		bool m_pressed;
		/**
		 * Whether the element is focused.
		 */
		bool m_focused;

		/**
		 * The callback which is called when a mouse button is pressed over this element.
		 */
		std::function<void(Element *element, int mouseButton, unsigned int modifiers)> m_mousePressCallback;
		/**
		 * The callback which is called when a mouse button is released over this element.
		 */
		std::function<void(Element *element, int mouseButton, unsigned int modifiers)> m_mouseReleaseCallback;
		/**
		 * The callback which is called when this element is the {@link #PRESSED_ELEMENT pressed element} and the mouse is moved.
		 */
		std::function<void(Element *element, float cursorX, float cursorY)> m_mouseMoveCallback;
		/**
		 * The callback which is called when the mouse enters or leaves this element.
		 */
		std::function<void(Element *element, bool entered)> m_mouseEnterCallback;
		/**
		 * The callback which is called when the scroll wheel is used over this element.
		 */
		std::function<void(Element *element, float offsetX, float offsetY, unsigned int modifiers)> m_scrollCallback;
		/**
		 * The callback which is called when this element is interacted with.
		 */
		std::function<void(Element *element)> m_interactCallback;
		/**
		 * The callback which is called when this element is the {@link #FOCUSED_ELEMENT focused element} and a key is pressed.
		 */
		std::function<void(Element *element, int keyCode, unsigned int modifiers)> m_keyPressCallback;
		/**
		 * The callback which is called when this element is the {@link #FOCUSED_ELEMENT focused element} and a key is released.
		 */
		std::function<void(Element *element, int keyCode, unsigned int modifiers)> m_keyReleaseCallback;
		/**
		 * The callback which is called when this element is the {@link FOCUSED_ELEMENT focused element} and a char input is registered.
		 */
		std::function<void(Element *element, unsigned int codePoint)> m_charCallback;
		/**
		 * The callback which is called when this element is updated.
		 */
		std::function<void(Element *element, unsigned long currentTime, unsigned long tickCount)> m_updateCallback;

	public:
		/**
		 * Creates a new element.
		 *
		 * @param originX The x coordinate of the origin of the element in pixel.
		 * @param originY The y coordinate of the origin of the element in pixel.
		 * @param zIndex The z index of the element.
		 * @param width The width of the element in pixel.
		 * @param height The height of the element in pixel.
		 * @param alignment The alignment of the element.
		 */
		Element(float originX, float originY, unsigned char zIndex, float width, float height,
				unsigned int alignment = CEDAR_ALIGNMENT_TOP | CEDAR_ALIGNMENT_LEFT);

		/**
		 * Destroys the element.
		 */
		~Element();

		/**
		 * Renders the element.
		 *
		 * @param currentTime The current time of the frame in microseconds.
		 */
		virtual void render(unsigned long currentTime) = 0;

		/**
		 * Gets the x coordinate of the origin of the element.
		 *
		 * @return The x coordinate of the origin.
		 */
		[[nodiscard]] float getOriginX() const;

		/**
		 * Sets the x coordinate of the origin of the element.
		 *
		 * @param newOriginX The new x coordinate of the origin.
		 */
		virtual void setOriginX(float newOriginX);

		/**
		 * Gets the y coordinate of the origin of the element.
		 *
		 * @return The y coordinate of the origin.
		 */
		[[nodiscard]] float getOriginY() const;

		/**
		 * Sets the y coordinate of the origin of the element.
		 *
		 * @param newOriginY The new y coordinate of the origin.
		 */
		virtual void setOriginY(float newOriginY);

		/**
		 * Sets the origin of the element.
		 *
		 * @param newOriginX The new x coordinate of the origin.
		 * @param newOriginY The new y coordinate of the origin.
		 */
		virtual void setOrigin(float newOriginX, float newOriginY);

		/**
		 * Gets the x coordinate of the element.
		 *
		 * @return The x coordinate of the element.
		 */
		[[nodiscard]] float getPosX() const;

		/**
		 * Sets the x coordinate of the element.
		 *
		 * @param newPosX The new x coordinate of the element.
		 */
		virtual void setPosX(float newPosX);

		/**
		 * Gets the y coordinate of the element.
		 *
		 * @return The y coordinate of the element.
		 */
		[[nodiscard]] float getPosY() const;

		/**
		 * Sets the y coordinate of the element.
		 *
		 * @param newPosY The new y coordinate of the element.
		 */
		virtual void setPosY(float newPosY);

		/**
		 * Sets the position of the element.
		 *
		 * @param newPosX The new x coordinate of the element.
		 * @param newPosY The new y coordinate of the element.
		 */
		virtual void setPosition(float newPosX, float newPosY);

		/**
		 * Gets the z index of the element.
		 *
		 * @return The z index of the element.
		 */
		[[nodiscard]] unsigned char getZIndex() const;

		/**
		 * Gets the width of the element.
		 *
		 * @return The width of the element.
		 */
		[[nodiscard]] float getWidth() const;

		/**
		 * Sets the width of the element.
		 *
		 * @param newWidth The new width of the element.
		 */
		virtual void setWidth(float newWidth);

		/**
		 * Gets the height of the element.
		 *
		 * @return The height of the element.
		 */
		[[nodiscard]] float getHeight() const;

		/**
		 * Sets the height of the element.
		 *
		 * @param newHeight The new height of the element.
		 */
		virtual void setHeight(float newHeight);

		/**
		 * Sets the size of the element.
		 *
		 * @param newWidth The new width of the element.
		 * @param newHeight The new height of the element.
		 */
		virtual void setSize(float newWidth, float newHeight);

		/**
		 * Gets the alignment of the element.
		 *
		 * @return The alignment of the element.
		 */
		[[nodiscard]] unsigned int getAlignment() const;

		/**
		 * Checks whether the element is enabled or not.
		 *
		 * @return Whether the element is enabled or not.
		 */
		[[nodiscard]] bool isEnabled() const;

		/**
		 * Enabled or disables the element.
		 *
		 * @param enabled Whether the element will be enabled or disabled.
		 */
		void setEnabled(bool enabled);

		/**
		 * Checks whether the element is visible or not.
		 *
		 * @return Whether the element is visible or not.
		 */
		[[nodiscard]] bool isVisible() const;

		/**
		 * Sets the visibility of the element.
		 *
		 * @param visible Whether the element will be visible or not.
		 */
		void setVisibility(bool visible);

		/**
		 * Checks whether the element can be interacted with.
		 *
		 * @return Whether the element can be interacted with or not.
		 */
		[[nodiscard]] bool isInteractable() const;

		/**
		 * Sets whether the element can be interacted with.
		 *
		 * @param interactable Whether the element can be interacted with or not.
		 */
		void setInteractable(bool interactable);

		/**
		 * Checks if the element is being hovered over or not.
		 *
		 * @return Whether the element is being hovered over.
		 */
		[[nodiscard]] bool isHovered() const;

		/**
		 * Sets whether the element is being hovered over.
		 *
		 * @param hovered Whether the element is being hovered over.
		 */
		void setHovered(bool hovered);

		/**
		 * Checks if the element is pressed.
		 *
		 * @return Whether the element is pressed.
		 */
		[[nodiscard]] bool isPressed() const;

		/**
		 * Sets whether the element is pressed.
		 *
		 * @param pressed Whether the element is pressed.
		 */
		void setPressed(bool pressed);

		/**
		 * Checks if the element is focused.
		 *
		 * @return Whether the element is focused.
		 */
		[[nodiscard]] bool isFocused() const;

		/**
		 * Sets whether the element is focused.
		 *
		 * @param focused Whether the element is focused.
		 */
		void setFocused(bool focused);

		/**
		 * Gets the callback which is called when a mouse button is pressed over this element.
		 *
		 * @return The callback which is called when a mouse button is pressed over this element.
		 */
		[[nodiscard]] std::function<void(Element *element, int mouseButton, unsigned int modifiers)> getMousePressCallback() const;

		/**
		 * Sets the callback which is called when a mouse button is pressed over this element.
		 *
		 * @param callback The new callback which is called when a mouse button is pressed over this element.
		 */
		void setMousePressCallback(const std::function<void(Element *element, int mouseButton, unsigned int modifiers)> &callback);

		/**
		 * Gets the callback which is called when a mouse button is released over this element.
		 *
		 * @return The callback which is called when a mouse button is released over this element.
		 */
		[[nodiscard]] std::function<void(Element *element, int mouseButton, unsigned int modifiers)> getMouseReleaseCallback() const;

		/**
		 * Sets the callback which is called when a mouse button is released over this element.
		 *
		 * @param callback The new callback which is called when a mouse button is released over this element.
		 */
		void setMouseReleaseCallback(const std::function<void(Element *element, int mouseButton, unsigned int modifiers)> &callback);

		/**
		 * Gets the callback which is called if this element if the {@link #PRESSED_ELEMENT pressed element} and the mouse is moved.
		 *
		 * @return The callback which is called if this element if the {@link #PRESSED_ELEMENT pressed element} and the mouse is moved.
		 */
		[[nodiscard]] std::function<void(Element *element, float cursorX, float cursorY)> getMouseMoveCallback() const;

		/**
		 * Sets the callback which is called if this element if the {@link #PRESSED_ELEMENT pressed element} and the mouse is moved.
		 *
		 * @param callback The new callback which is called if this element if the {@link #PRESSED_ELEMENT pressed element} and the mouse is moved.
		 */
		void setMouseMoveCallback(const std::function<void(Element *element, float cursorX, float cursorY)> &callback);

		/**
		 * Gets the callback which is called when the mouse enters or leaves this element.
		 *
		 * @return The callback which is called when the mouse enters or leaves this element.
		 */
		[[nodiscard]] std::function<void(Element *element, bool entered)> getMouseEnterCallback() const;

		/**
		 * Sets the callback which is called when the mouse enters or leaves this element.
		 *
		 * @param callback The new callback which is called when the mouse enters or leaves this element.
		 */
		void setMouseEnterCallback(const std::function<void(Element *element, bool entered)> &callback);

		/**
		 * Gets the callback which is called when the mouse wheel is used over this element.
		 *
		 * @return The callback which is called when the mouse wheel is used over this element.
		 */
		[[nodiscard]] std::function<void(Element *element, float offsetX, float offsetY, unsigned int modifiers)> getScrollCallback() const;

		/**
		 * Sets the callback which is called when the mouse wheel is used over this element.
		 *
		 * @param callback The new callback which is called when the mouse wheel is used over this element.
		 */
		void setScrollCallback(const std::function<void(Element *element, float offsetX, float offsetY, unsigned int modifiers)> &callback);

		/**
		 * Gets the callback which is called when this element is interacted with.
		 *
		 * @return The callback which is called when the element is interacted with.
		 */
		[[nodiscard]] std::function<void(Element *element)> getInteractCallback() const;

		/**
		 * Sets the callback which is called when this element is interacted with.
		 *
		 * @param callback The new callback which is called when the element is interacted with.
		 */
		void setInteractCallback(const std::function<void(Element *element)> &callback);

		/**
		 * Gets the callback which is called when this element is the {@link #FOCUSED_ELEMENT focused element} and a key is pressed down.
		 *
		 * @return The callback which is called when this element is the {@link #FOCUSED_ELEMENT focused element} and a kes is pressed down.
		 */
		[[nodiscard]] std::function<void(Element *element, int keyCode, unsigned int modifiers)> getKeyPressCallback() const;

		/**
		 * Sets the callback which is called when this element is the {@link #FOCUSED_ELEMENT focused element} and a key is pressed down.
		 *
		 * @param callback The new callback which is called when this element is the {@link #FOCUSED_ELEMENT focused element} and a kes is pressed down.
		 */
		void setKeyPressCallback(const std::function<void(Element *element, int keyCode, unsigned int modifiers)> &callback);

		/**
		 * Gets the callback which is called when this element is the {@link #FOCUSED_ELEMENT focused element} and a key is released.
		 *
		 * @return The callback which is called when this element is the {@link #FOCUSED_ELEMENT focused element} and a key is released.
		 */
		[[nodiscard]] std::function<void(Element *element, int keyCode, unsigned int modifiers)> getKeyReleaseCallback() const;

		/**
		 * Sets the callback which is called when this element is the {@link #FOCUSED_ELEMENT focused element} and a key is released.
		 *
		 * @param callback The new callback which is called when this element is the {@link #FOCUSED_ELEMENT focused element} and a key is released.
		 */
		void setKeyReleaseCallback(const std::function<void(Element *element, int keyCode, unsigned int modifiers)> &callback);

		/**
		 * Sets the callback which is called when this element is the {@link #FOCUSED_ELEMENT focused element} and a char input is registered.
		 *
		 * @return The callback which is called when this element is the {@link #FOCUSED_ELEMENT focused element} and a char input is registered.
		 */
		[[nodiscard]] std::function<void(Element *element, unsigned int codePoint)> getCharCallback() const;

		/**
		 * Sets the callback which is called when this element is the {@link #FOCUSED_ELEMENT focused element} and a char input is registered.
		 *
		 * @param callback The new callback which is called when this element is the {@link #FOCUSED_ELEMENT focused element} and a char input is registered.
		 */
		void setCharCallback(const std::function<void(Element *element, unsigned int codePoint)> &callback);

		/**
		 * Gets the callback which is called when this element is updated.
		 *
		 * @return The callback which is called when this element is updated.
		 */
		[[nodiscard]] std::function<void(Element *element, unsigned long currentTime, unsigned long tickCount)> getUpdateCallback() const;

		/**
		 * Sets the callback which is called when this element is updated.
		 *
		 * @param callback The new callback which is called when this element is updated.
		 */
		void setUpdateCallback(const std::function<void(Element *element, unsigned long currentTime, unsigned long tickCount)> &callback);

		friend class Screen;
	};
}

#endif //CEDAR_ELEMENT_H
