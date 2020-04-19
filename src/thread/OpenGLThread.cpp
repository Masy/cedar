//
// Created by masy on 06.03.20.
//

#include <cedar/TextureRegistry.hpp>
#include <cedar/FontRegistry.hpp>
#include <cedar/ScreenRegistry.hpp>
#include <cedar/ModelRegistry.hpp>
#include "cedar/OpenGLThread.hpp"
#include "cedar/Cedar.hpp"

using namespace cedar;

OpenGLThread::OpenGLThread() : Thread("OpenGLThread", static_cast<float>(Cedar::getConfig()->getFPSLimit()),
									  QUEUE_BEFORE_TICK, 256)
{
	this->m_window = nullptr;
	this->m_inputHandler = nullptr;
	this->m_masterRenderer = nullptr;
	this->m_initCallback = nullptr;
	this->m_inputCallback = nullptr;
	this->m_postRenderCallback = nullptr;
	this->m_stopCallback = nullptr;
	this->m_fps = static_cast<float>(Cedar::getConfig()->getFPSLimit());
	this->m_frameTimes = 0.0;
	this->m_frameCount = 0;
	this->m_nextSecond = 0;
}

OpenGLThread *OpenGLThread::getInstance()
{
	static OpenGLThread *instance = new OpenGLThread();
	return instance;
}

void OpenGLThread::onStart()
{
	const Config *config = Cedar::getConfig();
	this->m_window = new Window("", config->getWindowWidth(), config->getWindowHeight(), config->isFullscreen());
	this->m_window->init(config->getSelectedMonitor());
	this->m_inputHandler = this->m_window->getInputHandler();

	this->m_window->setCloseCallback([]() {
		Cedar::getInstance()->stop();
	});

	this->m_masterRenderer = new MasterRenderer(this->m_window);
	this->m_window->setResizeCallback([=](int newWidth, int newHeight) {
		this->m_masterRenderer->onResize();
	});

	if (this->m_initCallback)
		this->m_initCallback(this->m_masterRenderer);

	this->m_masterRenderer->init();
	this->m_window->show();
	this->m_nextSecond = std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::high_resolution_clock::now().time_since_epoch()).count() + 1000000;
}

void OpenGLThread::onTick(unsigned long currentTime, unsigned long tickCount)
{
	if (this->m_inputCallback)
		this->m_inputCallback(currentTime, tickCount, this->m_inputHandler);

	this->m_masterRenderer->render(currentTime, tickCount);

	if (this->m_postRenderCallback)
		this->m_postRenderCallback(currentTime, tickCount);

	this->m_window->update(currentTime, tickCount);

	this->m_frameCount++;
	this->m_frameTimes += this->m_frameTime;
	if (currentTime >= this->m_nextSecond)
	{
		this->m_fps = static_cast<float>(1.0 / (this->m_frameTimes / this->m_frameCount));
		this->m_frameTimes = 0.0;
		this->m_frameCount = 0;
		this->m_nextSecond = currentTime + 1000000;
	}
}

void OpenGLThread::onStop()
{
	this->m_window->close();
	// First delete the master renderer and then the window because the window will destroy the context causing segfaults
	// when trying to delete GL objects.
	delete this->m_masterRenderer;
	ScreenRegistry::cleanup();
	ModelRegistry::cleanup();
	TextureRegistry::cleanup();
	FontRegistry::cleanup();
	delete this->m_window;

	if (this->m_stopCallback)
		this->m_stopCallback();
}

Window *OpenGLThread::getWindow() const
{
	return this->m_window;
}

MasterRenderer *OpenGLThread::getMasterRenderer() const
{
	return this->m_masterRenderer;
}

float OpenGLThread::getFPS() const
{
	return this->m_fps;
}

void OpenGLThread::setInitCallback(const std::function<void(MasterRenderer *)> &initCallback)
{
	this->m_initCallback = initCallback;
}

void OpenGLThread::setInputCallback(const std::function<void(unsigned long, unsigned long, const InputHandler *)> &inputCallback)
{
	this->m_inputCallback = inputCallback;
}

void OpenGLThread::setPostRenderCallback(const std::function<void(unsigned long, unsigned long)> &postRenderCallback)
{
	this->m_postRenderCallback = postRenderCallback;
}

void OpenGLThread::setStopCallback(const std::function<void()> &stopCallback)
{
	this->m_stopCallback = stopCallback;
}

