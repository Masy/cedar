//
// Created by masy on 08.03.20.
//

#ifndef CEDAR_LABEL_HPP
#define CEDAR_LABEL_HPP

#include <memory>
#include "cedar/Element.hpp"
#include "cedar/Vector4f.hpp"
#include "cedar/Font.hpp"

/**
 * Base namespace of the cedar engine.
 */
namespace cedar
{
	/**
	 * Class representing a text element.
	 */
	class Label : public Element
	{
	protected:
		/**
		 * The text of the label.
		 */
		std::string m_text;
		/**
		 * A shared pointer to the font of the text.
		 */
		std::shared_ptr<Font> m_font;
		/**
		 * The color of the text.
		 */
		Vector4f m_textColor;
		/**
		 * A pointer to the text buffer storing the glyphs of the label's text.
		 */
		TextBuffer *m_textBuffer;

	public:
		/**
		 * Creates a new label.
		 *
		 * <p>The size of the label is calculated based on the label's text.</p>
		 *
		 * @param originX The x coordinate of the origin of the element in pixel.
		 * @param originY The y coordinate of the origin of the element in pixel.
		 * @param zIndex The z index of the element.
		 * @param text The text of the button. Can be empty.
		 * @param font A shared pointer to the font of the text.
		 * @param textColor The color of the text.
		 * @param alignment The alignment of the element.
		 *
		 * @throws ElementCreationException if the provided text is empty.
		 * @throws ElementCreationException if <code>font</code> is a <code>nullptr</code>.
		 */
		Label(float originX, float originY, unsigned char zIndex, const std::string &text, const std::shared_ptr<Font> &font, const Vector4f &textColor,
			  unsigned int alignment = CEDAR_ALIGNMENT_TOP | CEDAR_ALIGNMENT_LEFT);

		/**
		 * Destroys the label.
		 */
		~Label();

		/**
		 * Renders the label.
		 *
		 * @param currentTime The current time of the frame in microseconds.
		 */
		void render(unsigned long currentTime) override;

		/**
		 * Gets the text of the label.
		 *
		 * @return The text of the label.
		 */
		[[nodiscard]] std::string getText() const;

		/**
		 * Sets the text of the label.
		 *
		 * @param text The new text of the label.
		 *
		 * @throws ElementUpdateException if the provided text is empty.
		 */
		void setText(const std::string &text);

		/**
		 * Gets the font of the label.
		 *
		 * @return A shared pointer to the font of the label.
		 */
		[[nodiscard]] std::shared_ptr<Font> getFont() const;

		/**
		 * Sets the font of the label.
		 *
		 * @param newFont A shared pointer to the new font of the label.
		 *
		 * @throws ElementUpdateException if the provided font is a <code>nullptr</code>.
		 */
		void setFont(const std::shared_ptr<Font> &newFont);

		/**
		 * Sets the color of the label's text.
		 *
		 * @param color The new color of the label's text.
		 */
		void setTextColor(const Vector4f &color);

		/**
		 * Sets the width of the label.
		 *
		 * <p>Overload to throw an exception as the width is controlled by the label's text.</p>
		 *
		 * @param newWidth The new width of the label.
		 *
		 * @throws UnsupportedOperationException because the width is controlled by the label's text.
		 */
		void setWidth(float newWidth) override;

		/**
		 * Sets the height of the label.
		 *
		 * <p>Overload to throw an exception as the height is controlled by the label's text.</p>
		 *
		 * @param newHeight The new height of the label.
		 *
		 * @throws UnsupportedOperationException because the height is controlled by the label's text.
		 */
		void setHeight(float newHeight) override;

		/**
		 * Sets the size of the label.
		 *
		 * <p>Overload to throw an exception as the size is controlled by the label's text.</p>
		 *
		 * @param newWidth The new width of the label.
		 * @param newHeight The new height of the label.
		 *
		 * @throws UnsupportedOperationException because the size is controlled by the label's text.
		 */
		void setSize(float newWidth, float newHeight) override;
	};
}

#endif //CEDAR_LABEL_HPP
