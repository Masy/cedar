//
// Created by masy on 23.02.20.
//

#ifndef TALESOFCATVENTURE_TEXTURE2D_H
#define TALESOFCATVENTURE_TEXTURE2D_H

#include "cedar/Texture.h"

/**
 * Base namespace of the cedar engine.
 */
namespace cedar
{
	/**
	 * Class representing a 2 dimensional texture.
	 */
	class Texture2D : public Texture
	{
	protected:
		/**
		 * The width of the texture in pixel.
		 */
		int m_width;
		/**
		 * The height of the texture in pixel.
		 */
		int m_height;
		/**
		 * The number of samples each texel has.
		 *
		 * <p>If it is one, the texture is not multisampled.</p>
		 */
		int m_samples;
		/**
		 * The number of reserved levels.
		 *
		 * <p>This will be 0 unless you reserve storage on the graphics card via {@link #reserve(int)}.</p>
		 */
		int m_reservedLevels;

	public:
		/**
		 * Creates a new two dimensional texture.
		 *
		 * @param width The width of the texture.
		 * @param height The height of the texture.
		 * @param internalFormat The internal data format of the texture.
		 * @param target The target of the texture.
		 *
		 * @throws TextureCreationException if <code>target</code> is not a two dimensional target.
		 */
		Texture2D(int width, int height, int internalFormat = CEDAR_RGBA8, unsigned int target = CEDAR_TEXTURE_2D);

		/**
		 * Allocates memory for the texture on the graphics card.
		 *
		 * <p>The memory will be allocated for the current {@link #m_width}, {@link #m_height} and given amount of layers.
		 * This will make the texture <code>immutable</code>, which will cause a {@link TextureResizeException} if {@link #setSize(int, int)} is called.</p>
		 *
		 * @param levels The number of layers that will be allocated.
		 *               <p>This will only have an effect if {@link #m_target} is {@link CEDAR_TEXTURE_2D_ARRAY}.</p>
		 *
		 * @throws TextureInitException if the texture is already initialized.
		 * @throws TextureInitException if no texture id was returned by the graphics card.
		 */
		void reserve(int levels);

		/**
		 * Allocates memory for the texture on the graphics card.
		 *
		 * <p>The memory will be allocated for the current {@link #m_width}, {@link #m_height} and given amount of samples.
		 * This will make the texture <code>immutable</code>, which will cause a {@link TextureResizeException} if {@link #setSize(int, int)} is called.</p>
		 *
		 * <p>This will make the texture a multisampled texture, which means that it can only be rendered to. {@link #upload(unsigned int, unsigned int, const void*, int)}
		 * and {@link #upload(int, int, int, int, unsigned int, unsigned int, const void*, int)} will now also cause {@link TextureUploadException}s.</p>
		 *
		 * @param samples The number of samples each texel of the texture will have.
		 * @param fixedSampleLocations Whether the samples will be uniformly places inside each texel or not.
		 *
		 * @throws TextureInitException if the texture is already initialized.
		 * @throws TextureInitException if <code>samples</code> is smaller than two.
		 * @throws TextureInitException if no texture id was returned by the graphics card.
		 */
		void reserveMultisample(int samples, bool fixedSampleLocations = true);

