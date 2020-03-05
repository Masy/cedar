//
// Created by masy on 23.02.20.
//

#ifndef CEDAR_TEXTURE_H
#define CEDAR_TEXTURE_H

#include "cedar/XException.h"
#include "cedar/GLConstants.h"

/**
 * Base namespace of the cedar engine.
 */
namespace cedar
{
	/**
	 * Base class for all texture related exceptions.
	 */
	class TextureException : public XException
	{
	public:
		/**
		 * Creates a new texture exception.
		 *
		 * @param message The message of the exception.
		 */
		explicit TextureException(const std::string &message);
	};

	/**
	 * Exception which is thrown when a texture could not be created.
	 */
	class TextureCreationException : public TextureException
	{
	public:
		/**
		 * Creates a new texture creation exception.
		 *
		 * @param message The message of the exception.
		 */
		explicit TextureCreationException(const std::string &message);
	};

	/**
	 * Exception which is thrown when a texture could not be initialized.
	 */
	class TextureInitException : public TextureException
	{
	public:
		/**
		 * Creates a new texture init exception.
		 *
		 * @param message The message of the exception.
		 */
		explicit TextureInitException(const std::string &message);
	};

	/**
	 * Exception which is thrown when a texture could not be resized.
	 */
	class TextureResizeException : public TextureException
	{
	public:
		/**
		 * Creates a new texture resize exception.
		 *
		 * @param message The message of the exception.
		 */
		explicit TextureResizeException(const std::string &message);
	};

	/**
	 * Exception which is thrown when data could not be uploaded to a texture.
	 */
	class TextureUploadException : public TextureException
	{
	public:
		/**
		 * Creates a new texture upload exception.
		 *
		 * @param message The message of the exception.
		 */
		explicit TextureUploadException(const std::string &message);
	};

	/**
	 * Exception which is thrown when a parameter could not be set.
	 */
	class TextureParameterException : public TextureException
	{
	public:
		/**
		 * Creates a new texture parameter exception.
		 *
		 * @param message The message of the exception.
		 */
		explicit TextureParameterException(const std::string &message);
	};

	/**
	 * Base class for all textures.
	 */
	class Texture
	{
	protected:
		/**
		 * The id of the texture on the graphics card.
		 */
		unsigned int m_textureId;
		/**
		 * The target of the texture.
		 *
		 * <p>Can be one of the following targets, depending on the class extension:
		 * <table>
		 *   <tr><th>Texture1D</th><th>Texture2D</th><th>Texture3D</th></tr>
		 *   <tr><td>{@link #CEDAR_TEXTURE_1D}</td><td>{@link #CEDAR_TEXTURE_2D}</td><td>{@link #CEDAR_TEXTURE_3D}</td></tr>
		 *   <tr><td>{@link #CEDAR_PROXY_TEXTURE_1D</td><td>{@link #CEDAR_PROXY_TEXTURE_2D</td><td>{@link #CEDAR_PROXY_TEXTURE_3D</td></tr>
		 *   <tr><td/><td>{@link #CEDAR_TEXTURE_1D_ARRAY</td><td>{@link #CEDAR_TEXTURE_2D_ARRAY}</td></tr>
		 *   <tr><td/><td>{@link #CEDAR_TEXTURE_2D_MULTISAMPLE}</td><td/></tr>
		 *   <tr><td/><td>{@link #CEDAR_PROXY_TEXTURE_2D_MULTISAMPLE}</td><td/></tr>
		 *   <tr><td/><td>{@link #CEDAR_TEXTURE_2D_MULTISAMPLE_ARRAY}</td><td/></tr>
		 *   <tr><td/><td>{@link #CEDAR_PROXY_TEXTURE_2D_MULTISAMPLE_ARRAY}</td><td/></tr>
		 *   <tr><td/><td>{@link #CEDAR_TEXTURE_RECTANGLE}</td><td/></tr>
		 *   <tr><td/><td>{@link #CEDAR_PROXY_TEXTURE_RECTANGLE}</td><td/></tr>
		 *   <tr><td/><td>{@link #CEDAR_TEXTURE_CUBE_MAP}</td><td/></tr>
		 *   <tr><td/><td>{@link #CEDAR_PROXY_TEXTURE_CUBE_MAP}</td><td/></tr>
		 *   <tr><td/><td>{@link #CEDAR_TEXTURE_CUBE_MAP_ARRAY}</td><td/></tr>
		 *   <tr><td/><td>{@link #CEDAR_PROXY_TEXTURE_CUBE_MAP_ARRAY}</td><td/></tr>
		 *   <tr><td/><td>{@link #CEDAR_TEXTURE_CUBE_MAP_POSITIVE_X}</td><td/></tr>
		 *   <tr><td/><td>{@link #CEDAR_TEXTURE_CUBE_MAP_NEGATIVE_X}</td><td/></tr>
		 *   <tr><td/><td>{@link #CEDAR_TEXTURE_CUBE_MAP_POSITIVE_Y}</td><td/></tr>
		 *   <tr><td/><td>{@link #CEDAR_TEXTURE_CUBE_MAP_NEGATIVE_Y}</td><td/></tr>
		 *   <tr><td/><td>{@link #CEDAR_TEXTURE_CUBE_MAP_POSITIVE_Z}</td><td/></tr>
		 *   <tr><td/><td>{@link #CEDAR_TEXTURE_CUBE_MAP_NEGATIVE_Z}</td><td/></tr>
		 * </table></p>
		 */
		unsigned int m_target;
		/**
		 * The internal format of the texture.
		 *
		 * <p>The format should either be a <code>generic</code> sized format or a <code>specific</code> sized format.
		 * If the format is a <code>generic</code> format, the graphics card will will choose a <code>specific</code> format itself.</p>
		 */
		int m_internalFormat;
		/**
		 * Whether the texture is a depth texture or not.
		 *
		 * <p>This is based on the <code>internal format</code> of the texture.</p>
		 */
		bool m_depthTexture;
		/**
		 * Whether the texture is a stencil texture or not.
		 *
		 * <p>This is based on the <code>internal format</code> of the texture.</p>
		 */
		bool m_stencilTexture;
		/**
		 * Whether the texture is immutable or not.
		 *
		 * <p>A texture will become immutable if it is created with a <code>reserve<code> method.
		 * Immutable in this context only means that the size and layer count can not change anymore, you can however still
		 * upload data to it.</p>
		 */
		bool m_immutable;

