//
// Created by masy on 08.02.20.
//

#ifndef CEDAR_SHADERPROGRAM_H
#define CEDAR_SHADERPROGRAM_H

#include "cedar/XException.h"
#include "cedar/GLConstants.h"
// Since Vector4X includes Vector3X and Vector3X includes Vector2X i only include the 4 dimensional ones
#include "Vector4i.h"
#include "Vector4ui.h"
#include "Vector4f.h"
#include "Vector4d.h"
#include "Matrix4f.h"
#include <map>

/**
 * Base namespace of the cedar engine.
 */
namespace cedar
{
	/**
	 * Base class for all shader program related exceptions.
	 */
	class ShaderProgramException : public XException
	{
	public:
		/**
		 * Creates a new shader program exception.
		 *
		 * @param message The message of the exception.
		 */
		explicit ShaderProgramException(const std::string &message);
	};

	/**
	 * Exception which is thrown when a shader program could not be created.
	 */
	class ShaderProgramCreationException : public ShaderProgramException
	{
	public:
		/**
		 * Creates a new shader program creation exception.
		 *
		 * @param message The message of the exception.
		 */
		explicit ShaderProgramCreationException(const std::string &message);
	};

	/**
	 * Exception which is thrown when a shader could not be created.
	 */
	class ShaderCreationException : public ShaderProgramException
	{
	public:
		/**
		 * Creates a new shader creation exception.
		 *
		 * @param message The message of the exception.
		 */
		explicit ShaderCreationException(const std::string &message);
	};

	/**
	 * Exception which is thrown when a shader could not be compiled.
	 */
	class ShaderCompileException : public ShaderProgramException
	{
	public:
		/**
		 * Constructs a new shader compile exception.
		 *
		 * @param message The message of the exception.
		 */
		explicit ShaderCompileException(const std::string &message);
	};

	/**
	 * Exception which is thrown when a shader program could not be linked.
	 */
	class ShaderProgramLinkException : public ShaderProgramException
	{
	public:
		/**
		 * Creates a new shader program link exception.
		 *
		 * @param message The message of the exception.
		 */
		explicit ShaderProgramLinkException(const std::string &message);
	};

	/**
	 * Exception which is thrown when a uniform could not be created.
	 */
	class UniformCreationException : public ShaderProgramException
	{
	public:
		/**
		 * Creates a new uniform creation exception.
		 *
		 * @param message The message of the exception.
		 */
		explicit UniformCreationException(const std::string &message);
	};

	/**
	 * Class representing an OpenGL shader program.
	 */
	class ShaderProgram
	{
	private:
		/**
		 * The id of the shader program on the graphics card.
		 */
		unsigned int m_shaderProgramId;
		/**
		 * The if of the vertex shader on the graphics card.
		 *
		 * <p>If this is 0 that the shader program doesn't have a vertex shader.</p>
		 */
		unsigned int m_vertexShaderId;
		/**
		 * The if of the geometry shader on the graphics card.
		 *
		 * <p>If this is 0 that the shader program doesn't have a geometry shader.</p>
		 */
		unsigned int m_geometryShaderId;
		/**
		 * The if of the fragment shader on the graphics card.
		 *
		 * <p>If this is 0 that the shader program doesn't have a fragment shader.</p>
		 */
		unsigned int m_fragmentShaderId;
		/**
		 * The if of the compute shader on the graphics card.
		 *
		 * <p>If this is 0 that the shader program doesn't have a compute shader.</p>
		 */
		unsigned int m_computeShaderId;
		/**
		 * Whether the shader program is linked or not.
		 */
		bool m_linked;

		/**
		 * A map which maps names of uniforms to the id of them on the graphics card.
		 */
		std::map<const char *, int> m_uniforms;

