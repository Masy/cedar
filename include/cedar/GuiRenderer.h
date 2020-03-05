//
// Created by masy on 23.02.20.
//

#ifndef CEDAR_GUIRENDERER_H
#define CEDAR_GUIRENDERER_H

#include "cedar/Vector4f.h"
#include "cedar/ShaderProgram.h"
#include "cedar/Matrix4f.h"
#include "cedar/Texture2D.h"
#include "cedar/Quad.h"
#include "cedar/Font.h"

/**
 * Defines the horizontal alignment to be left.
 */
#define CEDAR_ALIGNMENT_LEFT 0x00
/**
 * Defines the horizontal alignment to be center.
 */
#define CEDAR_ALIGNMENT_CENTER 0x01
/**
 * Defines the horizontal alignment to be right.
 */
#define CEDAR_ALIGNMENT_RIGHT 0x02
/**
 * Defines the vertical alignment to be top.
 */
#define CEDAR_ALIGNMENT_TOP 0x00
/**
 * Defines the vertical alignment to be middle
 */
#define CEDAR_ALIGNMENT_MIDDLE 0x04
/**
 * Defines the vertical alignment to be bottom.
 */
#define CEDAR_ALIGNMENT_BOTTOM 0x08

/**
 * Base namespace of the cedar engine.
 */
namespace cedar
{

	/**
	 * Class for rendering 2 dimensional GUI elements.
	 */
	class GuiRenderer
	{
	private:
		/**
		 * A pointer to the shader program the renderer uses to render the elements.
		 */
		ShaderProgram *m_shader;
		/**
		 * A pointer to the uniform locations of the shader program.
		 */
		int *m_uniformLocations;
		/**
		 * A pointer to the orthographic projection matrix of the window.
		 */
		Matrix4f *m_projectionMatrix;
		/**
		 * A pointer to the default texture.
		 *
		 * <p>The default texture is always a white 1x1 square to render colored quads without any texture.</p>
		 */
		Texture2D *m_defaultTexture;

		/**
		 * A pointer to the batch array of the renderer.
		 *
		 * <p>The size of the array is fixed and will not be reallocated at any time.</p>
		 */
		Quad *m_batch;
		/**
		 * A pointer to the next quad that will be written to the batch.
		 */
		Quad *m_nextQuad;
		/**
		 * The number of quads currently used by the batch.
		 */
		unsigned int m_quadCount;
		/**
		 * The size of the {@link #m_batch batch array}.
		 */
		unsigned int m_batchSize;

		/**
		 * The number of texture units used by the renderer.
		 */
		unsigned int m_textureUnitCount;
		/**
		 * A pointer to the array storing each units id.
		 *
		 * <p>This is basically just an array of int counting from 0 to {@link #m_textureUnitCount} and is used
		 * to activate all texture banks before rendering.</p>
		 */
		int *m_textureUnits;
		/**
		 * A pointer to the array storing the texture ids.
		 *
		 * <p>The size is determined by {@link #m_textureUnitCount} and each texture is bound to the unit with the same index.</p>
		 */
		unsigned int *m_textures;
		/**
		 * The number of textures the current batch actually uses.
		 */
		unsigned int m_textureCount;

		/**
		 * The id of the quad vertex array object on the graphics card.
		 */
		unsigned int m_vaoId;
		/**
		 * The id of the unit quad vertex buffer object on the graphics card.
		 */
		unsigned int m_quadVboId;
		/**
		 * The id of the vertex buffer object that stores the information about all instances rendered in this batch.
		 */
		unsigned int m_instanceVboId;

		/**
		 * Initializes the shader program.
		 *
		 * @throws ShaderCreationException if the vertex or fragment shader could not be created.
		 * @throws ShaderLinkException if the shader program could not be linked.
		 * @throws ShaderUniformException if one or more uniforms could not be created.
		 */
		void initShader();

	public:
		/**
		 * Creates a new gui renderer.
		 */
		GuiRenderer();

		/**
		 * Destroys the gui renderer.
		 */
		~GuiRenderer();

		/**
		 * Initializes the gui renderer.
		 *
		 * @param batchSize The size of the batch.
		 *                  <p>If the quad count exceeds the size of the batch before the batch is flushed it will flush automatically and reset
		 *                  the {@link #m_nextQuad next quad pointer} the the start of the batch.</p>
		 * @param projectionMatrix A pointer to the orthographic projection matrix of the window.
		 */
		void init(unsigned int batchSize, Matrix4f *projectionMatrix);

		/**
		 * Declares the beginning of a batch.
		 *
		 * <p>This will set the {@link #m_nextQuad next quad pointer} to the beginning of the {@link #m_batch batch array},
		 * reset the {@link #m_quadCount quad count} to 0 and set the {@link #m_textureCount texture count} back to 1.</p>
		 */
		void beginBatch();

		/**
		 * Uploads the data of the current batch to the vertex buffer object on the graphics card.
		 */
		void endBatch();

		/**
		 * Renders all quads currently in the batch.
		 */
		void flush();

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
		void drawRect(float posX, float posY, float posZ, float width, float height, const Vector4f *color);

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
		void drawTexturedRect(float posX, float posY, float posZ, float width, float height, float uvX1, float uvY1, float uvX2, float uvY2,
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
		 */
		void drawText(float posX, float posY, float posZ, const std::string &text, Font *font, const Vector4f *color,
					  unsigned int alignment = CEDAR_ALIGNMENT_TOP | CEDAR_ALIGNMENT_LEFT);

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
		 * @param color A pointer to the color of the text.
		 * @param alignment The alignment of the text.
		 * @return A pointer to the generated text buffer.
		 */
		TextBuffer *generateTextBuffer(const std::string &text, Font *font, const Vector4f *color, unsigned int alignment = CEDAR_ALIGNMENT_TOP | CEDAR_ALIGNMENT_LEFT);

		/**
		 * Draws the text stored in the text buffer.
		 *
		 * @param offsetX The offset applied to the text buffer on the x axis.
		 * @param offsetY The offset applied to the text buffer on the x axis.
		 * @param offsetZ The z index of the text.
		 * @param textBuffer A pointer to the text buffer that will be drawn.
		 */
		void drawText(float offsetX, float offsetY, float offsetZ, const TextBuffer *textBuffer);
	};
}

#endif //CEDAR_GUIRENDERER_H