		/**
		 * Creates a new texture.
		 *
		 * @param internalFormat The internal format of the texture.
		 * @param target The target of the texture.
		 */
		Texture(int internalFormat, unsigned int target);

	public:
		/**
		 * Gets the unsized internal format of the given sized internal format.
		 *
		 * @param sizedInternalFormat The sized internal format that will be converted.
		 * @return The unsized internal format of the given sized internal format.
		 */
		static unsigned int sizedToUnsized(unsigned int sizedInternalFormat);
		/**
		 * Destroys the texture.
		 *
		 * <p>This will also free the memory of the texture on the graphics card.</p>
		 */
		virtual ~Texture();

		/**
		 * Gets the id of the texture on the graphics card.
		 *
		 * @return the id of the texture on the graphics card.
		 */
		[[nodiscard]] unsigned int getId() const;

		/**
		 * Gets the target of the texture.
		 *
		 * @return the target of the texture.
		 */
		[[nodiscard]] unsigned int getTarget() const;

		/**
		 * Gets the internal format of the texture.
		 *
		 * @return the internal format of the texture.
		 */
		[[nodiscard]] int getInternalFormat() const;

		/**
		 * Checks whether the texture is a depth texture or not.
		 *
		 * @return <code>true</code> if the texture is a depth texture.
		 */
		[[nodiscard]] bool isDepthTexture() const;

		/**
		 * Checks whether the texture is a stencil texture or not.
		 *
		 * @return <code>true</code> if the texture is a stencil texture-
		 */
		[[nodiscard]] bool isStencilTexture() const;

		/**
		 * Checks whether the texture is a depth and a stencil texture.
		 *
		 * @return <code>true</code> if the texture is a depth and a stencil texture.
		 */
		[[nodiscard]] bool isDepthAndStencilTexture() const;

		/**
		 * Checks whether the texture is immutable.
		 *
		 * @return <code>true</code> if the texture is immutable.
		 */
		[[nodiscard]] bool isImmutable() const;

		/**
		 * Sets the given parameter of the texture to the given integer value.
		 *
		 * @param parameter The parameter that will be set.
		 * @param value The new value of the parameter.
		 *
		 * @throws TextureParameterException if the texture is not initialized yet.
		 */
		void setParameteri(unsigned int parameter, int value) const;
		/**
		 * Sets the given parameter of the texture to the given float value.
		 *
		 * @param parameter The parameter that will be set.
		 * @param value The new value of the parameter.
		 *
		 * @throws TextureParameterException if the texture is not initialized yet.
		 */
		void setParameterf(unsigned int parameter, float value) const;
		/**
		 * Sets the given parameter of the texture to the given integer values.
		 *
		 * @param parameter The parameter that will be set.
		 * @param value The new values of the parameter.
		 *
		 * @throws TextureParameterException if the texture is not initialized yet.
		 */
		void setParameteriv(unsigned int parameter, const int *values) const;
		/**
		 * Sets the given parameter of the texture to the given float values.
		 *
		 * @param parameter The parameter that will be set.
		 * @param value The new values of the parameter.
		 *
		 * @throws TextureParameterException if the texture is not initialized yet.
		 */
		void setParameterfv(unsigned int parameter, const float *values) const;
		/**
		 * Sets the given parameter of the texture to the given integer values without modifying them.
		 *
		 * @param parameter The parameter that will be set.
		 * @param value The new values of the parameter.
		 *
		 * @throws TextureParameterException if the texture is not initialized yet.
		 */
		void setParameterIiv(unsigned int parameter, const int *values) const;
		/**
		 * Sets the given parameter of the texture to the given unsigned integer values without modifying them.
		 *
		 * @param parameter The parameter that will be set.
		 * @param value The new values of the parameter.
		 *
		 * @throws TextureParameterException if the texture is not initialized yet.
		 */
		void setParameterIuiv(unsigned int parameter, const unsigned int *values) const;

		/**
		 * Checks whether two textures are wrappers of the same texture on the graphics card.
		 *
		 * <p>The {@link #m_textureId} is compared to check if the two textures are the same.</p>
		 *
		 * @param other The other texture.
		 * @return <code>true</code> if the textures are wrapper of the same texture on the graphics card.
		 */
		bool operator ==(const Texture& other) const;
	};
}

#endif //CEDAR_TEXTURE_H
