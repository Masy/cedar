//
// Created by masy on 06.03.20.
//

#ifndef CEDAR_OPENGLTHREAD_H
#define CEDAR_OPENGLTHREAD_H

#include "cedar/Thread.h"
#include "cedar/Window.h"
#include "cedar/MasterRenderer.h"

/**
 * Base namespace of the cedar engine.
 */
namespace cedar
{
	/**
	 * The class of the OpenGL thread.
	 *
	 * <p>This thread is responsible for rendering and everything OpenGL related like creating models and textures.</p>
	 *
	 * <p>The tick speed of this thread is depending on the user configuration, but 60 ticks per second is the default speed.</p>
	 */
	class OpenGLThread : public Thread
	{
	private:
		/**
		 * A pointer to the window of the game.
		 */
		Window *m_window;
		/**
		 * A pointer to the master renderer of the game.
		 */
		MasterRenderer *m_masterRenderer;
		/**
		 * The initialization callback of the OpenGL thread.
		 *
		 * <p>This is called after the window has been initialized and before the master renderer is initialized.</p>
		 */
		std::function<void(MasterRenderer *)> m_initCallback;
		/**
		 * The pre tick callback of the OpenGL thread.
		 *
		 * <p>This is called before anything is rendered.</p>
		 */
		std::function<void(unsigned long, unsigned long)> m_preTickCallback;
		/**
		 * The post tick callback of the OpenGL thread.
		 *
		 * <p>This is called after everything has rendered.</p>
		 */
		std::function<void(unsigned long, unsigned long)> m_postTickCallback;
		/**
		 * The stop callback of the OpenGL thread.
		 *
		 * <p>This is called after the window is terminated and the renderers have been deleted.</p>
		 */
		std::function<void()> m_stopCallback;
		/**
		 * The actually achieved frames per second of the last second.
		 */
		float m_fps;
		/**
		 * The amount of frame time since the last second.
		 */
		double m_frameTimes;
		/**
		 * The amount of frames since the last second.
		 */
		int m_frameCount;
		/**
		 * The timestamp in microseconds when the current second is over.
		 */
		unsigned long m_nextSecond;

		/**
		 * Creates a new OpenGL thread.
		 */
		OpenGLThread();

	public:
		/**
		 * Singleton getter to get the instance of the OpenGL thread.
		 *
		 * @return A pointer to the singleton instance of the OpenGL thread.
		 */
		static OpenGLThread *getInstance();

		/**
		 * Method which is called when the OpenGL thread is about to start.
		 *
		 * <p>The OpenGL thread is initialized here.</p>
		 */
		void onStart() override;

		/**
		 * Method which is called every tick of the input thread.
		 *
		 * <p>This will render a frame and/or generate models and textures.</p>
		 *
		 * @param currentTime The current time in microseconds.
		 * @param tickCount The current tick.
		 */
		void onTick(unsigned long currentTime, unsigned long tickCount) override;

		/**
		 * Method which is called when the OpenGL thread is about to stop.
		 *
		 * <p>The window and all the renderers, models and textures will be cleaned up here.</p>
		 */
		void onStop() override;

		/**
		 * Gets the window of the game.
		 *
		 * @return a pointer to the window of the game.
		 */
		[[nodiscard]] Window *getWindow() const;

		/**
		 * Gets the master renderer of the game.
		 *
		 * @return A pointer to the master renderer of the game.
		 */
		[[nodiscard]] MasterRenderer *getMasterRenderer() const;

		/**
		 * Gets the frames per second of the last second.
		 *
		 * @return The frames per second of the last second.
		 */
		[[nodiscard]] float getFPS() const;

		/**
		 * Sets the initialization callback of the OpenGL thread.
		 *
		 * @param initCallback The new initialization callback.
		 */
		void setInitCallback(const std::function<void(MasterRenderer *)> &initCallback);

		/**
		 * Sets the pre tick callback of the OpenGL thread.
		 *
		 * @param preTickCallback The new pre tick callback.
		 */
		void setPreTickCallback(const std::function<void(unsigned long, unsigned long)> &preTickCallback);

		/**
		 * Sets the post tick callback of the OpenGL thread.
		 *
		 * @param postTickCallback The new post tick callback.
		 */
		void setPostTickCallback(const std::function<void(unsigned long, unsigned long)> &postTickCallback);

		/**
		 * Sets the stop callback of the OpenGL thread.
		 *
		 * @param stopCallback The new stop callback.
		 */
		void setStopCallback(const std::function<void()> &stopCallback);
	};
}

#endif //CEDAR_OPENGLTHREAD_H
