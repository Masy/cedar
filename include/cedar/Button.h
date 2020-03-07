//
// Created by masy on 08.03.20.
//

#ifndef CEDAR_BUTTON_H
#define CEDAR_BUTTON_H

#include "cedar/Element.h"
#include "cedar/Font.h"

/**
 * Base namespace of the cedar engine.
 */
namespace cedar
{
	/**
	 * Class representing a button element.
	 */
	class Button : public Element
	{
	protected:
		/**
		 * The text of the button.
		 *
		 * <p>Can be empty.</p>
		 */
		std::string m_text;
		/**
		 * A pointer to the font the text of the button is rendered with.
		 *
		 * <p>Can be a <code>nullptr</code> if the button has no text.</p>
		 */
		Font *m_font;
		/**
		 * The default color of the text.
		 */
		Vector4f m_textColor;
		/**
		 * The color of the text when the button is being hovered over.
		 */
		Vector4f m_hoveredTextColor;
		/**
		 * The color of the text when the button is being pressed down.
		 */
		Vector4f m_pressedTextColor;
		/**
		 * A pointer to the text buffer storing the glyphs of the button's text.
		 *
		 * <p>Can be a <code>nullptr</code> if the button has no text.</p>
		 */
		TextBuffer *m_textBuffer;
		/**
		 * The default background color of the button.
		 */
		Vector4f m_backgroundColor;
		/**
		 * The background color of the button when it is being hovered over.
		 */
		Vector4f m_hoveredBackgroundColor;
		/**
		 * The background color of the button when it is being pressed down.
		 */
		Vector4f m_pressedBackgroundColor;

	public:
		/**
		 * Creates a new button.
		 *
		 * <p>If the <code>text</code> is empty the <code>font</code> is allowed to be a nullptr.</p>
		 *
		 * @param originX The x coordinate of the origin of the element in pixel.
		 * @param originY The y coordinate of the origin of the element in pixel.
		 * @param zIndex The z index of the element.
		 * @param width The width of the element in pixel.
		 * @param height The height of the element in pixel.
		 * @param text The text of the button. Can be empty.
		 * @param font A pointer to the font of the text.
		 * @param color The color of the text.
		 * @param alignment The alignment of the element.
		 *
		 * @throws ElementCreationException if the <code>font</code> is <code>nullptr</code> when the <code>text</code> is not empty.
		 */
		Button(float originX, float originY, unsigned char zIndex, float width, float height, const std::string &text, Font *font,
			   const Vector4f &color, unsigned int alignment = CEDAR_ALIGNMENT_TOP | CEDAR_ALIGNMENT_LEFT);

		/**
		 * Deletes the button.
		 */
		~Button();

		/**
		 * Renders the button.
		 *
		 * @param currentTime The current time of the frame in microseconds.
		 */
		void render(unsigned long currentTime) override;

		/**
		 * Sets the default background color of the button.
		 *
		 * @param color The new default background color of the button.
		 */
		void setBackgroundColor(const Vector4f &color);

		/**
		 * Sets the hovered background color of the button.
		 *
		 * @param color The new hovered background color of the button.
		 */
		void setHoveredBackgroundColor(const Vector4f &color);

		/**
		 * Sets the pressed background color of the button.
		 *
		 * @param color The new pressed background color of the button.
		 */
		void setPressedBackgroundColor(const Vector4f &color);

		/**
		 * Sets the default text color of the button.
		 *
		 * @param color The new default text color of the button.
		 */
		void setTextColor(const Vector4f &color);

		/**
		 * Sets the hovered text color of the button.
		 *
		 * @param color The new hovered text color of the button.
		 */
		void setHoveredTextColor(const Vector4f &color);

		/**
		 * Sets the pressed text color of the button.
		 *
		 * @param color The new pressed text color of the button.
		 */
		void setPressedTextColor(const Vector4f &color);

		/**
		 * Gets the text of the button.
		 *
		 * @return The text of the button.
		 */
		[[nodiscard]] std::string getText() const;

		/**
		 * Sets the text of the button.
		 *
		 * @param text The new text of the button.
		 *
		 * @throws ElementUpdateException if the new text isn't empty and the {@link #m_font font} of the button is not set.
		 */
		void setText(const std::string &text);

		/**
		 * Gets the font of the text of the button.
		 *
		 * @return A pointer to the font of text of the button
		 */
		[[nodiscard]] Font *getFont() const;

		/**
		 * Sets the font of the text of the button.
		 *
		 * @param newFont A pointer to the new font of the text of the button.
		 *
		 * @throws ElementUpdateException if the provided font is a <code>nullptr</code>.
		 */
		void setFont(Font *newFont);
	};
}

#endif //CEDAR_BUTTON_H