		/**
		 * Creates a shader of the given type.
		 *
		 * <p>The <code>type</code> of the shader must be one of the following types:
		 * <ul>
		 *   <li>{@link CEDAR_VERTEX_SHADER}</li>
		 *   <li>{@link CEDAR_GEOMETRY_SHADER}</li>
		 *   <li>{@link CEDAR_FRAGMENT_SHADER}</li>
		 *   <li>{@link CEDAR_COMPUTE_SHADER}</li>
		 * </ul>
		 *
		 * @param source The source code of the shader.
		 * @param type The type of the shader.
		 * @return the id of the shader on the graphics card.
		 *
		 * @throws ShaderCreationException if the graphics card couldn't allocate memory for the shader.
		 * @throws ShaderCompileException if the shader source code couldn't be compiled.
		 */
		unsigned int createShader(const std::string &source, unsigned int type);

	public:
		/**
		 * Creates a new shader program.
		 *
		 * @throws ShaderProgramCreationException if the graphics card couldn't allocate memory for the shader program.
		 */
		ShaderProgram();

		/**
		 * Destroys the shader program.
		 */
		~ShaderProgram();

		/**
		 * Creates a new vertex shader.
		 *
		 * @param source The source code of the vertex shader.
		 *
		 * @throws ShaderCreationException if the shader program is already linked.
		 */
		void createVertexShader(const std::string &source);

		/**
		 * Creates a new geometry shader.
		 *
		 * @param source The source code of the geometry shader.
		 *
		 * @throws ShaderCreationException if the shader program is already linked.
		 */
		void createGeometryShader(const std::string &source);

		/**
		 * Creates a new fragment shader.
		 *
		 * @param source The source code of the fragment shader.
		 *
		 * @throws ShaderCreationException if the shader program is already linked.
		 */
		void createFragmentShader(const std::string &source);

		/**
		 * Creates a new compute shader.
		 *
		 * @param source The source code of the compute shader.
		 *
		 * @throws ShaderCreationException if the shader program is already linked.
		 */
		void createComputeShader(const std::string &source);

		/**
		 * Links the shader program.
		 *
		 * @throws ShaderProgramLinkException if the shader program is already linked or the graphics card returns an invalid status.
		 */
		void link();

		/**
		 * Creates the given uniforms.
		 *
		 * @param count The number of uniforms that will be created.
		 * @param uniforms A Pointer to the array of names of the uniforms.
		 * @param uniformLocations A pointer to where the ids of each uniform will be stored.
		 *
		 * @throws UniformCreationException if the graphics card couldn't create a uniform.
		 */
		void createUniforms(unsigned int count, const char **uniforms, int *uniformLocations);

		/**
		 * Binds the shader program.
		 */
		void bind() const;

		/**
		 * Unbinds the shader program.
		 */
		void unbind() const;

		/**
		 * Sets the uniform at the given location to the given integer.
		 *
		 * @param location The location of the uniform that will be set.
		 * @param value The value of the uniform.
		 */
		void setUniform1i(int location, int value) const;

		/**
		 * Sets the uniform at the given location to the given integer array.
		 *
		 * @param location The location of the uniform that will be set.
		 * @param count The size of the array.
		 * @param values A pointer to the integer array that will be the value of the uniform.
		 */
		void setUniform1iv(int location, unsigned int count, const int *values) const;

		/**
		 * Sets the uniform at the given location to the given unsigned integer.
		 *
		 * @param location The location of the uniform that will be set.
		 * @param value The value of the uniform.
		 */
		void setUniform1ui(int location, unsigned int value);

		/**
		 * Sets the uniform at the given location to the given unsigned integer array.
		 *
		 * @param location The location of the uniform that will be set.
		 * @param count The size of the array.
		 * @param values A pointer to the unsigned integer array that will be the value of the uniform.
		 */
		void setUniform1uiv(int location, unsigned int count, const unsigned int *values) const;

		/**
		 * Sets the uniform at the given location to the given float.
		 *
		 * @param location The location of the uniform that will be set.
		 * @param value The value of the uniform.
		 */
		void setUniform1f(int location, float value) const;

