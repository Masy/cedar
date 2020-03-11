//
// Created by masy on 06.03.20.
//

#include "cedar/EngineThread.h"

using namespace cedar;

EngineThread::EngineThread() : Thread("EngineThread", 20, QUEUE_BEFORE_TICK, 256)
{
	this->m_camera = nullptr;
	this->m_loadedScene = nullptr;
}

EngineThread *EngineThread::getInstance() {
	static EngineThread *instance = new EngineThread();
	return instance;
}

void EngineThread::onStart() {
	if (this->m_initCallback)
		this->m_initCallback();
}

void EngineThread::onTick(const unsigned long currentTime, const unsigned long tickCount) {
	if (this->m_preTickCallback)
		this->m_preTickCallback(currentTime, tickCount);

	if (this->m_camera)
		this->m_camera->update(currentTime);

	if (this->m_loadedScene)
		this->m_loadedScene->update(currentTime, tickCount);

	if (this->m_postTickCallback)
		this->m_postTickCallback(currentTime, tickCount);
}

void EngineThread::onStop() {
	delete this->m_camera;

	if (this->m_stopCallback)
		this->m_stopCallback();
}

void EngineThread::setInitCallback(const std::function<void ()> &initCallback) {
	this->m_initCallback = initCallback;
}

void EngineThread::setPreTickCallback(const std::function<void (unsigned long, unsigned long)> &preTickCallback) {
	this->m_preTickCallback = preTickCallback;
}

void EngineThread::setPostTickCallback(const std::function<void (unsigned long, unsigned long)> &postTickCallback) {
	this->m_postTickCallback = postTickCallback;
}

void EngineThread::setStopCallback(const std::function<void ()> &stopCallback) {
	this->m_stopCallback = stopCallback;
}

Camera *EngineThread::getCamera() {
	return this->m_camera;
}

void EngineThread::setCamera(Camera *camera) {
	if (this->m_camera != camera)
		delete this->m_camera;

	this->m_camera = camera;
}

Scene *EngineThread::getLoadedScene() const {
	return this->m_loadedScene;
}

Scene *EngineThread::loadScene(Scene *scene) {
	Scene *old = this->m_loadedScene;
	this->m_loadedScene = scene;
	return old;
}
