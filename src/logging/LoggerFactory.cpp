//
// Created by masy on 01.02.20.
//

#include "cedar/LoggerFactory.h"
#include <vector>

// Normally i wouldn't do this, but i guess in the implementation file of a class its's ok.
using namespace cedar;

QueueLogAppender *LoggerFactory::currentQueueLogAppender = nullptr;
std::vector<Logger *> LoggerFactory::loggers = std::vector<Logger*>();

void LoggerFactory::setQueueLogAppender(QueueLogAppender *queueLogAppender)
{
	delete currentQueueLogAppender;
	currentQueueLogAppender = queueLogAppender;
}

Logger *LoggerFactory::getLogger(const std::string &name)
{
	for (auto &logger : loggers)
	{
		if (name == logger->m_name)
		{
			return logger;
		}
	}

	if (!currentQueueLogAppender)
		throw LoggerCreationException("Could not create Logger. The queue log appender is not set!");

	Logger *logger = new Logger(name, currentQueueLogAppender);
	loggers.push_back(logger);
	return logger;
}

void LoggerFactory::removeLogger(Logger *removingLogger)
{
	for (auto iterator = loggers.begin(); iterator != loggers.end(); iterator++)
	{
		if ((*iterator)->m_name == removingLogger->m_name)
		{
			loggers.erase(iterator);
			return;
		}
	}
}

void LoggerFactory::cleanUp()
{
	for (auto &logger : loggers)
	{
		delete logger;
	}

	loggers.clear();
	delete currentQueueLogAppender;
}