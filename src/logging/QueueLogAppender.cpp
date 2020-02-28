//
// Created by masy on 01.02.20.
//

#include "cedar/QueueLogAppender.h"

// Normally i wouldn't do this, but i guess in the implementation file of a class it's ok.
using namespace cedar;

//---------------------------------------------------------------------------//
//                                  Log Event                                //
//---------------------------------------------------------------------------//

LogEvent::LogEvent(const std::time_t &logTime, const LogLevel &logLevel, const char *loggerName, const char *message)
{
	this->m_logTime = logTime;
	this->m_logLevel = logLevel;
	this->m_loggerName = loggerName;
	this->m_message = message;
}

LogEvent::~LogEvent()
{
	delete[] this->m_message;
}

const char *LogEvent::getLogLevelAsString() const
{
	switch (this->m_logLevel)
	{
		case INFO:
			return "INFO";

		case WARNING:
			return "WARN";

		case ERROR:
			return "ERROR";

		case DEBUG:
			return "DEBUG";

		default:
			return "UNKNOWN";
	}
}


//---------------------------------------------------------------------------//
//                             Queue Log Appender                            //
//---------------------------------------------------------------------------//

LogAppenderException::LogAppenderException(const std::string &message) : XException(message)
{}

LogAppenderCreationException::LogAppenderCreationException(const std::string &message) : LogAppenderException(message)
{}

LogAppenderStartException::LogAppenderStartException(const std::string &message) : LogAppenderException(message)
{}

QueueLogAppender::QueueLogAppender()
{
	this->m_frontLogQueue = new std::queue<const LogEvent *>();
	this->m_backLogQueue = new std::queue<const LogEvent *>();
	this->m_thread = nullptr;
}

QueueLogAppender::~QueueLogAppender()
{
	delete this->m_frontLogQueue;
	delete this->m_backLogQueue;
	delete this->m_thread;
}

void QueueLogAppender::start()
{
	this->m_thread = new std::thread(&QueueLogAppender::run, this);
	this->m_thread->detach();
}

void QueueLogAppender::append(const LogEvent *logEvent)
{
	this->m_logQueueMutex.lock();
	this->m_backLogQueue->push(logEvent);
	this->m_logQueueMutex.unlock();
}

[[noreturn]] void QueueLogAppender::run()
{
	while (true)
	{
		this->m_logQueueMutex.lock();
		bool isEmpty = this->m_backLogQueue->empty();

		if (!isEmpty)
		{
			std::queue<const LogEvent *> *tmp = this->m_backLogQueue;
			this->m_backLogQueue = this->m_frontLogQueue;
			this->m_frontLogQueue = tmp;
			this->m_logQueueMutex.unlock();

			while (!this->m_frontLogQueue->empty())
			{
				const LogEvent *event = this->m_frontLogQueue->front();
				this->processLogEvent(event);
				this->m_frontLogQueue->pop();
				delete event;
			}
		}
		else
		{
			this->m_logQueueMutex.unlock();
			std::this_thread::sleep_for(std::chrono::milliseconds(1));
		}
	}
}
