//
// Created by masy on 02.03.20.
//

#ifndef CEDAR_CEDAR_H
#define CEDAR_CEDAR_H

#include "cedar/LoggerFactory.h"

/**
 * Base namespace of the cedar engine.
 */
namespace cedar
{
	/**
	 * A pointer to the core logger of cedar.
	 */
	extern Logger *CoreLogger;
	/**
	 * A pointer to the OpenGL logger of cedar.
	 */
	extern Logger *GLLogger;

	/**
	 * Initializes the engine.
	 *
	 * @param logAppender The standard queue log appender.
	 * @param argc The number of program arguments.
	 * @param args The program arguments.
	 */
	void initEngine(QueueLogAppender *logAppender, int argc = 0, const char **args = nullptr);
}

#endif //CEDAR_CEDAR_H