		/**
		 * Sets the uniform at the given location to the given float array.
		 *
		 * @param location The location of the uniform that will be set.
		 * @param count The size of the array.
		 * @param values A pointer to the float array that will be the value of the uniform.
		 */
		void setUniform1fv(int location, unsigned int count, const float *values) const;

		/**
		 * Sets the uniform at the given location to the given double.
		 *
		 * @param location The location of the uniform that will be set.
		 * @param value The value of the uniform.
		 */
		void setUniform1d(int location, double value) const;

		/**
		 * Sets the uniform at the given location to the given double array.
		 *
		 * @param location The location of the uniform that will be set.
		 * @param count The size of the array.
		 * @param values A pointer to the double array that will be the value of the uniform.
		 */
		void setUniform1dv(int location, unsigned int count, const double *values) const;

		/**
		 * Sets the uniform at the given location to the given <code>ivec2</code>.
		 *
		 * @param location The location of the uniform that will be set.
		 * @param x The x coordinate of the <code>ivec2</code> uniform.
		 * @param y The y coordinate of the <code>ivec2</code> uniform.
		 */
		void setUniform2i(int location, int x, int y) const;

		/**
		 * Sets the uniform at the given location to the given <code>ivec2</code>.
		 *
		 * @param location The location of the uniform that will be set.
		 * @param value The value of the <code>ivec2</code> uniform.
		 */
		void setUniform2i(int location, const Vector2i &value) const;

		/**
		 * Sets the uniform at the given location to the given <code>ivec2[]</code>.
		 *
		 * @param location The location of the uniform that will be set.
		 * @param count The size of the array.
		 * @param values A pointer to the int array that will be the <code>ivec2[]</code> uniform.
		 */
		void setUniform2iv(int location, unsigned int count, const int *values) const;

		/**
		 * Sets the uniform at the given location to the given <code>ivec2[]</code>.
		 *
		 * @param location The location of the uniform that will be set.
		 * @param count The size of the array.
		 * @param values A pointer to the <code>Vector2i</code> array that will be the <code>ivec2[]</code> uniform.
		 */
		void setUniform2iv(int location, unsigned int count, const Vector2i *values) const;

		/**
		 * Sets the uniform at the given location to the given <code>uvec2</code>.
		 *
		 * @param location The location of the uniform that will be set.
		 * @param x The x coordinate of the <code>uvec2</code> uniform.
		 * @param y The y coordinate of the <code>uvec2</code> uniform.
		 */
		void setUniform2ui(int location, unsigned int x, unsigned int y) const;

		/**
		 * Sets the uniform at the given location to the given <code>uvec2</code>.
		 *
		 * @param location The location of the uniform that will be set.
		 * @param value The value of the <code>uvec2</code> uniform.
		 */
		void setUniform2ui(int location, const Vector2ui &value) const;

		/**
		 * Sets the uniform at the given location to the given <code>uvec2[]</code>.
		 *
		 * @param location The location of the uniform that will be set.
		 * @param count The size of the array.
		 * @param values A pointer to the unsigned int array that will be the <code>uvec2[]</code> uniform.
		 */
		void setUniform2uiv(int location, unsigned int count, const unsigned int *values) const;

		/**
		 * Sets the uniform at the given location to the given <code>uvec2[]</code>.
		 *
		 * @param location The location of the uniform that will be set.
		 * @param count The size of the array.
		 * @param values A pointer to the <code>Vector2ui</code> array that will be the <code>uvec2[]</code> uniform.
		 */
		void setUniform2uiv(int location, unsigned int count, const Vector2ui *values) const;

		/**
		 * Sets the uniform at the given location to the given <code>vec2</code>.
		 *
		 * @param location The location of the uniform that will be set.
		 * @param x The x coordinate of the <code>vec2</code> uniform.
		 * @param y The y coordinate of the <code>vec2</code> uniform.
		 */
		void setUniform2f(int location, float x, float y) const;

		/**
		 * Sets the uniform at the given location to the given <code>vec2</code>.
		 *
		 * @param location The location of the uniform that will be set.
		 * @param value The value of the <code>vec2</code> uniform.
		 */
		void setUniform2f(int location, const Vector2f &value) const;

