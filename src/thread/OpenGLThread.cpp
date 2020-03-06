//
// Created by masy on 06.03.20.
//

#include "cedar/OpenGLThread.h"
#include "cedar/Cedar.h"

using namespace cedar;

OpenGLThread::OpenGLThread() : Thread("OpenGLThread", 60, QUEUE_BEFORE_TICK, 256)
{
	this->m_window = nullptr;
	this->m_masterRenderer = nullptr;
	this->m_initCallback = nullptr;
	this->m_preTickCallback = nullptr;
	this->m_postTickCallback = nullptr;
	this->m_stopCallback = nullptr;
	this->m_fps = 60.0f;
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
	this->m_window = new Window("Cedar", 1280, 720, false);
	this->m_window->init(-1);

	this->m_window->setCloseCallback([]() {
		Cedar::getInstance()->stop();
	});

	this->m_masterRenderer = new MasterRenderer(this->m_window);

	if (this->m_initCallback)
		this->m_initCallback(this->m_masterRenderer);

	this->m_masterRenderer->init();
	this->m_window->show();
	this->m_nextSecond = std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::high_resolution_clock::now().time_since_epoch()).count() + 1000000;
}

void OpenGLThread::onTick(unsigned long currentTime, unsigned long tickCount)
{
	if (this->m_preTickCallback)
		this->m_preTickCallback(currentTime, tickCount);

	this->m_masterRenderer->render(currentTime, tickCount);

	if (this->m_postTickCallback)
		this->m_postTickCallback(currentTime, tickCount);

	this->m_window->update();

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
	delete this->m_window;
	delete this->m_masterRenderer;

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

void OpenGLThread::setPreTickCallback(const std::function<void(unsigned long, unsigned long)> &preTickCallback)
{
	this->m_preTickCallback = preTickCallback;
}

void OpenGLThread::setPostTickCallback(const std::function<void(unsigned long, unsigned long)> &postTickCallback)
{
	this->m_postTickCallback = postTickCallback;
}

void OpenGLThread::setStopCallback(const std::function<void()> &stopCallback)
{
	this->m_stopCallback = stopCallback;
}

