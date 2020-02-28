//
// Created by masy on 01.02.20.
//

#ifndef CEDAR_LOGGERFACTORY_H
#define CEDAR_LOGGERFACTORY_H

#include "Logger.h"
#include <string>
#include "XException.h"

/**
 * Base namespace of the cedar engine.
 */
namespace cedar
{

	/**
	 * Class for creating and handling logger instances.
	 */
	class LoggerFactory
	{
	private:
		/**
		 * A pointer to the queue log appender that all new loggers will use.
		 */
		static QueueLogAppender *currentQueueLogAppender;
		/**
		 * A vector holding pointers to all loggers.
		 */
		static std::vector<Logger*> loggers;

	public:
		/**
		 * Sets the pointer to the queue log appender that all new loggers will use.
		 *
		 * @param queueLogAppender A pointer to the new queue log appender.
		 */
		static void setQueueLogAppender(QueueLogAppender *queueLogAppender);

		/**
		 * Gets or creates a new logger with the given name.
		 *
		 * @param name The name of the logger.
		 * @return a pointer to the logger with the given name.
		 *
		 * @throws LoggerCreationException if {@link #currentQueueLogAppender the current queue log appender} is a <code>nullptr</code>.
		 */
		static Logger *getLogger(const std::string &name);

		/**
		 * Removes the given logger from the factory's list.
		 *
		 * @param logger A pointer to the logger that will be removed.
		 */
		static void removeLogger(Logger *logger);

		/**
		 * Deletes all loggers that are currently in the {@link #loggers} list.
		 */
		static void cleanUp();
	};

}

#endif //CEDAR_LOGGERFACTORY_H