		/**
		 * Sets the uniform at the given location to the given <code>vec2[]</code>.
		 *
		 * @param location The location of the uniform that will be set.
		 * @param count The size of the array.
		 * @param values A pointer to the float array that will be the <code>vec2[]</code> uniform.
		 */
		void setUniform2fv(int location, unsigned int count, const float *values) const;

		/**
		 * Sets the uniform at the given location to the given <code>vec2[]</code>.
		 *
		 * @param location The location of the uniform that will be set.
		 * @param count The size of the array.
		 * @param values A pointer to the <code>Vector2f</code> array that will be the <code>vec2[]</code> uniform.
		 */
		void setUniform2fv(int location, unsigned int count, const Vector2f *values) const;

		/**
		 * Sets the uniform at the given location to the given <code>vec2</code>.
		 *
		 * @param location The location of the uniform that will be set.
		 * @param x The x coordinate of the <code>dvec2</code> uniform.
		 * @param y The y coordinate of the <code>dvec2</code> uniform.
		 */
		void setUniform2d(int location, double x, double y) const;

		/**
		 * Sets the uniform at the given location to the given <code>dvec2</code>.
		 *
		 * @param location The location of the uniform that will be set.
		 * @param value The value of the <code>dvec2</code> uniform.
		 */
		void setUniform2d(int location, const Vector2d &value) const;

		/**
		 * Sets the uniform at the given location to the given <code>dvec2[]</code>.
		 *
		 * @param location The location of the uniform that will be set.
		 * @param count The size of the array.
		 * @param values A pointer to the double array that will be the <code>dvec2[]</code> uniform.
		 */
		void setUniform2dv(int location, unsigned int count, const double *values) const;

		/**
		 * Sets the uniform at the given location to the given <code>dvec2[]</code>.
		 *
		 * @param location The location of the uniform that will be set.
		 * @param count The size of the array.
		 * @param values A pointer to the <code>Vector2d</code> array that will be the <code>dvec2[]</code> uniform.
		 */
		void setUniform2dv(int location, unsigned int count, const Vector2d *values) const;

		/**
		 * Sets the uniform at the given location to the given <code>ivec3</code>.
		 *
		 * @param location The location of the uniform that will be set.
		 * @param x The x coordinate of the <code>ivec3</code> uniform.
		 * @param y The y coordinate of the <code>ivec3</code> uniform.
		 * @param y The z coordinate of the <code>ivec3</code> uniform.
		 */
		void setUniform3i(int location, int x, int y, int z) const;

		/**
		 * Sets the uniform at the given location to the given <code>ivec3</code>.
		 *
		 * @param location The location of the uniform that will be set.
		 * @param value The value of the <code>ivec3</code> uniform.
		 */
		void setUniform3i(int location, const Vector3i &value) const;

		/**
		 * Sets the uniform at the given location to the given <code>ivec3[]</code>.
		 *
		 * @param location The location of the uniform that will be set.
		 * @param count The size of the array.
		 * @param values A pointer to the int array that will be the <code>ivec3[]</code> uniform.
		 */
		void setUniform3iv(int location, unsigned int count, const int *values) const;

		/**
		 * Sets the uniform at the given location to the given <code>ivec3[]</code>.
		 *
		 * @param location The location of the uniform that will be set.
		 * @param count The size of the array.
		 * @param values A pointer to the <code>Vector3i</code> array that will be the <code>ivec3[]</code> uniform.
		 */
		void setUniform3iv(int location, unsigned int count, const Vector3i *values) const;

		/**
		 * Sets the uniform at the given location to the given <code>uvec3</code>.
		 *
		 * @param location The location of the uniform that will be set.
		 * @param x The x coordinate of the <code>uvec3</code> uniform.
		 * @param y The y coordinate of the <code>uvec3</code> uniform.
		 * @param y The z coordinate of the <code>uvec3</code> uniform.
		 */
		void setUniform3ui(int location, unsigned int x, unsigned int y, unsigned int z) const;

