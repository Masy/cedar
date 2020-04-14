//
// Created by masy on 14.04.20.
//

#ifndef CEDAR_IMAGE_HPP
#define CEDAR_IMAGE_HPP


#include <memory>
#include "Element.hpp"
#include "Texture2D.hpp"
#include "Vector4f.hpp"

/**
 * Base namespace of the cedar engine.
 */
namespace cedar
{

	/**
	 * Class representing an image element.
	 */
	class Image : public Element
	{
	private:
		/**
		 * A shared pointer to the texture of the image.
		 */
		std::shared_ptr<Texture> m_texture;
		/**
		 * The uv section of the texture that will be rendered.
		 */
		Vector4f m_uvSection;

	public:
		/**
		 * Creates a new image.
		 *
		 * @param originX The x coordinate of the origin of the element in pixel.
		 * @param originY The y coordinate of the origin of the element in pixel.
		 * @param zIndex The z index of the element.
		 * @param width The width of the image in pixel.
		 * @param height The height of the image in pixel.
		 * @param texture A shared pointer to the texture of the image.
		 * @param uvSection The uv section of the texture that will be rendered.
		 * @param alignment The alignment of the element.
		 */
		Image(float originX, float originY, unsigned char zIndex, float width, float height, const std::shared_ptr<Texture> &texture, const Vector4f &uvSection, unsigned int alignment = CEDAR_ALIGNMENT_TOP | CEDAR_ALIGNMENT_LEFT);

		/**
		 * Renders the Image.
		 *
		 * @param currentTime The current time of the frame in microseconds.
		 */
		void render(unsigned long currentTime) override;
	};

}

#endif //CEDAR_IMAGE_HPP
