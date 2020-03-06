//
// Created by masy on 06.03.20.
//

#ifndef CEDAR_INPUTTHREAD_H
#define CEDAR_INPUTTHREAD_H

#include "cedar/Thread.h"
#include "cedar/OpenGLThread.h"
#include "cedar/InputHandler.h"

/**
 * Base namespace of the cedar engine.
 */
namespace cedar
{
	/**
	 * The class of the input thread.
	 *
	 * <p>The input thread is responsible for polling mouse and key events and to process them.</p>
	 *
	 * <p>This thread ticks at a speed of 20 ticks per second.</p>
	 */
	class InputThread : public Thread
	{
	private:
		/**
		 * A pointer to the window of the game.
		 */
		Window *m_window;
		/**
		 * A pointer to the input handler of the game
		 */
		InputHandler *m_inputHandler;
		/**
		 * The initialization callback of the input thread.
		 *
		 * <p>This is called right after the input handler has been initialized.</p>
		 */
		std::function<void(InputHandler *)> m_initCallback;
		/**
		 * The tick callback of the input thread.
		 *
		 * <p>This is called right after the input handler has polled the input.</p>
		 */
		std::function<void(unsigned long, unsigned long, InputHandler *)> m_tickCallback;
		/**
		 * The stop callback of the input thread.
		 *
		 * <p>This is called right after the input handler has been deletes.</p>
		 */
		std::function<void()> m_stopCallback;

		/**
		 * Creates a new input thread.
		 */
		InputThread();

	public:
		/**
		 * Singleton getter to get the instance of the input thread.
		 *
		 * @return A pointer to the singleton instance of the input thread.
		 */
		static InputThread *getInstance();

		/**
		 * Method which is called when the input thread is about to start.
		 *
		 * <p>The input thread is initialized here.</p>
		 */
		void onStart() override;

		/**
		 * Method which is called every tick of the input thread.
		 *
		 * <p>This will poll events and process them.</p>
		 *
		 * @param currentTime The current time in microseconds.
		 * @param tickCount The current tick.
		 */
		void onTick(unsigned long currentTime, unsigned long tickCount) override;

		/**
		 * Method which is called when the input thread is about to stop.
		 *
		 * <p>All the key combinations and the input handler will be cleaned up here.</p>
		 */
		void onStop() override;

		/**
		 * Sets the initialization callback of the input thread.
		 *
		 * @param initCallback The new initialization callback.
		 */
		void setInitCallback(const std::function<void(InputHandler *)> &initCallback);

		/**
		 * Sets the tick callback of the input thread.
		 *
		 * @param tickCallback The new tick callback.
		 */
		void setTickCallback(const std::function<void(unsigned long, unsigned long, InputHandler *)> &tickCallback);

		/**
		 * Sets the stop callback of the input thread.
		 *
		 * @param stopCallback The new stop callback of the input thread.
		 */
		void setStopCallback(const std::function<void()> &stopCallback);
	};
}

#endif //CEDAR_INPUTTHREAD_H
