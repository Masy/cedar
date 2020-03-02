//
// Created by masy on 02.03.20.
//

#include "cedar/Cedar.h"

using namespace cedar;

Logger *cedar::CoreLogger = nullptr;
Logger *cedar::GLLogger = nullptr;

void cedar::initEngine(QueueLogAppender *logAppender, const int argc, const char **args)
{
	LoggerFactory::setQueueLogAppender(logAppender);
	logAppender->start();

	cedar::CoreLogger = LoggerFactory::getLogger("Cedar::Core");
	cedar::GLLogger = LoggerFactory::getLogger("Cedar::GL");
}
