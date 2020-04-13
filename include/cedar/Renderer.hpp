//
// Created by masy on 06.03.20.
//

#ifndef CEDAR_RENDERER_HPP
#define CEDAR_RENDERER_HPP

/**
 * Base namespace of the cedar engine.
 */
namespace cedar
{
	/**
	 * The base class of all renderers.
	 *
	 * <p>The {@link #init()} method is called when the master renderer finished initializing.</p>
	 */
	class Renderer
	{
	public:
		/**
		 * Creates a new renderer.
		 */
		Renderer();

		/**
		 * Destroys the renderer.
		 */
		virtual ~Renderer();

		/**
		 * Initialized the renderer.
		 */
		virtual void init() = 0;

		/**
		 * Resize callback when the window is resized.
		 */
		virtual void onResize() = 0;

		/**
		 * Render method which is called each frame.
		 *
		 * @param currentTime The current time of the frame in microseconds.
		 * @param tickCount The current tick count of the OpenGL Thread.
		 */
		virtual void render(unsigned long currentTime, unsigned long tickCount) = 0;
	};
}

#endif //CEDAR_RENDERER_HPP
