//
// Created by masy on 05.03.20.
//

#ifndef CEDAR_QUAD_H
#define CEDAR_QUAD_H

#include "cedar/Vector4f.h"

/**
 * Base namespace of the cedar engine.
 */
namespace cedar
{
	/**
	 * Class storing information of a quad instance needed to render a quad at a certain position.
	 */
	class Quad
	{
	public:
		/**
		 * The positions of the two corners of the quad.
		 *
		 * <p>The <code>X</code> and <code>Y</code> coordinates are the coordinates of the first corner and
		 * the <code>Z</code> and <code>W</code> coordinates are the position of the second corner.</p>
		 */
		Vector4f m_corners;
		/**
		 * The layer and texture unit of the quad.
		 *
		 * <p>The <code>X</code> is basically the z coordinate of the quad instance, which determines if it is rendered
		 * in front of or behind other quads. The <code>Y</code> coordinate is the id of the texture unit this quad uses.</p>
		 */
		Vector2f m_layerAndTexture;
		/**
		 * The uv coordinates of the quad.
		 *
		 * <p>The <code>X</code> and <code>Y</code> are the uv coordinates of the first corner and the <code>Z</code> and <code>W</code>
		 * coordinates are the uv coordinates of the second corner.
		 */
		Vector4f m_uvs;
		/**
		 * The tint of the quad.
		 *
		 * <p>The color components are normalized, meaning each component ranges between 0.0 and 1.0.</p>
		 */
		Vector4f m_tint;

		/**
		 * Creates a new quad.
		 */
		Quad();

		/**
		 * Creates a new quad.
		 *
		 * @param corners The top-left and bottom-right corners of the quad in pixel.
		 * @param layerAndTexture The layer and texture unit of the quad.
		 * @param uvs The uvs coordinates of the top-left and bottom-right corner.
		 * @param tint The tint of the color.
		 */
		Quad(const Vector4f &corners, const Vector2f &layerAndTexture, const Vector4f &uvs, const Vector4f &tint);

		/**
		 * Sets the values of the quad.
		 *
		 * @param corners The new corners of the quad,
		 * @param layerAndTexture The new layer and texture unit of the quad.
		 * @param uvs The new uv coordinates of the quad.
		 * @param tint The new tint of the quad.
		 */
		void set(const Vector4f &corners, const Vector2f &layerAndTexture, const Vector4f &uvs, const Vector4f &tint);

		/**
		 * Sets the values of the quad.
		 *
		 * @param cornerX1 The x coordinate of the top-left corner of the quad.
		 * @param cornerY1 The y coordinate of the top-left corner of the quad.
		 * @param cornerX2 The x coordinate of the bottom-right corner of the quad.
		 * @param cornerY2 The y coordinate of the bottom-right corner of the quad.
		 * @param layer The layer of the quad.
		 * @param textureUnit The texture unit of the quad.
		 * @param uvX1 The x uv coordinate of the top-left corner of the quad.
		 * @param uvY1 The y uv coordinate of the top-left corner of the quad.
		 * @param uvX2 The x uv coordinate of the bottom-right corner of the quad.
		 * @param uvY2 The y uv coordinate of the bottom-right corner of the quad.
		 * @param tintRed The red component of the tint of the quad.
		 * @param tintGreen The green component of the tint of the quad.
		 * @param tintBlue The blue component of the tint of the quad.
		 * @param tintAlpha The alpha component of the tint of the quad.
		 */
		void set(float cornerX1, float cornerY1, float cornerX2, float cornerY2, float layer, float textureUnit, float uvX1, float uvY1, float uvX2,
				 float uvY2, float tintRed, float tintGreen, float tintBlue, float tintAlpha);
	};
};

#endif //CEDAR_QUAD_H
