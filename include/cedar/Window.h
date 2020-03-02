//
// Created by Marcel Schauer on 26.01.20.
//

#ifndef CEDAR_WINDOW_H
#define CEDAR_WINDOW_H

#include "glad/glad.h"
#include "GLFW/glfw3.h"
#include "XException.h"
#include "Vector2d.h"
#include <functional>
#include <string>

/**
 * Base namespace of the cedar engine.
 */
namespace cedar
{

	/**
	 * Base class for all window related exceptions.
	 */
	class WindowException : public XException
	{
	public:
		/**
		 * Creates a new window exception.
		 *
		 * @param message The message of the exception.
		 */
		explicit WindowException(const std::string &message);
	};

	/**
	 * Exception which is thrown when a window could not be created.
	 */
	class WindowCreationException : public WindowException
	{
	public:
		/**
		 * Creates a new window creation exception.
		 *
		 * @param message The message of the exception.
		 */
		explicit WindowCreationException(const std::string &message);
	};

	/**
	 * Exception which is thrown when a window could not be initialized.
	 */
	class WindowInitException : public WindowException
	{
	public:
		/**
		 * Creates a new window init exception.
		 *
		 * @param message The message of the exception.
		 */
		explicit WindowInitException(const std::string &message);
	};

	/**
	 * Wrapper class for the GLFW window.
	 */
	class Window
	{
	private:
		/**
		 * A pointer to the window handle that GLFW provides.
		 */
		GLFWwindow *m_windowHandle;
		/**
		 * A pointer to the monitor the window is displayed on.
		 */
		GLFWmonitor *m_monitor;
		/**
		 * A pointer the the video mode which stores information about the monitor.
		 *
		 * <p>Note: I don't know why this isn't stored in the monitor itself, but that's GLFW</p>
		 */
		const GLFWvidmode *m_vidMode;
		/**
		 * The title of the window.
		 */
		std::string m_title;
		/**
		 * The x coordinate of the window on the desktop.
		 *
		 * <p>Note: This position is relative to the left most monitor, not the monitor the window is displayed on.</p>
		 */
		int m_posX;
		/**
		 * The y coordinate of the window on the desktop.
		 *
		 * <p>Note: This position is relative to the left most monitor, not the monitor the window is displayed on.</p>
		 */
		int m_posY;
		/**
		 * The width of the content area of the window.
		 */
		int m_width;
		/**
		 * The width of the content area of the window when it's windowed.
		 *
		 * <p>Note: This is stored separately so when exiting fullscreen mode the window can be resized back to the original width </p>
		 */
		int m_windowedWidth;
		/**
		 * Half the width of the content area of the window.
		 */
		double m_halfWidth;
		/**
		 * The height of the content area of the window.
		 */
		int m_height;
		/**
		 * The height of the content area of the window when it's windowed.
		 *
		 * <p>Note: This is stored separately so when exiting fullscreen mode the window can be resized back to the original width </p>
		 */
		int m_windowedHeight;
		/**
		 * Half the height of the content area of the window.
		 */
		double m_halfHeight;
		/**
		 * The aspect ratio of the window.
		 */
		double m_ratio;

		/**
		 * The x coordinate of the cursor relative to the top left corner of the content area of the window.
		 */
		double m_cursorPosX;
		/**
		 * The y coordinate of the cursor relative to the top left corner of the content area of the window.
		 */
		double m_cursorPosY;
		/**
		 * The distance the cursor moved on the x axis since the last time it has been polled in pixel.
		 */
		double m_cursorDistX;
		/**
		 * The distance the cursor moved on the y axis since the last time it has been polled in pixel.
		 */
		double m_cursorDistY;
		/**
		 * The amount that has been scrolled on the x axis since the last time is has been polled.
		 */
		double m_scrollOffsetX;
		/**
		 * The amount that has been scrolled on the y axis since the last time is has been polled.
		 */
		double m_scrollOffsetY;
		/**
		 * Whether the window is currently closing or not.
		 */
		bool m_closing;
		/**
		 * Whether the window is currently in fullscreen mode or in windowed.
		 */
		bool m_fullscreen;
		/**
		 * Whether the window is initialized or not.
		 */
		bool m_initialized;
		/**
		 * Whether the cursor is locked in the center of the content area or not.
		 */
		bool m_cursorLocked;

		/**
		 * The close callback of the window.
		 */
		std::function<void()> m_closeCallback;
		/**
		 * The resize callback of the window.
		 */
		std::function<void(int, int)> m_resizeCallback;

