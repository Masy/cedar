//
// Created by Marcel on 27.01.20.
//

#include "cedar/Window.h"
#include <iostream>

using namespace cedar;

WindowException::WindowException(const std::string &message) : XException(message)
{}

WindowCreationException::WindowCreationException(const std::string &message) : WindowException(message)
{}

WindowInitException::WindowInitException(const std::string &message) : WindowException(message)
{}

Window::Window(const std::string &title, const int width, const int height, const bool fullscreen)
{
	if (width <= 0 || height <= 0)
		throw WindowCreationException("Could not create window. Width and height must be greater than 0!");

	this->m_title = title;
	this->m_posX = 0;
	this->m_posY = 0;
	this->m_width = width;
	this->m_windowedWidth = width;
	this->m_halfWidth = width * 0.5;
	this->m_height = height;
	this->m_windowedHeight = height;
	this->m_halfHeight = height * 0.5;
	this->m_ratio = width / (double) height;
	this->m_cursorPosX = this->m_halfWidth;
	this->m_cursorPosY = this->m_halfHeight;
	this->m_cursorDistX = 0.0;
	this->m_cursorDistY = 0.0;
	this->m_closing = false;
	this->m_fullscreen = fullscreen;
	this->m_initialized = false;
	this->m_cursorLocked = false;
	this->m_windowHandle = nullptr;
	this->m_monitor = nullptr;
	this->m_vidMode = nullptr;
}

Window::~Window()
{
	glfwDestroyWindow(this->m_windowHandle);
	glfwTerminate();
}

void Window::init(const int selectedMonitor)
{
	if (this->m_initialized)
		throw WindowInitException("Could not initialize window. Window is already initialized!");

	if (!glfwInit())
		throw WindowInitException("Could not initialize window. GLFW could not be initialized!");

	glfwWindowHint(GLFW_VISIBLE, GLFW_FALSE);
	glfwWindowHint(GLFW_SAMPLES, 4);

	if (selectedMonitor > 0)
	{
		int monitorCount;
		GLFWmonitor **monitors = glfwGetMonitors(&monitorCount);

		if (monitorCount == 0 || monitors == nullptr)
		{
			throw WindowCreationException("Could not create window. Haven't found any monitors..?");
		}

		if (selectedMonitor >= monitorCount)
		{
			std::cout << "couldn't find selected monitor, using primary monitor!" << std::endl;
		}
		else
		{
			this->m_monitor = monitors[selectedMonitor];
		}
	}

	if (!this->m_monitor)
		this->m_monitor = glfwGetPrimaryMonitor();

	this->m_vidMode = glfwGetVideoMode(this->m_monitor);

	this->m_windowHandle = glfwCreateWindow(this->m_width, this->m_height, this->m_title.c_str(), this->m_fullscreen ? this->m_monitor : nullptr, nullptr);
	if (this->m_windowHandle == nullptr)
		throw WindowInitException("Could not initialize window. Couldn't create window handle!");

	glfwSetWindowUserPointer(this->m_windowHandle, reinterpret_cast<void *>(this));

	glfwSetWindowSizeCallback(this->m_windowHandle, [](GLFWwindow *glfwWindow, int width, int height) {
		Window *window = reinterpret_cast<Window *>(glfwGetWindowUserPointer(glfwWindow));
		window->m_width = width;
		window->m_height = height;
		window->m_halfWidth = width * 0.5;
		window->m_halfHeight = height * 0.5;
		if (!window->m_fullscreen)
		{
			window->m_windowedWidth = width;
			window->m_windowedHeight = height;
		}
		window->m_ratio = width / (double) height;
		glViewport(0, 0, width, height);
		if (window->m_resizeCallback)
			window->m_resizeCallback(width, height);
	});

	glfwSetCursorPosCallback(this->m_windowHandle, [](GLFWwindow *glfwWindow, double cursorX, double cursorY) {
		Window *window = reinterpret_cast<Window *>(glfwGetWindowUserPointer(glfwWindow));


		window->m_cursorDistX += cursorX - window->m_cursorPosX;
		window->m_cursorDistY += cursorY - window->m_cursorPosY;
		window->m_cursorPosX = cursorX;
		window->m_cursorPosY = cursorY;

		if (window->m_cursorLocked)
		{
			glfwSetCursorPos(glfwWindow, window->m_cursorPosX, window->m_cursorPosY);
		}
	});

	glfwSetScrollCallback(this->m_windowHandle, [](GLFWwindow *glfwWindow, double offsetX, double offsetY) {
		Window *window = reinterpret_cast<Window *>(glfwGetWindowUserPointer(glfwWindow));
		window->m_scrollOffsetX += offsetX;
		window->m_scrollOffsetY += offsetY;
	});

	glfwMakeContextCurrent(this->m_windowHandle);
	gladLoadGL();

	this->m_initialized = true;
	this->centerWindow();
}

