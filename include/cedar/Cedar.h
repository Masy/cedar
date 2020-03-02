//
// Created by masy on 02.03.20.
//

#ifndef TALESOFCATVENTURE_CEDAR_H
#define TALESOFCATVENTURE_CEDAR_H

#include "cedar/LoggerFactory.h"

/**
 * Base namespace of the cedar engine.
 */
namespace cedar
{
	extern Logger *CoreLogger;
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

#endif //TALESOFCATVENTURE_CEDAR_H
