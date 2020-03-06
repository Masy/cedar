//
// Created by masy on 06.03.20.
//

#ifndef CEDAR_ENGINETHREAD_H
#define CEDAR_ENGINETHREAD_H

#include "cedar/Thread.h"
#include "cedar/Camera.h"

/**
 * Base namespace of the cedar engine.
 */
namespace cedar
{
	/**
	 * The class of the engine thread.
	 *
	 * <p>The engine thread is responsible for handling entities and everything that other threads don't handle.</p>
	 *
	 * <p>This thread ticks at a speed of 20 ticks per second.</p>
	 */
	class EngineThread : public Thread
	{
	private:
		/**
		 * The camera of the game.
		 */
		Camera *m_camera;
		/**
		 * The initialization callback of the engine thread.
		 *
		 * <p>This is called when then engine thread is done with its initialization.</p>
		 */
		std::function<void()> m_initCallback;
		/**
		 * The pre tick callback of the engine thread.
		 *
		 * <p>This is called before anything is updated.</p>
		 */
		std::function<void(unsigned long, unsigned long)> m_preTickCallback;
		/**
		 * The post tick callback of the engine thread.
		 *
		 * <p>This is called after everything is updated.</p>
		 */
		std::function<void(unsigned long, unsigned long)> m_postTickCallback;
		/**
		 * The stop callback of the engine thread.
		 *
		 * </p>This is called after all entities have been deleted.</p>
		 */
		std::function<void()> m_stopCallback;

		/**
		 * Creates a new engine thread.
		 */
		EngineThread();

	public:
		/**
		 * Singleton getter to get the instance of the engine thread.
		 *
		 * @return A pointer to the singleton instance of the engine thread.
		 */
		static EngineThread *getInstance();

		/**
		 * Method which is called when the engine thread is about to start.
		 *
		 * <p>The engine thread is initialized here.</p>
		 */
		void onStart() override;

		/**
		 * Method which is called every tick of the engine thread.
		 *
		 * <p>This will handle the game state machine and entity updates.</p>
		 *
		 * @param currentTime The current time in microseconds.
		 * @param tickCount The current tick.
		 */
		void onTick(unsigned long currentTime, unsigned long tickCount) override;

		/**
		 * Method which is called when the engine thread is about to stop.
		 *
		 * <p>Everything the entity thread handled will be cleaned up here.</p>
		 */
		void onStop() override;

		/**
		 * Sets the initialization callback of the engine thread.
		 *
		 * @param initCallback The new initialization callback.
		 */
		void setInitCallback(const std::function<void()> &initCallback);

		/**
		 * Sets the pre tick callback of the engine thread.
		 *
		 * @param preTickCallback The new pre tick callback.
		 */
		void setPreTickCallback(const std::function<void(unsigned long, unsigned long)> &preTickCallback);

		/**
		 * Sets the post tick callback of the engine thread.
		 *
		 * @param postTickCallback The new post tick callback.
		 */
		void setPostTickCallback(const std::function<void(unsigned long, unsigned long)> &postTickCallback);

		/**
		 * Sets the stop callback of the engine thread.
		 *
		 * @param stopCallback The new stop callback.
		 */
		void setStopCallback(const std::function<void()> &stopCallback);

		/**
		 * Gets the current camera.
		 *
		 * @return A pointer to the current camera.
		 */
		[[nodiscard]] Camera *getCamera();

		/**
		 * Sets the current camera.
		 *
		 * @param camera A pointer to the new camera.
		 */
		void setCamera(Camera *camera);
	};
}

#endif //CEDAR_ENGINETHREAD_H