		/**
		 * Initializes the texture on the graphics card with the given data.
		 *
		 * <p>If <code>data</code> is a nullptr, memory will be allocated for the texture but no data will be uploaded.</p>
		 *
		 * <p><code>format</code> should be one of the following formats, depending on the {@link #m_internalFormat}:
		 * <ul>
		 *   <li>{@link CEDAR_RED}</li>
		 *   <li>{@link CEDAR_RG}</li>
		 *   <li>{@link CEDAR_RGB}</li>
		 *   <li>{@link CEDAR_RGBA}</li>
		 *   <li>{@link CEDAR_DEPTH_COMPONENT}</li>
		 *   <li>{@link CEDAR_STENCIL_INDEX}</li>
		 * </ul>
		 * </p>
		 *
		 * <p><code>type</code> should be one of the following types:
		 * <ul>
		 *   <li>{@link CEDAR_UNSIGNED_BYTE}</li>
		 *   <li>{@link CEDAR_BYTE}</li>
		 *   <li>{@link CEDAR_UNSIGNED_SHORT}</li>
		 *   <li>{@link CEDAR_SHORT}</li>
		 *   <li>{@link CEDAR_UNSIGNED_INT}</li>
		 *   <li>{@link CEDAR_INT}</li>
		 *   <li>{@link CEDAR_FLOAT}</li>
		 * </ul>
		 *
		 * @param format The format of the provided data.
		 * @param type The type of the provided data.
		 * @param data The data that the texture will be initialized with or <code>nullptr</code> if just memory should be allocated.
		 *
		 * @throws TextureInitException if the texture is already initialized.
		 * @throws TextureInitException if no texture id was returned by the graphics card.
		 */
		void init(unsigned int format = CEDAR_RGBA, unsigned int type = CEDAR_UNSIGNED_BYTE, const void *data = nullptr);

		/**
		 * Initializes the texture on the graphics card.
		 *
		 * <p>This will make the texture a multisampled texture, which means that it can only be rendered to. {@link #upload(unsigned int, unsigned int, const void*, int)}
		 * and {@link #upload(int, int, int, int, unsigned int, unsigned int, const void*, int)} will now also cause {@link TextureUploadException}s.</p>
		 *
		 * @param samples The number of samples each texel of the texture will have.
		 * @param fixedSampleLocations Whether the samples will be uniformly places inside each texel or not.
		 *
		 * @throws TextureInitException if the texture is already initialized.
		 * @throws TextureInitException if <code>samples</code> is smaller than two.
		 * @throws TextureInitException if no texture id was returned by the graphics card.
		 */
		void initMultisample(int samples, bool fixedSampleLocations = true);

		/**
		 * Uploads the given data to the texture on the graphics card.
		 *
		 * <p><code>data</code> is expected to contain data for the whole texture.</p>
		 *
		 * <p><code>format</code> should be one of the following formats, depending on the {@link #m_internalFormat internal format}:
		 * <ul>
		 *   <li>{@link CEDAR_RED}</li>
		 *   <li>{@link CEDAR_RG}</li>
		 *   <li>{@link CEDAR_RGB}</li>
		 *   <li>{@link CEDAR_RGBA}</li>
		 *   <li>{@link CEDAR_DEPTH_COMPONENT}</li>
		 *   <li>{@link CEDAR_STENCIL_INDEX}</li>
		 * </ul>
		 * </p>
		 *
		 * <p><code>type</code> should be one of the following types:
		 * <ul>
		 *   <li>{@link CEDAR_UNSIGNED_BYTE}</li>
		 *   <li>{@link CEDAR_BYTE}</li>
		 *   <li>{@link CEDAR_UNSIGNED_SHORT}</li>
		 *   <li>{@link CEDAR_SHORT}</li>
		 *   <li>{@link CEDAR_UNSIGNED_INT}</li>
		 *   <li>{@link CEDAR_INT}</li>
		 *   <li>{@link CEDAR_FLOAT}</li>
		 * </ul>
		 *
		 * @param format The format of the provided data.
		 * @param type The type of the provided data.
		 * @param data The data that will be uploaded to the texture.
		 * @param level The level on which the data will be uploaded to.
		 *               <p>This will only have an effect if {@link #m_target} is {@link CEDAR_TEXTURE_2D_ARRAY}, otherwise this should be <code>0</code>.</p>
		 *
		 * @throws TextureUploadException if the texture is not initialized.
		 * @throws TextureUploadException if {@link #m_samples} is greater than one.
		 * @throws TextureUploadException if <code>width</code> or <code>height</code> is smaller than one.
		 * @throws TextureUploadException if the texture has reserved levels and <code>levels</code> is greater than the reserved amount.
		 */
		void upload(unsigned int format, unsigned int type, const void *data, int level = 0);

