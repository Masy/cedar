//
// Created by masy on 01.02.20.
//

#ifndef CEDAR_QUEUELOGAPPENDER_H
#define CEDAR_QUEUELOGAPPENDER_H

#include <string>
#include <ctime>
#include <thread>
#include <queue>
#include <mutex>
#include "XException.h"

/**
 * Base namespace of the cedar engine.
 */
namespace cedar
{

	/**
	 * Enum defining the level of a log event.
	 */
	enum LogLevel
	{
		/**
		 * The log event will be an information.
		 */
		INFO,
		/**
		 * The log event will be a warning.
		 */
		WARNING,
		/**
		 * The log event will be an error.
		 */
		ERROR,
		/**
		 * The log event will be for debugging
		 */
		DEBUG
	};

	/**
	 * Class for bundling multiple information into a single log event.
	 */
	class LogEvent
	{
	public:
		/**
		 * The timestamp of the log event.
		 */
		std::time_t m_logTime;
		/**
		 * The level of the log event.
		 */
		LogLevel m_logLevel;
		/**
		 * A pointer to the name of the logger that fired the log event.
		 */
		const char *m_loggerName;
		/**
		 * A pointer to the message of the log event.
		 */
		const char *m_message;

		/**
		 * Creates a new log event.
		 *
		 * @param logTime The timestamp of the log event.
		 * @param logLevel The level of the log event.
		 * @param loggerName A pointer to the name of the logger that fired the log event.
		 * @param message A pointer to the message of the log event.
		 */
		LogEvent(const std::time_t &logTime, const LogLevel &logLevel, const char *loggerName, const char *message);

		/**
		 * Destroys the log event.
		 */
		~LogEvent();

		/**
		 * Gets the log level of the logger as string.
		 *
		 * @return the log level of the logger as string.
		 */
		[[nodiscard]] const char *getLogLevelAsString() const;
	};

	/**
	 * Base class for all log appender related exceptions.
	 */
	class LogAppenderException : public XException
	{
	public:
		/**
		 * Creates a new log appender exception.
		 *
		 * @param message The message of the exception.
		 */
		explicit LogAppenderException(const std::string &message);
	};

	/**
	 * Exception which is thrown when a log appender could not be created.
	 */
	class LogAppenderCreationException : public cedar::LogAppenderException
	{
	public:
		/**
		 * Creates a new log appender creation exception.
		 *
		 * @param message The message of the exception.
		 */
		explicit LogAppenderCreationException(const std::string &message);
	};

	/**
	 * Exception which is thrown when a log appender could not be started.
	 */
	class LogAppenderStartException : public LogAppenderException
	{
	public:
		/**
		 * Creates a new log appender start exception.
		 *
		 * @param message The message of the exception.
		 */
		explicit LogAppenderStartException(const std::string &message);
	};

	/**
	 * Class which queues log events and outputs them to streams.
	 */
	class QueueLogAppender
	{
	protected:
		/**
		 * A pointer to the thread this queue log appender runs in.
		 */
		std::thread *m_thread;
		/**
		 * A pointer to the front queue of log events.
		 */
		std::queue<const LogEvent *> *m_frontLogQueue;
		/**
		 * A pointer to the back queue of log events.
		 */
		std::queue<const LogEvent *> *m_backLogQueue;
		/**
		 * The mutex of the {@link #m_backLogQueue back log queue}.
		 */
		std::mutex m_logQueueMutex;

		/**
		 * The main method of the queue log appender.
		 */
		[[noreturn]] void run();

	public:
		/**
		 * Creates a new queue log appender.
		 */
		QueueLogAppender();

		/**
		 * Destroys the queue log appender.
		 */
		virtual ~QueueLogAppender();

		/**
		 * Starts the queue log appender.
		 */
		virtual void start();

		/**
		 * Appends the given log event to the {@link #m_backLogQueue back log queue} of the queue lof appender.
		 *
		 * @param logEvent A pointer to the log event that will be appended.
		 */
		void append(const LogEvent *logEvent);

		/**
		 * Processes the given log event.
		 *
		 * @param logEvent A pointer to the log event that will be processed.
		 */
		virtual void processLogEvent(const LogEvent *logEvent) = 0;
	};

}

#endif //CEDAR_QUEUELOGAPPENDER_H
