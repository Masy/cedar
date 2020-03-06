//
// Created by masy on 06.03.20.
//

#ifndef CEDAR_MASTERRENDERER_H
#define CEDAR_MASTERRENDERER_H

#include <vector>

#include "cedar/Window.h"
#include "cedar/Matrix4f.h"
#include "cedar/Renderer.h"

/**
 * Base namespace of the cedar engine.
 */
namespace cedar
{
	/**
	 * The master renderer of the game.
	 *
	 * <p>This renderer handles all the other renderers and the projection and view matrices.</p>
	 */
	class MasterRenderer
	{
	private:
		/**
		 * A pointer to the window of the game.
		 */
		Window *m_window;
		/**
		 * A pointer to the perspective projection matrix of the window.
		 */
		Matrix4f *m_perspectiveProjectionMatrix;
		/**
		 * A pointer to the orthographic projection matrix of the window.
		 */
		Matrix4f *m_orthographicProjectionMatrix;
		/**
		 * A pointer to the view matrix of the camera.
		 *
		 * <p>If there currently is no camera this will be a unit matrix.</p>
		 */
		Matrix4f *m_viewMatrix;

		/**
		 * A list with all renderers.
		 */
		std::vector<Renderer *> m_renderers;

	public:
		/**
		 * Creates a new master renderer.
		 *
		 * @param window A pointer to the window of the game.
		 */
		explicit MasterRenderer(Window *window);

		/**
		 * Deletes the master renderer.
		 */
		~MasterRenderer();

		/**
		 * Initializes the master renderer.
		 */
		void init();

		/**
		 * Resize callback when the window is resized.
		 *
		 * <p>This also calls the {@link Renderer#onResize()} method for all renderers.</p>
		 */
		void onResize();

		/**
		 * Updates the view matrix and then renders all renderers.
		 *
		 * @param currentTime The current time of the frame in microseconds.
		 * @param tickCount The current tick count.
		 */
		void render(unsigned long currentTime, unsigned long tickCount);

		/**
		 * Adds a renderer to the master renderer.
		 *
		 * @param renderer A pointer to the renderer that will be added.
		 */
		void addRenderer(Renderer *renderer);

		/**
		 * Gets the perspective projection matrix of the window.
		 *
		 * @return A constant pointer to the perspective projection matrix of the window.
		 */
		[[nodiscard]] const Matrix4f *getPerspectiveProjectionMatrix() const;

		/**
		 * Gets the orthographic projection matrix of the window.
		 *
		 * @return A constant pointer to the orthographic projection matrix of the window.
		 */
		[[nodiscard]] const Matrix4f *getOrthographicProjectionMatrix() const;

		/**
		 * Gets the view matrix of the camera.
		 *
		 * @return A constant pointer to the view matrix of the camera.
		 */
		[[nodiscard]] const Matrix4f *getViewMatrix() const;
	};
}

#endif //CEDAR_MASTERRENDERER_H
