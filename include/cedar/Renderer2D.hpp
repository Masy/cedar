//
// Created by masy on 23.02.20.
//

#ifndef CEDAR_RENDERER2D_HPP
#define CEDAR_RENDERER2D_HPP

#include "cedar/Vector4f.hpp"
#include "cedar/ShaderProgram.hpp"
#include "cedar/Matrix4f.hpp"
#include "cedar/Texture2D.hpp"
#include "cedar/Quad.hpp"
#include "cedar/Font.hpp"

/**
 * Base namespace of the cedar engine.
 */
namespace cedar
{

	/**
	 * Class for rendering 2 dimensional elements.
	 */
	class Renderer2D
	{
	private:
		/**
		 * A pointer to the shader program the renderer uses to render the elements.
		 */
		static ShaderProgram *shader;
		/**
		 * A pointer to the uniform locations of the shader program.
		 */
		static int *uniformLocations;
		/**
		 * A pointer to the orthographic projection matrix of the window.
		 */
		static Matrix4f *projectionMatrix;
		/**
		 * A pointer to the default texture.
		 *
		 * <p>The default texture is always a white 1x1 square to render colored quads without any texture.</p>
		 */
		static Texture2D *defaultTexture;

		/**
		 * A pointer to the batch array of the renderer.
		 *
		 * <p>The size of the array is fixed and will not be reallocated at any time.</p>
		 */
		static Quad *batch;
		/**
		 * A pointer to the next quad that will be written to the batch.
		 */
		static Quad *nextQuad;
		/**
		 * The number of quads currently used by the batch.
		 */
		static unsigned int quadCount;
		/**
		 * The size of the {@link #batch batch array}.
		 */
		static unsigned int batchSize;

		/**
		 * The number of texture units used by the renderer.
		 */
		static unsigned int textureUnitCount;
		/**
		 * A pointer to the array storing each units id.
		 *
		 * <p>This is basically just an array of int counting from 0 to {@link #textureUnitCount} and is used
		 * to activate all texture banks before rendering.</p>
		 */
		static int *textureUnits;
		/**
		 * A pointer to the array storing the texture ids.
		 *
		 * <p>The size is determined by {@link #textureUnitCount} and each texture is bound to the unit with the same index.</p>
		 */
		static unsigned int *textures;
		/**
		 * The number of textures the current batch actually uses.
		 */
		static unsigned int textureCount;

		/**
		 * The id of the quad vertex array object on the graphics card.
		 */
		static unsigned int vaoId;
		/**
		 * The id of the unit quad vertex buffer object on the graphics card.
		 */
		static unsigned int quadVboId;
		/**
		 * The id of the vertex buffer object that stores the information about all instances rendered in this batch.
		 */
		static unsigned int instanceVboId;
		/**
		 * Creates a new 2D renderer.
		 */
		Renderer2D();

		/**
		 * Initializes the shader program.
		 *
		 * @param maxTextureUnits The maximum number of texture units.
		 *
		 * @throws ShaderCreationException if the vertex or fragment shader could not be created.
		 * @throws ShaderLinkException if the shader program could not be linked.
		 * @throws ShaderUniformException if one or more uniforms could not be created.
		 */
		static void initShader(int maxTextureUnits);

	public:

		/**
		 * Initializes the 2D renderer.
		 *
		 * @param batchSize The size of the batch.
		 *                  <p>If the quad count exceeds the size of the batch before the batch is flushed it will flush automatically and reset
		 *                  the {@link #nextQuad next quad pointer} the the start of the batch.</p>
		 * @param projectionMatrix A pointer to the orthographic projection matrix of the window.
		 */
		static void init(unsigned int batchSize, Matrix4f *projectionMatrix);

		/**
		 * Cleans up the renderer.
		 */
		static void cleanup();

		/**
		 * Declares the beginning of a batch.
		 *
		 * <p>This will set the {@link #nextQuad next quad pointer} to the beginning of the {@link #batch batch array},
		 * reset the {@link #quadCount quad count} to 0 and set the {@link #textureCount texture count} back to 1.</p>
		 */
		static void beginBatch();

		/**
		 * Uploads the data of the current batch to the vertex buffer object on the graphics card.
		 */
		static void endBatch();

		/**
		 * Renders all quads currently in the batch.
		 */
		static void flush();

		/**
		 * Draws a colored rectangle.
		 *
		 * <p>This will automatically flush the current and begin a new batch if the size of the batch is exceeded.</p>
		 *
		 * @param posX The x coordinate of the rectangle in pixel.
		 * @param posY The y coordinate of the rectangle in pixel.
		 * @param posZ The z index of the rectangle.
		 * @param width The width of the rectangle in pixel.
		 * @param height The height of the rectangle in pixel.
		 * @param color A pointer to the color of the rectangle.
		 */
		static void drawRect(float posX, float posY, float posZ, float width, float height, const Vector4f *color);

