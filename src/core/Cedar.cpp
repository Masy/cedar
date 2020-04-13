//
// Created by masy on 02.03.20.
//

#include "cedar/Cedar.hpp"
#include "cedar/EngineThread.hpp"
#include "cedar/OpenGLThread.hpp"

using namespace cedar;

Cedar *Cedar::instance = nullptr;
Logger *Cedar::CoreLogger = nullptr;
Logger *Cedar::GLLogger = nullptr;
Config *Cedar::config = nullptr;

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

	OpenGLThread::getInstance()->start(1, glWaitFor);
	std::thread *engine = EngineThread::getInstance()->start();

	this->onStart();
	engine->join();
}

void Cedar::stop()
{
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

Config *Cedar::getConfig()
{
	return config;
}