		/**
		 * Sets the uniform at the given location to the given <code>uvec3</code>.
		 *
		 * @param location The location of the uniform that will be set.
		 * @param value The value of the <code>uvec3</code> uniform.
		 */
		void setUniform3ui(int location, const Vector3ui &value) const;

		/**
		 * Sets the uniform at the given location to the given <code>uvec3[]</code>.
		 *
		 * @param location The location of the uniform that will be set.
		 * @param count The size of the array.
		 * @param values A pointer to the unsigned int array that will be the <code>uvec3[]</code> uniform.
		 */
		void setUniform3uiv(int location, unsigned int count, const unsigned int *values) const;

		/**
		 * Sets the uniform at the given location to the given <code>uvec3[]</code>.
		 *
		 * @param location The location of the uniform that will be set.
		 * @param count The size of the array.
		 * @param values A pointer to the <code>Vector3ui</code> array that will be the <code>uvec3[]</code> uniform.
		 */
		void setUniform3uiv(int location, unsigned int count, const Vector3ui *values) const;

		/**
		 * Sets the uniform at the given location to the given <code>vec3</code>.
		 *
		 * @param location The location of the uniform that will be set.
		 * @param x The x coordinate of the <code>vec3</code> uniform.
		 * @param y The y coordinate of the <code>vec3</code> uniform.
		 * @param y The z coordinate of the <code>vec3</code> uniform.
		 */
		void setUniform3f(int location, float x, float y, float z) const;

		/**
		 * Sets the uniform at the given location to the given <code>vec3</code>.
		 *
		 * @param location The location of the uniform that will be set.
		 * @param value The value of the <code>vec3</code> uniform.
		 */
		void setUniform3f(int location, const Vector3f &value) const;

		/**
		 * Sets the uniform at the given location to the given <code>vec3[]</code>.
		 *
		 * @param location The location of the uniform that will be set.
		 * @param count The size of the array.
		 * @param values A pointer to the float array that will be the <code>vec3[]</code> uniform.
		 */
		void setUniform3fv(int location, unsigned int count, const float *values) const;

		/**
		 * Sets the uniform at the given location to the given <code>vec3[]</code>.
		 *
		 * @param location The location of the uniform that will be set.
		 * @param count The size of the array.
		 * @param values A pointer to the <code>Vector3f</code> array that will be the <code>vec3[]</code> uniform.
		 */
		void setUniform3fv(int location, unsigned int count, const Vector3f *values) const;

		/**
		 * Sets the uniform at the given location to the given <code>dvec3</code>.
		 *
		 * @param location The location of the uniform that will be set.
		 * @param x The x coordinate of the <code>dvec3</code> uniform.
		 * @param y The y coordinate of the <code>dvec3</code> uniform.
		 * @param y The z coordinate of the <code>dvec3</code> uniform.
		 */
		void setUniform3d(int location, double x, double y, double z) const;

		/**
		 * Sets the uniform at the given location to the given <code>dvec3</code>.
		 *
		 * @param location The location of the uniform that will be set.
		 * @param value The value of the <code>dvec3</code> uniform.
		 */
		void setUniform3d(int location, const Vector3d &value) const;

		/**
		 * Sets the uniform at the given location to the given <code>dvec3[]</code>.
		 *
		 * @param location The location of the uniform that will be set.
		 * @param count The size of the array.
		 * @param values A pointer to the double array that will be the <code>dvec3[]</code> uniform.
		 */
		void setUniform3dv(int location, unsigned int count, const double *values) const;

		/**
		 * Sets the uniform at the given location to the given <code>dvec3[]</code>.
		 *
		 * @param location The location of the uniform that will be set.
		 * @param count The size of the array.
		 * @param values A pointer to the <code>Vector3d</code> array that will be the <code>dvec3[]</code> uniform.
		 */
		void setUniform3dv(int location, unsigned int count, const Vector3d *values) const;

