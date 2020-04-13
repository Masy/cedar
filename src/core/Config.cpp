//
// Created by masy on 06.03.20.
//

#include "cedar/Config.hpp"

using namespace cedar;

Config::Config() : Config(1280, 720, 60, -1, false, 90.0f)
{}

Config::Config(int windowWidth, int windowHeight, int fpsLimit, int selectedMonitor, bool fullscreen, float fov)
{
	this->m_windowWidth = windowWidth;
	this->m_windowHeight = windowHeight;
	this->m_fpsLimit = fpsLimit;
	this->m_selectedMonitor = selectedMonitor;
	this->m_fullscreen = fullscreen;
	this->m_fov = fov;
}

int Config::getWindowWidth() const
{
	return this->m_windowWidth;
}

void Config::setWindowWith(const int newWindowWidth)
{
	this->m_windowWidth = newWindowWidth;
}

int Config::getWindowHeight() const
{
	return this->m_windowHeight;
}

void Config::setWindowHeight(const int newWindowHeight)
{
	this->m_windowHeight = newWindowHeight;
}

int Config::getFPSLimit() const
{
	return this->m_fpsLimit;
}

void Config::setFPSLimit(const int newFPSLimit)
{
	this->m_fpsLimit = newFPSLimit;
}

int Config::getSelectedMonitor() const
{
	return this->m_selectedMonitor;
}

void Config::setSelectedMonitor(const int newSelectedMonitor)
{
	this->m_selectedMonitor = newSelectedMonitor;
}

bool Config::isFullscreen() const
{
	return this->m_fullscreen;
}

void Config::setFullscreen(const bool newFullscreen)
{
	this->m_fullscreen = newFullscreen;
}

float Config::getFOV() const
{
	return this->m_fov;
}

void Config::setFOV(const float newFOV)
{
	this->m_fov = newFOV;
}
