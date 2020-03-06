//
// Created by masy on 06.03.20.
//

#ifndef CEDAR_CONFIG_H
#define CEDAR_CONFIG_H

/**
 * Base namespace of the cedar engine.
 */
namespace cedar
{
	/**
	 * Configuration class for the cedar engine.
	 */
	class Config
	{
	private:
		/**
		 * The initial width of the window.
		 *
		 * <p>If {@link #m_fullscreen} is <code>true</code> this only sets the horizontal resolution of the window, not the actual width.</p>
		 */
		int m_windowWidth;
		/**
		 * The initial height of the window.
		 *
		 * <p>If {@link #m_fullscreen} is <code>true</code> this only sets the vertical resolution of the window, not the actual height.</p>
		 */
		int m_windowHeight;
		/**
		 * The initial fps limit of the game.
		 */
		int m_fpsLimit;
		/**
		 * The initial monitor the window is opened on.
		 */
		int m_selectedMonitor;
		/**
		 * Whether the window is opened in fullscreen or not.
		 */
		bool m_fullscreen;
		/**
		 * The initial field of view of the perspective cameras in degrees.
		 */
		float m_fov;

	public:
		/**
		 * Creates a default config.
		 */
		Config();

		/**
		 * Creates a config.
		 *
		 * @param windowWidth The width of the window.
		 * @param windowHeight The height of the window.
		 * @param fpsLimit The fps limit of the game.
		 * @param selectedMonitor The selected monitor the window is opened on.
		 * @param fullscreen Whether the window will be fullscreen or not.
		 * @param fov The field of view of the camera in degrees.
		 */
		Config(int windowWidth, int windowHeight, int fpsLimit, int selectedMonitor, bool fullscreen, float fov);

		/**
		 * Gets the initial width of the window.
		 *
		 * @return The initial width of the window.
		 */
		[[nodiscard]] int getWindowWidth() const;

		/**
		 * Sets the initial width of the window.
		 *
		 * @param newWindowWidth The new initial width of the window.
		 */
		void setWindowWith(int newWindowWidth);

		/**
		 * Gets the initial height of the window.
		 *
		 * @return The initial height of the window.
		 */
		[[nodiscard]] int getWindowHeight() const;

		/**
		 * Sets the initial height of the window.
		 *
		 * @param newWindowHeight The new initial height of the window.
		 */
		void setWindowHeight(int newWindowHeight);

		/**
		 * Sets the initial fps limit of the game.
		 *
		 * @return The initial fps limit of the game.
		 */
		[[nodiscard]] int getFPSLimit() const;

		/**
		 * Sets the initial fps limit of the game.
		 *
		 * @param newFPSLimit The initial fps limit of the game.
		 */
		void setFPSLimit(int newFPSLimit);

		/**
		 * Gets the initial monitor of the window.
		 *
		 * @return The initial monitor of the window.
		 */
		[[nodiscard]] int getSelectedMonitor() const;

		/**
		 * Sets the initial monitor of the window.
		 *
		 * @param newSelectedMonitor The new initial monitor of the window.
		 */
		void setSelectedMonitor(int newSelectedMonitor);

		/**
		 * Checks whether the window is initially opened in fullscreen mode.
		 *
		 * @return Whether the window is initially opened in fullscreen mode.
		 */
		[[nodiscard]] bool isFullscreen() const;

		/**
		 * Sets whether the window is initially opened in fullscreen mode.
		 *
		 * @param newFullscreen The new value whether the window will initially open in fullscreen mode.
		 */
		void setFullscreen(bool newFullscreen);

		/**
		 * Gets the initial field of view in degerees.
		 *
		 * @return The initial field of view in degerees.
		 */
		[[nodiscard]] float getFOV() const;

		/**
		 * Sets the initial field of view in degrees.
		 *
		 * @param newFOV The new initial field of view in degrees.
		 */
		void setFOV(float newFOV);
	};
}

#endif //CEDAR_CONFIG_H