		/**
		 * Sets the uniform at the given location to the given <code>ivec4</code>.
		 *
		 * @param location The location of the uniform that will be set.
		 * @param x The x coordinate of the <code>ivec4</code> uniform.
		 * @param y The y coordinate of the <code>ivec4</code> uniform.
		 * @param y The z coordinate of the <code>ivec4</code> uniform.
		 * @param y The w coordinate of the <code>ivec4</code> uniform.
		 */
		void setUniform4i(int location, int x, int y, int z, int w) const;

		/**
		 * Sets the uniform at the given location to the given <code>ivec4</code>.
		 *
		 * @param location The location of the uniform that will be set.
		 * @param value The value of the <code>ivec4</code> uniform.
		 */
		void setUniform4i(int location, const Vector4i &value) const;

		/**
		 * Sets the uniform at the given location to the given <code>ivec4[]</code>.
		 *
		 * @param location The location of the uniform that will be set.
		 * @param count The size of the array.
		 * @param values A pointer to the int array that will be the <code>ivec4[]</code> uniform.
		 */
		void setUniform4iv(int location, unsigned int count, const int *values) const;

		/**
		 * Sets the uniform at the given location to the given <code>ivec4[]</code>.
		 *
		 * @param location The location of the uniform that will be set.
		 * @param count The size of the array.
		 * @param values A pointer to the <code>Vector4i</code> array that will be the <code>ivec4[]</code> uniform.
		 */
		void setUniform4iv(int location, unsigned int count, const Vector4i *values) const;

		/**
		 * Sets the uniform at the given location to the given <code>uvec4</code>.
		 *
		 * @param location The location of the uniform that will be set.
		 * @param x The x coordinate of the <code>uvec4</code> uniform.
		 * @param y The y coordinate of the <code>uvec4</code> uniform.
		 * @param y The z coordinate of the <code>uvec4</code> uniform.
		 * @param y The w coordinate of the <code>uvec4</code> uniform.
		 */
		void setUniform4ui(int location, unsigned int x, unsigned int y, unsigned int z, unsigned int w) const;

		/**
		 * Sets the uniform at the given location to the given <code>uvec4</code>.
		 *
		 * @param location The location of the uniform that will be set.
		 * @param value The value of the <code>uvec4</code> uniform.
		 */
		void setUniform4ui(int location, const Vector4ui &value) const;

		/**
		 * Sets the uniform at the given location to the given <code>uvec4[]</code>.
		 *
		 * @param location The location of the uniform that will be set.
		 * @param count The size of the array.
		 * @param values A pointer to the unsigned int array that will be the <code>uvec4[]</code> uniform.
		 */
		void setUniform4uiv(int location, unsigned int count, const unsigned int *values) const;

		/**
		 * Sets the uniform at the given location to the given <code>uvec4[]</code>.
		 *
		 * @param location The location of the uniform that will be set.
		 * @param count The size of the array.
		 * @param values A pointer to the <code>Vector4ui</code> array that will be the <code>uvec4[]</code> uniform.
		 */
		void setUniform4uiv(int location, unsigned int count, const Vector4ui *values) const;

		/**
		 * Sets the uniform at the given location to the given <code>vec4</code>.
		 *
		 * @param location The location of the uniform that will be set.
		 * @param x The x coordinate of the <code>vec4</code> uniform.
		 * @param y The y coordinate of the <code>vec4</code> uniform.
		 * @param y The z coordinate of the <code>vec4</code> uniform.
		 * @param y The w coordinate of the <code>vec4</code> uniform.
		 */
		void setUniform4f(int location, float x, float y, float z, float w) const;

		/**
		 * Sets the uniform at the given location to the given <code>vec4</code>.
		 *
		 * @param location The location of the uniform that will be set.
		 * @param value The value of the <code>vec4</code> uniform.
		 */
		void setUniform4f(int location, const Vector4f &value) const;

