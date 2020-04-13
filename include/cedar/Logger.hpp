//
// Created by masy on 01.02.20.
//

#ifndef CEDAR_LOGGER_HPP
#define CEDAR_LOGGER_HPP

#include <cstring>
#include "cedar/XException.hpp"
#include "cedar/QueueLogAppender.hpp"

/**
 * Base namespace of the cedar engine.
 */
namespace cedar
{

	/**
	 * Base class for all logger related exceptions.
	 */
	class LoggerException : public XException
	{
	public:
		/**
		 * Creates a new logger exception.
		 *
		 * @param message The message of the exception
		 */
		explicit LoggerException(const std::string &message);
	};

	/**
	 * Exception which is thrown when a logger could not be created.
	 */
	class LoggerCreationException : public LoggerException
	{
	public:
		/**
		 * Creates a new logger creation exception.
		 *
		 * @param message The message of the exception.
		 */
		explicit LoggerCreationException(const std::string &message);
	};

	/**
	 * Class representing a logger.
	 */
	class Logger
	{
	protected:
		/**
		 * A pointer to the queue log appender that handles the log events of this logger.
		 */
		QueueLogAppender *m_queueLogAppender;

	public:
		/**
		 * The name of the logger.
		 */
		std::string m_name;

		/**
		 * Creates a new logger.
		 *
		 * @param name The name of the logger.
		 * @param queueLogAppender A pointer to the queue log appender that will handle the log events of the logger.
		 */
		Logger(const std::string &name, QueueLogAppender *queueLogAppender);

		/**
		 * Destroys the logger.
		 */
		~Logger();

		/**
		 * Creates an informal log event.
		 *
		 * @tparam Args The type of the variadic arguments.
		 * @param message The message of the log event.
		 * @param args The arguments with which the tags in the message will be replaced with.
		 */
		template<typename ... Args>
		void info(const std::string &message, Args &&... args) const
		{
			const size_t length = message.length() + 512;
			char *logMessage = new char[length];

			sprintf(logMessage, message.c_str(), std::forward<Args>(args)...);
			const LogEvent *logEvent = new LogEvent(std::time(nullptr), INFO, this->m_name.c_str(), logMessage);
			this->m_queueLogAppender->append(logEvent);
		};

		/**
		 * Creates an informal log event.
		 *
		 * @param message The message of the log event.
		 */
		void info(const std::string &message) const
		{
			char *logMessage = new char[message.length() + 1];
			std::strcpy(logMessage, message.c_str());
			const LogEvent *logEvent = new LogEvent(std::time(nullptr), INFO, this->m_name.c_str(), logMessage);
			this->m_queueLogAppender->append(logEvent);
		}

		/**
		 * Creates a warning log event.
		 *
		 * @tparam Args The type of the variadic arguments.
		 * @param message The message of the log event.
		 * @param args The arguments with which the tags in the message will be replaced with.
		 */
		template<typename ... Args>
		void warn(const std::string &message, Args &&... args) const
		{
			const size_t length = message.length() + 512;
			char *logMessage = new char[length];

			sprintf(logMessage, message.c_str(), std::forward<Args>(args)...);
			const LogEvent *logEvent = new LogEvent(std::time(nullptr), WARNING, this->m_name.c_str(), logMessage);
			this->m_queueLogAppender->append(logEvent);
		};

		/**
		 * Creates a warning log event.
		 *
		 * @param message The message of the log event.
		 */
		void warn(const std::string &message) const
		{
			char *logMessage = new char[message.length() + 1];
			std::strcpy(logMessage, message.c_str());
			const LogEvent *logEvent = new LogEvent(std::time(nullptr), WARNING, this->m_name.c_str(), logMessage);
			this->m_queueLogAppender->append(logEvent);
		}

		/**
		 * Creates an error log event.
		 *
		 * @tparam Args The type of the variadic arguments.
		 * @param message The message of the log event.
		 * @param args The arguments with which the tags in the message will be replaced with.
		 */
		template<typename ... Args>
		void error(const std::string &message, Args &&... args) const
		{
			const size_t length = message.length() + 512;
			char *logMessage = new char[length];

			sprintf(logMessage, message.c_str(), std::forward<Args>(args)...);
			const LogEvent *logEvent = new LogEvent(std::time(nullptr), ERROR, this->m_name.c_str(), logMessage);
			this->m_queueLogAppender->append(logEvent);
		};

		/**
		 * Creates an error log event.
		 *
		 * @param message The message of the log event.
		 */
		void error(const std::string &message) const
		{
			char *logMessage = new char[message.length() + 1];
			std::strcpy(logMessage, message.c_str());
			const LogEvent *logEvent = new LogEvent(std::time(nullptr), ERROR, this->m_name.c_str(), logMessage);
			this->m_queueLogAppender->append(logEvent);
		}

		/**
		 * Creates a debug log event.
		 *
		 * @tparam Args The type of the variadic arguments.
		 * @param message The message of the log event.
		 * @param args The arguments with which the tags in the message will be replaced with.
		 */
		template<typename ... Args>
		void debug(const std::string &message, Args &&... args) const
		{
			const size_t length = message.length() + 512;
			char *logMessage = new char[length];

			sprintf(logMessage, message.c_str(), std::forward<Args>(args)...);
			const LogEvent *logEvent = new LogEvent(std::time(nullptr), DEBUG, this->m_name.c_str(), logMessage);
			this->m_queueLogAppender->append(logEvent);
		};

		/**
		 * Creates a debug log event.
		 *
		 * @param message The message of the log event.
		 */
		void debug(const std::string &message) const
		{
			char *logMessage = new char[message.length() + 1];
			std::strcpy(logMessage, message.c_str());
			const LogEvent *logEvent = new LogEvent(std::time(nullptr), DEBUG, this->m_name.c_str(), logMessage);
			this->m_queueLogAppender->append(logEvent);
		}
	};

}

#endif //CEDAR_LOGGER_HPP