		/**
		 * Uploads the given section of data to the texture on the graphics card with the given offset.
		 *
		 * <p><code>data</code> is expected to contain data for the region specified by <code>width</code> and <code>height</code>.</p>
		 *
		 * <p><code>format</code> should be one of the following formats, depending on the {@link #m_internalFormat internal format}:
		 * <ul>
		 *   <li>{@link CEDAR_RED}</li>
		 *   <li>{@link CEDAR_RG}</li>
		 *   <li>{@link CEDAR_RGB}</li>
		 *   <li>{@link CEDAR_RGBA}</li>
		 *   <li>{@link CEDAR_DEPTH_COMPONENT}</li>
		 *   <li>{@link CEDAR_STENCIL_INDEX}</li>
		 * </ul>
		 * </p>
		 *
		 * <p><code>type</code> should be one of the following types:
		 * <ul>
		 *   <li>{@link CEDAR_UNSIGNED_BYTE}</li>
		 *   <li>{@link CEDAR_BYTE}</li>
		 *   <li>{@link CEDAR_UNSIGNED_SHORT}</li>
		 *   <li>{@link CEDAR_SHORT}</li>
		 *   <li>{@link CEDAR_UNSIGNED_INT}</li>
		 *   <li>{@link CEDAR_INT}</li>
		 *   <li>{@link CEDAR_FLOAT}</li>
		 * </ul>
		 *
		 * @param offsetX The x offset to the origin of the texture where the section will be uploaded to.
		 * @param offsetY The y offset to the origin of the texture where the section will be uploaded to.
		 * @param width The width of the section that will be uploaded to the texture.
		 * @param height The height of the section that will be uploaded to the texture.
		 * @param format The format of the provided data.
		 * @param type The type of the provided data.
		 * @param data The data that will be uploaded to the texture.
		 * @param level The level on which the data will be uploaded to.
		 *              <p>This will only have an effect if {@link #m_target} is {@link CEDAR_TEXTURE_2D_ARRAY}, otherwise this should be <code>0</code>.</p>
		 *
		 * @throws TextureUploadException if the texture is not initialized.
		 * @throws TextureUploadException if {@link #m_samples} is greater than one.
		 * @throws TextureUploadException if <code>width</code> or <code>height</code> is smaller than one.
		 * @throws TextureUploadException if the texture has reserved levels and <code>levels</code> is greater than the reserved amount.
		 */
		void upload(int offsetX, int offsetY, int width, int height, unsigned int format, unsigned int type, const void *data, int level = 0);

		/**
		 * Gets the width of the texture.
		 *
		 * @return The width of the texture.
		 */
		[[nodiscard]] int getWidth() const;

		/**
		 * Gets the height of the texture.
		 *
		 * @return The height of the texture.
		 */
		[[nodiscard]] int getHeight() const;

		/**
		 * Sets the size of the texture.
		 *
		 * <p>If <code>keepData</code> is true and the new size is smaller than the old one the image is cropped.</p>
		 *
		 * @param newWidth The new width of the texture.
		 * @param newHeight The new height of the texture.
		 * @param keepData If this is true, the data of the texture will stay.
		 * @throws TextureResizeException if the texture is <code>immutable</code>.
		 */
		void setSize(int newWidth, int newHeight, bool keepData = false);

		/**
		 * Checks whether the texture is multisampled or not.
		 *
		 * @return <code>true</code> if {@link #m_samples} is greater than one.
		 */
		[[nodiscard]] bool isMultisample() const;

		/**
		 * Gets the number of samples of the texture.
		 *
		 * @return The number of samples of the texture.
		 */
		[[nodiscard]] int getSamples() const;

		/**
		 * Gets the number of reserved levels of the texture.
		 *
		 * @return The number of reserved levels of the texture.
		 */
		[[nodiscard]] int getReservedLevels() const;
	};
}

#endif //TALESOFCATVENTURE_TEXTURE2D_H