		/**
		 * Sets the uniform at the given location to the given <code>vec4[]</code>.
		 *
		 * @param location The location of the uniform that will be set.
		 * @param count The size of the array.
		 * @param values A pointer to the float array that will be the <code>vec4[]</code> uniform.
		 */
		void setUniform4fv(int location, unsigned int count, const float *values) const;

		/**
		 * Sets the uniform at the given location to the given <code>vec4[]</code>.
		 *
		 * @param location The location of the uniform that will be set.
		 * @param count The size of the array.
		 * @param values A pointer to the <code>Vector4f</code> array that will be the <code>vec4[]</code> uniform.
		 */
		void setUniform4fv(int location, unsigned int count, const Vector4f *values) const;

		/**
		 * Sets the uniform at the given location to the given <code>dvec4</code>.
		 *
		 * @param location The location of the uniform that will be set.
		 * @param x The x coordinate of the <code>dvec4</code> uniform.
		 * @param y The y coordinate of the <code>dvec4</code> uniform.
		 * @param y The z coordinate of the <code>dvec4</code> uniform.
		 * @param y The w coordinate of the <code>dvec4</code> uniform.
		 */
		void setUniform4d(int location, double x, double y, double z, double w) const;

		/**
		 * Sets the uniform at the given location to the given <code>dvec4</code>.
		 *
		 * @param location The location of the uniform that will be set.
		 * @param value The value of the <code>dvec4</code> uniform.
		 */
		void setUniform4d(int location, const Vector4d &value) const;

		/**
		 * Sets the uniform at the given location to the given <code>dvec4[]</code>.
		 *
		 * @param location The location of the uniform that will be set.
		 * @param count The size of the array.
		 * @param values A pointer to the double array that will be the <code>dvec4[]</code> uniform.
		 */
		void setUniform4dv(int location, unsigned int count, const double *values) const;

		/**
		 * Sets the uniform at the given location to the given <code>dvec4[]</code>.
		 *
		 * @param location The location of the uniform that will be set.
		 * @param count The size of the array.
		 * @param values A pointer to the <code>Vector4d</code> array that will be the <code>dvec4[]</code> uniform.
		 */
		void setUniform4dv(int location, unsigned int count, const Vector4d *values) const;

		/**
		 * Sets the uniform at the given location to the given <code>mat4</code>.
		 *
		 * @param location The location of the uniform that will be set.
		 * @param values A pointer to the float array that will be the <code>mat4</code> uniform.
		 */
		void setUniform4x4f(int location, const float *values) const;

		/**
		 * Sets the uniform at the given location to the given <code>mat4</code>.
		 *
		 * @param location The location of the uniform that will be set.
		 * @param value The value of the <code>mat4</code> uniform.
		 */
		void setUniform4x4f(int location, const Matrix4f &value) const;

		/**
		 * Sets the uniform at the given location to the given <code>mat4[]</code>.
		 *
		 * @param location The location of the uniform that will be set.
		 * @param count The size of the array.
		 * @param values A pointer to the float array that will be the <code>mat4[]</code> uniform.
		 */
		void setUniform4x4fv(int location, unsigned int count, const float *values) const;

		/**
		 * Sets the uniform at the given location to the given <code>mat4[]</code>.
		 *
		 * @param location The location of the uniform that will be set.
		 * @param count The size of the array.
		 * @param values A pointer to the <code>Matrix4f</code> array that will be the <code>mat4[]</code> uniform.
		 */
		void setUniform4x4fv(int location, unsigned int count, const Matrix4f *values) const;

		/**
		 * Gets the id of the shader program on the graphics card.
		 *
		 * @return the id of the shader program on the graphics card.
		 */
		[[nodiscard]] unsigned int getId() const;

		/**
		 * Gets the uniform location of the uniform with the given name.
		 *
		 * @param name A pointer to the name of the uniform.
		 * @return the location of the uniform or <code>-1</code> if there is no uniform with the given name in this shader program.
		 */
		[[nodiscard]] int getUniformLocation(const char *name) const;

	};

}

#endif //CEDAR_SHADERPROGRAM_H