void Window::setWindowMonitor(GLFWmonitor *monitor)
{
	int posX;
	int posY;

	glfwGetMonitorPos(this->m_monitor, &posX, &posY);

	posX += (this->m_vidMode->width - this->m_width) / 2;
	posY += (this->m_vidMode->height - this->m_height) / 2;

	glfwSetWindowMonitor(this->m_windowHandle, monitor, posX, posY, this->m_width, this->m_height, GLFW_DONT_CARE);
	glViewport(0, 0, this->m_width, this->m_height);
}

void Window::centerWindow()
{
	if (this->m_initialized)
	{
		int monitorPosX;
		int monitorPosY;
		glfwGetMonitorPos(this->m_monitor, &monitorPosX, &monitorPosY);

		this->m_posX = monitorPosX + ((this->m_vidMode->width - this->m_width) / 2);
		this->m_posY = monitorPosY + ((this->m_vidMode->height - this->m_height) / 2);
		glfwSetWindowPos(this->m_windowHandle, this->m_posX, this->m_posY);
	}
}

void Window::setWindowed()
{
	if (this->m_initialized && this->m_fullscreen)
	{
		this->m_width = this->m_windowedWidth;
		this->m_halfWidth = this->m_windowedWidth * 0.5;
		this->m_height = this->m_windowedHeight;
		this->m_halfHeight = this->m_windowedHeight * 0.5;

		this->setWindowMonitor(nullptr);
		this->m_fullscreen = false;
		glfwFocusWindow(this->m_windowHandle);
	}
}

void Window::setFullscreen()
{
	if (this->m_initialized && !this->m_fullscreen)
	{
		this->m_width = this->m_vidMode->width;
		this->m_halfWidth = this->m_vidMode->width * 0.5;
		this->m_height = this->m_vidMode->height;
		this->m_halfHeight = this->m_vidMode->height * 0.5;

		this->setWindowMonitor(this->m_monitor);
		this->m_fullscreen = true;
		glfwFocusWindow(this->m_windowHandle);
	}
}

void Window::centerCursor()
{
	if (this->m_initialized)
		glfwSetCursorPos(this->m_windowHandle, this->m_halfWidth, this->m_halfHeight);
}

void Window::showCursor(const bool center)
{
	if (this->m_initialized && this->m_cursorLocked)
	{
		glfwSetInputMode(this->m_windowHandle, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
		this->m_cursorLocked = false;
		this->m_cursorDistX = 0.0;
		this->m_cursorDistY = 0.0;
		if (center)
			this->centerCursor();
	}
}

void Window::hideCursor(const bool center)
{
	if (this->m_initialized && !this->m_cursorLocked)
	{
		glfwSetInputMode(this->m_windowHandle, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
		this->m_cursorLocked = true;
		this->m_cursorDistX = 0.0;
		this->m_cursorDistY = 0.0;
		if (center)
			this->centerCursor();
	}
}

void Window::show()
{
	if (this->m_initialized)
		glfwShowWindow(this->m_windowHandle);
}

void Window::hide()
{
	if (this->m_initialized)
		glfwHideWindow(this->m_windowHandle);
}

void Window::update()
{
	if (this->m_initialized && !this->m_closing)
	{
		glfwSwapBuffers(this->m_windowHandle);
		glfwPollEvents();
	}
}

void Window::close()
{
	if (this->m_initialized && !this->m_closing)
	{
		this->m_closing = true;
		glfwSetWindowShouldClose(this->m_windowHandle, true);
	}
}

void Window::setCloseCallback(const std::function<void()> &callback)
{
	this->m_closeCallback = callback;
	glfwSetWindowCloseCallback(this->m_windowHandle, [](GLFWwindow *window) {
		reinterpret_cast<Window *>(glfwGetWindowUserPointer(window))->m_closeCallback();
	});
}

void Window::setResizeCallback(const std::function<void (int, int)> &callback) {
	this->m_resizeCallback = callback;
}

bool Window::isKeyPressed(const int keyCode) const
{
	if (keyCode < 8)
		return glfwGetMouseButton(this->m_windowHandle, keyCode) == GLFW_PRESS;
	else
		return glfwGetKey(this->m_windowHandle, keyCode) == GLFW_PRESS;
}

int Window::getWidth() const
{
	return this->m_width;
}

int Window::getHeight() const
{
	return this->m_height;
}

double Window::getRatio() const
{
	return this->m_ratio;
}

bool Window::isFullscreen() const
{
	return this->m_fullscreen;
}

bool Window::isClosing() const
{
	return this->m_closing;
}

bool Window::isCursorLocked() const
{
	return this->m_cursorLocked;
}

void Window::getCursorDistance(Vector2d *dest) {
	dest->x = this->m_cursorDistX;
	dest->y = this->m_cursorDistY;

	this->m_cursorDistX = 0.0;
	this->m_cursorDistY = 0.0;
}

double Window::getScrollOffsetX() {
	double old = this->m_scrollOffsetX;
	this->m_scrollOffsetX = 0.0;
	return old;
}

double Window::getScrollOffsetY() {
	double old = this->m_scrollOffsetY;
	this->m_scrollOffsetY = 0.0;
	return old;
}
