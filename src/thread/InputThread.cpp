//
// Created by masy on 06.03.20.
//

#include "cedar/InputThread.h"

using namespace cedar;

InputThread::InputThread() : Thread("InputThread", 20, QUEUE_BEFORE_TICK, 256)
{
	this->m_window = nullptr;
	this->m_inputHandler = nullptr;
}

InputThread *InputThread::getInstance() {
	static InputThread *instance = new InputThread();
	return instance;
}

void InputThread::onStart() {
	this->m_window = OpenGLThread::getInstance()->getWindow();

	this->m_inputHandler = new InputHandler(this->m_window);

	if (this->m_initCallback)
		this->m_initCallback(this->m_inputHandler);
}

void InputThread::onTick(unsigned long currentTime, unsigned long tickCount) {
	this->m_inputHandler->update();

	if (this->m_tickCallback)
		this->m_tickCallback(currentTime, tickCount, this->m_inputHandler);
}

void InputThread::onStop() {
	delete this->m_inputHandler;

	if (this->m_stopCallback)
		this->m_stopCallback();
}

void InputThread::setInitCallback(const std::function<void (InputHandler *)> &initCallback) {
	this->m_initCallback = initCallback;
}

void InputThread::setTickCallback(const std::function<void (unsigned long, unsigned long, InputHandler*)> &tickCallback) {
	this->m_tickCallback = tickCallback;
}

void InputThread::setStopCallback(const std::function<void ()> &stopCallback) {
	this->m_stopCallback = stopCallback;
}
