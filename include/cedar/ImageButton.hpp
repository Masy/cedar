//
// Created by masy on 23.04.20.
//

#ifndef CEDAR_IMAGEBUTTON_HPP
#define CEDAR_IMAGEBUTTON_HPP

#include <memory>
#include "Element.hpp"
#include "Font.hpp"

/**
 * Base namespace of the cedar engine.
 */
namespace cedar
{
	/**
	 * Class representing a button element with a texture.
	 */
	class ImageButton : public Element
	{
	protected:
		/**
		 * A shared pointer to the texture of the button.
		 */
		std::shared_ptr<Texture> m_texture;
		/**
		 * The uv coordinates of the button in it's default state.
		 */
		Vector4f m_defaultUVs;
		/**
		 * The uv coordinates of the button in it's hovered state.
		 */
		Vector4f m_hoveredUVs;
		/**
		 * The uv coordinates of the button in it's pressed state.
		 */
		Vector4f m_pressedUVs;

		/**
		 * The caption of the button.
		 */
		std::string m_caption;
		/**
		 * A shared pointer to the font of the caption.
		 */
		std::shared_ptr<Font> m_font;
		/**
		 * A pointer to the text buffer of the caption.
		 */
		TextBuffer *m_textBuffer;
		/**
		 * The default color of the caption.
		 */
		Vector4f m_defaultCaptionColor;
		/**
		 * The color of the caption when the button is being hovered over.
		 */
		Vector4f m_hoveredCaptionColor;
		/**
		 * The color of the caption when the button is being pressed down.
		 */
		Vector4f m_pressedCaptionColor;

	public:
		/**
		 * Creates a new image button.
		 *
		 * @param originX The x coordinate of the origin of the button in pixel.
		 * @param originY The y coordinate of the origin of the button in pixel.
		 * @param zIndex The z index of the element.
		 * @param width The width of the button in pixel.
		 * @param height The height of the button in pixel.
		 * @param texture The texture of the button.
		 * @param defaultUVs The uv coordinates of the button in it's default state.
		 * @param hoveredUVs The uv coordinates of the button in it's hovered state.
		 * @param pressedUVs The uv coordinates of the button in it's pressed state.
		 * @param caption The caption of the button.
		 * @param font The font of the button's caption.
		 * @param captionColor The color of the button's caption.
		 * @param alignment The alignment of the button.
		 */
		ImageButton(float originX, float originY, unsigned char zIndex, float width, float height,
				const std::shared_ptr<Texture> &texture, const Vector4f &defaultUVs, const Vector4f &hoveredUVs, const Vector4f &pressedUVs,
				const std::string &caption, const std::shared_ptr<Font> &font, const Vector4f &captionColor,
				unsigned int alignment = CEDAR_ALIGNMENT_TOP | CEDAR_ALIGNMENT_LEFT);

		/**
		 * Creates a new image button.
		 *
		 * @param originX The x coordinate of the origin of the button in pixel.
		 * @param originY The y coordinate of the origin of the button in pixel.
		 * @param zIndex The z index of the element.
		 * @param width The width of the button in pixel.
		 * @param height The height of the button in pixel.
		 * @param texture The texture of the button.
		 * @param defaultUVs The uv coordinates of the button in it's default state.
		 * @param hoveredUVs The uv coordinates of the button in it's hovered state.
		 * @param pressedUVs The uv coordinates of the button in it's pressed state.
		 * @param caption The caption of the button.
		 * @param font The font of the button's caption.
		 * @param defaultCaptionColor The color of the button's caption in it's default state.
		 * @param hoveredCaptionColor The color of the button's caption in it's hovered state.
		 * @param pressedCaptionColor The color of the button's caption in it's pressed state
		 * @param alignment The alignment of the button.
		 */
		ImageButton(float originX, float originY, unsigned char zIndex, float width, float height,
				const std::shared_ptr<Texture> &texture, const Vector4f &defaultUVs, const Vector4f &hoveredUVs, const Vector4f &pressedUVs,
				const std::string &caption = "", const std::shared_ptr<Font> &font = nullptr, const Vector4f &defaultCaptionColor = Vector4f(1.0f, 1.0f, 1.0f, 1.0f),
				const Vector4f &hoveredCaptionColor = Vector4f(1.0f, 1.0f, 1.0f, 1.0f), const Vector4f &pressedCaptionColor = Vector4f(1.0f, 1.0f, 1.0f, 1.0f),
				unsigned int alignment = CEDAR_ALIGNMENT_TOP | CEDAR_ALIGNMENT_LEFT);

		/**
		 * Deletes the image button.
		 */
		~ImageButton();

		/**
		 * Gets the texture of the image button.
		 *
		 * @return A shared pointer to the texture of the button.
		 */
		[[nodiscard]] std::shared_ptr<Texture> getTexture() const;

		/**
		 * Gets the button's caption.
		 *
		 * @return The button's caption.
		 */
		[[nodiscard]] std::string getCaption() const;

		/**
		 * Sets the button's caption.
		 *
		 * @param newCaption The new caption of the button.
		 */
		void setCaption(const std::string &newCaption);

		/**
		 * Gets the font of the button's caption.
		 *
		 * @return A shared pointer to the font of the button's caption.
		 */
		[[nodiscard]] std::shared_ptr<Font> getFont() const;

		/**
		 * Sets the font of the button's caption.
		 *
		 * @param newFont A shared pointer to the new font of the button's caption.
		 */
		void setFont(const std::shared_ptr<Font> &newFont);

		/**
		 * Gets the color of the button's caption in it's default state.
		 *
		 * @return The color of the button's caption in it's default state.
		 */
		[[nodiscard]] Vector4f getDefaultCaptionColor() const;

		/**
		 * Sets the color of the button's caption in it's default state.
		 *
		 * @param newColor The new color of the button's caption in it's default state.
		 */
		void setDefaultCaptionColor(const Vector4f &newColor);

		/**
		 * Gets the color of the button's caption in it's hovered state.
		 *
		 * @return The color of the button's caption in it's hovered state.
		 */
		[[nodiscard]] Vector4f getHoveredCaptionColor() const;

		/**
		 * Sets the color of the button's caption in it's hovered state.
		 *
		 * @param newColor The new color of the button's caption in it's hovered state.
		 */
		void setHoveredCaptionColor(const Vector4f &newColor);

		/**
		 * Gets the color of the button's caption in it's pressed state.
		 *
		 * @return The color of the button's caption in it's pressed state.
		 */
		[[nodiscard]] Vector4f getPressedCaptionColor() const;

		/**
		 * Sets the color of the button's caption in it's pressed state.
		 *
		 * @param newColor The new color of the button's caption in it's pressed state.
		 */
		void setPressedCaptionColor(const Vector4f &newColor);

		/**
		 * Renders the button.
		 *
		 * @param currentTime The current time of the frame in microseconds.
		 */
		void render(unsigned long currentTime) override;
	};

}

#endif //CEDAR_IMAGEBUTTON_HPP
