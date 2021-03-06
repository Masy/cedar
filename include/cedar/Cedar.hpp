//
// Created by masy on 02.03.20.
//

#ifndef CEDAR_CEDAR_HPP
#define CEDAR_CEDAR_HPP

#include "cedar/Config.hpp"
#include "cedar/LoggerFactory.hpp"

using namespace cedar;

/**
 * Main class of the cedar engine.
 */
class Cedar
{
protected:
	/**
	 * A pointer to the instance of the cedar engine.
	 */
	static Cedar *instance;
	/**
	 * A pointer to the core logger of cedar.
	 */
	static Logger *CoreLogger;
	/**
	 * A pointer to the OpenGL logger of cedar.
	 */
	static Logger *GLLogger;
	/**
	 * A pointer to the configuration of the engine.
	 */
	static Config *config;

public:

	/**
	 * Gets the instance of the cedar engine.
	 *
	 * @return A pointer to the instance of the cedar engine.
	 */
	static Cedar *getInstance();

	/**
	 * Starts the engine.
	 *
	 * @param argc The number of program arguments.
	 * @param args The program arguments.
	 */
	void start(int argc = 0, const char **args = nullptr);
	/**
	 * Stops the engine.
	 */
	void stop();

	/**
	 * Method which is called when the engine is about to start.
	 */
	virtual void preStart() = 0;
	/**
	 * Method which is called right after all threads have been started.
	 */
	virtual void onStart() = 0;
	/**
	 * Method which is called when the engine is about to stop.
	 */
	virtual void onStop() = 0;

	/**
	 * Gets the core logger of the engine.
	 *
	 * @return A constant pointer to the core logger of the engine.
	 */
	[[nodiscard]] static const Logger *getCoreLogger();

	/**
	 * Gets the OpenGL logger of the engine.
	 *
	 * @return A constant pointer to the OpenGL logger of the engine.
	 */
	[[nodiscard]] static const Logger *getGLLogger();

	/**
	 * Gets the configuration of the engine.
	 *
	 * @return A pointer to the configuration of the engine.
	 */
	[[nodiscard]] static Config *getConfig();
};

#endif //CEDAR_CEDAR_HPP