		/**
		 * Draws a textured rectangle.
		 *
		 * <p>This will automatically flush the current and begin a new batch if the size of the batch or the texture count
		 * is exceeded.<p>
		 *
		 * <p>For most efficient use, render rectangles using the same texture successively.</p>
		 *
		 * @param posX The x coordinate of the rectangle in pixel.
		 * @param posY The y coordinate of the rectangle in pixel.
		 * @param posZ The z index of the rectangle.
		 * @param width The width of the rectangle in pixel.
		 * @param height The height of the rectangle in pixel.
		 * @param uvX1 The x coordinate of the first corner of the uv section of the texture.
		 * @param uvY1 The y coordinate of the first corner of the uv section of the texture.
		 * @param uvX2 The x coordinate of the second corner of the uv section of the texture.
		 * @param uvY2 The y coordinate of the second corner of the uv section of the texture.
		 * @param texture A pointer to the 2 dimensional texture a section will be rendered of.
		 */
		static void drawTexturedRect(float posX, float posY, float posZ, float width, float height, float uvX1, float uvY1, float uvX2, float uvY2,
							  const Texture2D *texture);

		/**
		 * Draws a text.
		 *
		 * <p>The <code>alignment</code> should be a combination of a horizontal alignment:
		 * <ul>
		 *   <li>{@link CEDAR_ALIGNMENT_LEFT}</li>
		 *   <li>{@link CEDAR_ALIGNMENT_CENTER}</li>
		 *   <li>{@link CEDAR_ALIGNMENT_RIGHT}</li>
		 * </ul>
		 * and a vertical alignment:
		 * <ul>
		 *   <li>{@link CEDAR_ALIGNMENT_TOP}</li>
		 *   <li>{@link CEDAR_ALIGNMENT_MIDDLE}</li>
		 *   <li>{@link CEDAR_ALIGNMENT_BOTTOM}</li>
		 * </ul></p>
		 *
		 * @param posX The x coordinate of the text.
		 * @param posY The y coordinate of the text.
		 * @param posZ The z index of the text.
		 * @param text The string of the text.
		 * @param font A pointer to the font of the text.
		 * @param color A pointer to the color of the text.
		 * @param alignment The alignment of the text.
		 * @param size A pointer to a vector where the size of the text will be stored if it is not <code>nullptr</code>.
		 */
		static void drawText(float posX, float posY, float posZ, const std::string &text, Font *font, const Vector4f *color,
					  unsigned int alignment = CEDAR_ALIGNMENT_TOP | CEDAR_ALIGNMENT_LEFT, Vector2f *size = nullptr);

		/**
		 * Generates a text buffer that can be rendered many times.
		 *
		 * <p>This is much faster for static texts as the model does not have to be generated each frame.</p>
		 *
		 * <p>The <code>alignment</code> should be a combination of a horizontal alignment:
		 * <ul>
		 *   <li>{@link CEDAR_ALIGNMENT_LEFT}</li>
		 *   <li>{@link CEDAR_ALIGNMENT_CENTER}</li>
		 *   <li>{@link CEDAR_ALIGNMENT_RIGHT}</li>
		 * </ul>
		 * and a vertical alignment:
		 * <ul>
		 *   <li>{@link CEDAR_ALIGNMENT_TOP}</li>
		 *   <li>{@link CEDAR_ALIGNMENT_MIDDLE}</li>
		 *   <li>{@link CEDAR_ALIGNMENT_BOTTOM}</li>
		 * </ul></p>
		 *
		 * @param text The string of the text.
		 * @param font A pointer to the font of the text.
		 * @param alignment The alignment of the text.
		 * @return A pointer to the generated text buffer.
		 */
		static TextBuffer *generateTextBuffer(const std::string &text, Font *font, unsigned int alignment = CEDAR_ALIGNMENT_TOP | CEDAR_ALIGNMENT_LEFT);

		/**
		 * Draws the text stored in the text buffer.
		 *
		 * @param offsetX The offset applied to the text buffer on the x axis.
		 * @param offsetY The offset applied to the text buffer on the x axis.
		 * @param offsetZ The z index of the text.
		 * @param textBuffer A pointer to the text buffer that will be drawn.
		 * @param color A pointer to the color of the text.
		 */
		static void drawText(float offsetX, float offsetY, float offsetZ, const TextBuffer *textBuffer, const Vector4f *color);
	};
}

#endif //CEDAR_RENDERER2D_HPP