		/**
		 * Updates the monitor of the window.
		 *
		 * <p>If the window is running in borderless fullscreen mode the monitor needs to be a nullptr.
		 * This also updates the OpenGL viewport.</p>
		 *
		 * @param monitor A pointer to the new monitor of the window.
		 */
		void setWindowMonitor(GLFWmonitor *monitor);

	public:
		/**
		 * Creates a new window.
		 *
		 * @param title      A reference to the title of the window.
		 * @param width      The width of the content area of the window.
		 * @param height     The height of the content area of the window.
		 * @param fullscreen Whether the window will be in fullscreen mode when it is initialized or not.
		 */
		Window(const std::string &title, int width, int height, bool fullscreen);

		/**
		 * Destroys the window.
		 */
		~Window();

		/**
		 * Initializes the window on the selected monitor.
		 *
		 * @param selectedMonitor The index of the monitor the window will be opened on.
		 *                        <p>If it is negative the primary monitor of the operating system will be chosen</p>
		 */
		void init(int selectedMonitor);

		/**
		 * Centers the window on the current monitor.
		 */
		void centerWindow();

		/**
		 * Changes the window from borderless fullscreen to windowed.
		 */
		void setWindowed();

		/**
		 * Changes the window from windowed to borderless fullscreen.
		 */
		void setFullscreen();

		/**
		 * Centers the cursor on the content area of the window.
		 */
		void centerCursor();

		/**
		 * Shows the cursor if it is hidden.
		 *
		 * @param center Whether the cursor should be centered after it is shown.
		 */
		void showCursor(bool center);

		/**
		 * Hides the cursor if it is shown.
		 *
		 * @param center Whether the cursor should be centered after it is hidden.
		 */
		void hideCursor(bool center);

		/**
		 * Shows the window if it is hidden.
		 */
		void show();

		/**
		 * Hides the window if it is shown.
		 */
		void hide();

		/**
		 * Swaps the back buffer with the front buffer and polls events.
		 */
		void update();

		/**
		 * Initiates the closure of the window.
		 *
		 * <p>This will trigger the close callback which will handle the actual stopping of the application</p>
		 */
		void close();

		/**
		 * Sets the close callback of the window.
		 *
		 * @param callback The new close callback of the window.
		 */
		void setCloseCallback(const std::function<void()> &callback);

		/**
		 * Sets the resize callback of the window.
		 *
		 * <p>The first int is the new <code>width</code>, the second int is the new <code>height</code>.</p>
		 *
		 * @param callback The new resize callback of the window.
		 */
		void setResizeCallback(const std::function<void(int, int)> &callback);

		/**
		 * Gets the title of the window.
		 *
		 * @return The title of the window.
		 */
		[[nodiscard]] std::string getTitle() const;

		/**
		 * Sets the title of the window.
		 *
		 * @param newTitle The new title of the window.
		 */
		void setTitle(const std::string &newTitle);

		/**
		 * Checks whether the given key is pressed.
		 *
		 * @param keyCode The key code that will be checked.
		 * @return <code>true</code> if the key is pressed.
		 */
		[[nodiscard]] bool isKeyPressed(int keyCode) const;

		/**
		 * Gets the width of the window.
		 *
		 * @return the width of the window.
		 */
		[[nodiscard]] int getWidth() const;

		/**
		 * Gets the height of the window.
		 *
		 * @return the height of the window.
		 */
		[[nodiscard]] int getHeight() const;

		/**
		 * Gets the aspect ratio of the window.
		 *
		 * @return the aspect ratio of the window.
		 */
		[[nodiscard]] double getRatio() const;

		/**
		 * Checks whether the window is in fullscreen mode or in windowed.
		 *
		 * @return <code>true</code> if the window is in fullscreen mode.
		 */
		[[nodiscard]] bool isFullscreen() const;

		/**
		 * Checks if the window is about to close.
		 *
		 * @return <code>true</code> if the window is about to close.
		 */
		[[nodiscard]] bool isClosing() const;

		/**
		 * Checks if the cursor is locked.
		 *
		 * @return <code>true</code> if the cursor is locked.
		 */
		[[nodiscard]] bool isCursorLocked() const;

		/**
		 * Gets the distance the cursor has moved since the last time this method has been called.
		 *
		 * @param dest A pointer to the vector the distance is stored in.
		 */
		void getCursorDistance(Vector2d *dest);

		/**
		 * Gets the scroll amount on the x axis since the last time this method has been called.
		 *
		 * @return the scroll amount on the x axis.
		 */
		[[nodiscard]] double getScrollOffsetX();

		/**
		 * Gets the scroll amount on the y axis since the last time this method has been called.
		 *
		 * @return the scroll amount on the y axis.
		 */
		[[nodiscard]] double getScrollOffsetY();
	};

}

#endif //CEDAR_WINDOW_H
