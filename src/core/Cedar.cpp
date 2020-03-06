//
// Created by masy on 02.03.20.
//

#include "cedar/Cedar.h"
#include "cedar/EngineThread.h"
#include "cedar/OpenGLThread.h"
#include "cedar/InputThread.h"

using namespace cedar;

Cedar *Cedar::instance = nullptr;
Logger *Cedar::CoreLogger = nullptr;
Logger *Cedar::GLLogger = nullptr;

Cedar *Cedar::getInstance()
{
	return instance;
}

void Cedar::start(const int argc, const char **args)
{
	instance = this;

	this->preStart();

	CoreLogger = LoggerFactory::getLogger("Cedar::Core");
	GLLogger = LoggerFactory::getLogger("Cedar::GL");

	Thread *glWaitFor[1] = {EngineThread::getInstance()};
	Thread *inputWaitFor[1] = {OpenGLThread::getInstance()};

	InputThread::getInstance()->start(1, inputWaitFor);
	OpenGLThread::getInstance()->start(1, glWaitFor);
	std::thread *engine = EngineThread::getInstance()->start();

	this->onStart();
	engine->join();
}

void Cedar::stop()
{
	InputThread::getInstance()->stop();
	OpenGLThread::getInstance()->stop();
	EngineThread::getInstance()->stop();

	this->onStop();
}

const Logger *Cedar::getCoreLogger()
{
	return CoreLogger;
}

const Logger *Cedar::getGLLogger()
{
	return GLLogger;
}
