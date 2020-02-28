//
// Created by masy on 08.02.20.
//

#include "cedar/ShaderProgram.h"
#include "glad/glad.h"
#include <cstring>

using namespace cedar;

//---------------------------------------------------------------------------//
//                                 Exceptions                                //
//---------------------------------------------------------------------------//

ShaderProgramException::ShaderProgramException(const std::string &message) : XException(message)
{}

ShaderProgramCreationException::ShaderProgramCreationException(const std::string &message) : ShaderProgramException(message)
{}

ShaderCreationException::ShaderCreationException(const std::string &message) : ShaderProgramException(message)
{}

ShaderCompileException::ShaderCompileException(const std::string &message) : ShaderProgramException(message)
{}

ShaderProgramLinkException::ShaderProgramLinkException(const std::string &message) : ShaderProgramException(message)
{}

UniformCreationException::UniformCreationException(const std::string &message) : ShaderProgramException(message)
{}

//---------------------------------------------------------------------------//
//                                Shader class                               //
//---------------------------------------------------------------------------//

ShaderProgram::ShaderProgram()
{
	this->m_shaderProgramId = glCreateProgram();

	if (this->m_shaderProgramId == 0)
		throw ShaderProgramCreationException("Could not create shader program!");

	this->m_vertexShaderId = 0;
	this->m_geometryShaderId = 0;
	this->m_fragmentShaderId = 0;
	this->m_computeShaderId = 0;
	this->m_linked = false;
}

ShaderProgram::~ShaderProgram()
{
	if (this->m_shaderProgramId)
	{
		if (this->m_vertexShaderId)
			glDeleteShader(this->m_vertexShaderId);

		if (this->m_geometryShaderId)
			glDeleteShader(this->m_geometryShaderId);

		if (this->m_fragmentShaderId)
			glDeleteShader(this->m_fragmentShaderId);

		if (this->m_computeShaderId)
			glDeleteShader(this->m_computeShaderId);
	}

	this->m_uniforms.clear();
}

unsigned int ShaderProgram::createShader(const std::string &source, const unsigned int type)
{
	unsigned int shaderId = glCreateShader(type);

	if (shaderId == 0)
		throw ShaderCreationException("Could not create shader!");

	const char *sourceCode = source.c_str();
	glShaderSource(shaderId, 1, &sourceCode, nullptr);
	glCompileShader(shaderId);

	int status;
	glGetShaderiv(shaderId, GL_COMPILE_STATUS, &status);
	if (status == 0)
	{
		std::string message = "Could not compile shader. Type: ";
		switch (type)
		{
			case GL_VERTEX_SHADER:
				message.append("VERTEX_SHADER");
				break;

			case GL_GEOMETRY_SHADER:
				message.append("GEOMETRY_SHADER");
				break;

			case GL_FRAGMENT_SHADER:
				message.append("FRAGMENT_SHADER");
				break;

			case GL_COMPUTE_SHADER:
				message.append("COMPUTE_SHADER");
				break;

			default:
				message.append("UNKNOWN_SHADER");
				break;
		}

		char infoLog[1024];
		int length;
		glGetShaderInfoLog(shaderId, 1024, &length, infoLog);
		message.append("\n");
		message.append(infoLog);
		throw ShaderCompileException(message);
	}

	glAttachShader(this->m_shaderProgramId, shaderId);
	return shaderId;
}

void ShaderProgram::createVertexShader(const std::string &source)
{
	if (this->m_linked)
		throw ShaderCreationException("Could not create Vertex shader. The shader program is already linked.");

	this->m_vertexShaderId = this->createShader(source, GL_VERTEX_SHADER);
}

void ShaderProgram::createGeometryShader(const std::string &source)
{
	if (this->m_linked)
		throw ShaderCreationException("Could not create Geometry shader. The shader program is already linked.");

	this->m_geometryShaderId = this->createShader(source, GL_GEOMETRY_SHADER);
}

void ShaderProgram::createFragmentShader(const std::string &source)
{
	if (this->m_linked)
		throw ShaderCreationException("Could not create Fragment shader. The shader program is already linked.");

	this->m_fragmentShaderId = this->createShader(source, GL_FRAGMENT_SHADER);
}

void ShaderProgram::createComputeShader(const std::string &source)
{
	if (this->m_linked)
		throw ShaderCreationException("Could not create Compute shader. The shader program is already linked.");

	this->m_computeShaderId = this->createShader(source, GL_COMPUTE_SHADER);
}

void ShaderProgram::link()
{
	if (this->m_linked)
		throw ShaderProgramLinkException("Could not link shader program. The shader program is already linked.");

	glLinkProgram(this->m_shaderProgramId);

	int status;
	glGetProgramiv(this->m_shaderProgramId, GL_LINK_STATUS, &status);
	if (status == 0)
		throw ShaderProgramLinkException("Could not link shader!");

	this->m_linked = true;
}

void ShaderProgram::createUniforms(unsigned int count, const char **uniforms, int *uniformLocations)
{
	for (unsigned int n = 0; n < count; n++)
	{
		uniformLocations[n] = glGetUniformLocation(this->m_shaderProgramId, uniforms[n]);

		if (uniformLocations[n] == -1)
		{
			std::string message = "Could not create uniform ";
			message.append(uniforms[n]);
			message.append("!");
			throw UniformCreationException(message);
		}

		this->m_uniforms.insert(std::make_pair(uniforms[n], uniformLocations[n]));
	}
}

void ShaderProgram::bind() const
{
	glUseProgram(this->m_shaderProgramId);
}

void ShaderProgram::unbind() const
{
	glUseProgram(0);
}


//---------------------------------------------------------------------------//
//                               Uniform setter                              //
//---------------------------------------------------------------------------//

// single value uniforms

void ShaderProgram::setUniform1i(const int location, const int value) const
{
	glUniform1i(location, value);
}

void ShaderProgram::setUniform1iv(const int location, const unsigned int count, const int *values) const
{
	glUniform1iv(location, count, values);
}

void ShaderProgram::setUniform1ui(const int location, const unsigned int value)
{
	glUniform1ui(location, value);
}

void ShaderProgram::setUniform1uiv(const int location, const unsigned int count, const unsigned int *values) const
{
	glUniform1uiv(location, count, values);
}

void ShaderProgram::setUniform1f(const int location, const float value) const
{
	glUniform1f(location, value);
}

void ShaderProgram::setUniform1fv(const int location, const unsigned int count, const float *values) const
{
	glUniform1fv(location, count, values);
}

void ShaderProgram::setUniform1d(const int location, const double value) const
{
	glUniform1d(location, value);
}

void ShaderProgram::setUniform1dv(const int location, const unsigned int count, const double *values) const
{
	glUniform1dv(location, count, values);
}

// 2 dimensional vector uniforms

void ShaderProgram::setUniform2i(const int location, const int x, const int y) const
{
	glUniform2i(location, x, y);
}

void ShaderProgram::setUniform2i(const int location, const Vector2i &value) const
{
	glUniform2i(location, value.x, value.y);
}

void ShaderProgram::setUniform2iv(const int location, const unsigned int count, const int *values) const
{
	glUniform2iv(location, count, values);
}

void ShaderProgram::setUniform2iv(const int location, const unsigned int count, const Vector2i *values) const
{
	glUniform2iv(location, count, reinterpret_cast<const int *>(values));
}

void ShaderProgram::setUniform2ui(const int location, const unsigned int x, const unsigned int y) const
{
	glUniform2ui(location, x, y);
}

void ShaderProgram::setUniform2ui(const int location, const Vector2ui &value) const
{
	glUniform2ui(location, value.x, value.y);
}

void ShaderProgram::setUniform2uiv(const int location, const unsigned int count, const unsigned int *values) const
{
	glUniform2uiv(location, count, values);
}

void ShaderProgram::setUniform2uiv(const int location, const unsigned int count, const Vector2ui *values) const
{
	glUniform2uiv(location, count, reinterpret_cast<const unsigned int *>(values));
}

void ShaderProgram::setUniform2f(const int location, const float x, const float y) const
{
	glUniform2f(location, x, y);
}

void ShaderProgram::setUniform2f(const int location, const Vector2f &value) const
{
	glUniform2f(location, value.x, value.y);
}

void ShaderProgram::setUniform2fv(const int location, const unsigned int count, const float *values) const
{
	glUniform2fv(location, count, values);
}

void ShaderProgram::setUniform2fv(const int location, const unsigned int count, const Vector2f *values) const
{
	glUniform2fv(location, count, reinterpret_cast<const float *>(values));
}

void ShaderProgram::setUniform2d(const int location, const double x, const double y) const
{
	glUniform2d(location, x, y);
}

void ShaderProgram::setUniform2d(const int location, const Vector2d &value) const
{
	glUniform2d(location, value.x, value.y);
}

void ShaderProgram::setUniform2dv(const int location, const unsigned int count, const double *values) const
{
	glUniform2dv(location, count, values);
}

void ShaderProgram::setUniform2dv(const int location, const unsigned int count, const Vector2d *values) const
{
	glUniform2dv(location, count, reinterpret_cast<const double *>(values));
}

// 3 dimensional vector uniforms

void ShaderProgram::setUniform3i(const int location, const int x, const int y, const int z) const
{
	glUniform3i(location, x, y, z);
}

void ShaderProgram::setUniform3i(const int location, const Vector3i &value) const
{
	glUniform3i(location, value.x, value.y, value.z);
}

void ShaderProgram::setUniform3iv(const int location, const unsigned int count, const int *values) const
{
	glUniform3iv(location, count, values);
}

void ShaderProgram::setUniform3iv(const int location, const unsigned int count, const Vector3i *values) const
{
	glUniform3iv(location, count, reinterpret_cast<const int *>(values));
}

void ShaderProgram::setUniform3ui(const int location, const unsigned int x, const unsigned int y, const unsigned int z) const
{
	glUniform3ui(location, x, y, z);
}

void ShaderProgram::setUniform3ui(const int location, const Vector3ui &value) const
{
	glUniform3ui(location, value.x, value.y, value.z);
}

void ShaderProgram::setUniform3uiv(const int location, const unsigned int count, const unsigned int *values) const
{
	glUniform3uiv(location, count, values);
}

void ShaderProgram::setUniform3uiv(const int location, const unsigned int count, const Vector3ui *values) const
{
	glUniform3uiv(location, count, reinterpret_cast<const unsigned int *>(values));
}

void ShaderProgram::setUniform3f(const int location, const float x, const float y, const float z) const
{
	glUniform3f(location, x, y, z);
}

void ShaderProgram::setUniform3f(const int location, const Vector3f &value) const
{
	glUniform3f(location, value.x, value.y, value.z);
}

void ShaderProgram::setUniform3fv(const int location, const unsigned int count, const float *values) const
{
	glUniform3fv(location, count, values);
}

void ShaderProgram::setUniform3fv(const int location, const unsigned int count, const Vector3f *values) const
{
	glUniform3fv(location, count, reinterpret_cast<const float *>(values));
}

void ShaderProgram::setUniform3d(const int location, const double x, const double y, const double z) const
{
	glUniform3d(location, x, y, z);
}

void ShaderProgram::setUniform3d(const int location, const Vector3d &value) const
{
	glUniform3d(location, value.x, value.y, value.z);
}

void ShaderProgram::setUniform3dv(const int location, const unsigned int count, const double *values) const
{
	glUniform3dv(location, count, values);
}

void ShaderProgram::setUniform3dv(const int location, const unsigned int count, const Vector3d *values) const
{
	glUniform3dv(location, count, reinterpret_cast<const double *>(values));
}

// 4 dimensional vector uniforms

void ShaderProgram::setUniform4i(const int location, const int x, const int y, const int z, const int w) const
{
	glUniform4i(location, x, y, z, w);
}

void ShaderProgram::setUniform4i(const int location, const Vector4i &value) const
{
	glUniform4i(location, value.x, value.y, value.z, value.w);
}

void ShaderProgram::setUniform4iv(const int location, const unsigned int count, const int *values) const
{
	glUniform4iv(location, count, values);
}

void ShaderProgram::setUniform4iv(const int location, const unsigned int count, const Vector4i *values) const
{
	glUniform4iv(location, count, reinterpret_cast<const int *>(values));
}

void ShaderProgram::setUniform4ui(const int location, const unsigned int x, const unsigned int y, const unsigned int z, const unsigned int w) const
{
	glUniform4ui(location, x, y, z, w);
}

void ShaderProgram::setUniform4ui(const int location, const Vector4ui &value) const
{
	glUniform4ui(location, value.x, value.y, value.z, value.w);
}

void ShaderProgram::setUniform4uiv(const int location, const unsigned int count, const unsigned int *values) const
{
	glUniform4uiv(location, count, values);
}

void ShaderProgram::setUniform4uiv(const int location, const unsigned int count, const Vector4ui *values) const
{
	glUniform4uiv(location, count, reinterpret_cast<const unsigned int *>(values));
}

void ShaderProgram::setUniform4f(const int location, const float x, const float y, const float z, const float w) const
{
	glUniform4f(location, x, y, z, w);
}

void ShaderProgram::setUniform4f(int location, const Vector4f &value) const
{
	glUniform4f(location, value.x, value.y, value.z, value.w);
}

void ShaderProgram::setUniform4fv(const int location, const unsigned int count, const float *values) const
{
	glUniform4fv(location, count, values);
}

void ShaderProgram::setUniform4fv(const int location, const unsigned int count, const Vector4f *values) const
{
	glUniform4fv(location, count, reinterpret_cast<const float *>(values));
}

void ShaderProgram::setUniform4d(const int location, const double x, const double y, const double z, const double w) const
{
	glUniform4d(location, x, y, z, w);
}

void ShaderProgram::setUniform4d(const int location, const Vector4d &value) const
{
	glUniform4d(location, value.x, value.y, value.z, value.w);
}

void ShaderProgram::setUniform4dv(const int location, const unsigned int count, const double *values) const
{
	glUniform4dv(location, count, values);
}

void ShaderProgram::setUniform4dv(const int location, const unsigned int count, const Vector4d *values) const
{
	glUniform4dv(location, count, reinterpret_cast<const double *>(values));
}

// 4x4 dimensional matrix uniforms

void ShaderProgram::setUniform4x4f(int location, const float *values) const
{
	glUniformMatrix4fv(location, 1, false, values);
}

void ShaderProgram::setUniform4x4f(const int location, const Matrix4f &value) const
{
	glUniformMatrix4fv(location, 1, false, reinterpret_cast<const float *>(&value));
}

void ShaderProgram::setUniform4x4fv(int location, unsigned int count, const float *values) const
{
	glUniformMatrix4fv(location, count, false, values);
}

void ShaderProgram::setUniform4x4fv(int location, unsigned int count, const Matrix4f *values) const
{
	glUniformMatrix4fv(location, count, false, reinterpret_cast<const float *>(values));
}

//---------------------------------------------------------------------------//
//                                   Getter                                  //
//---------------------------------------------------------------------------//

unsigned int ShaderProgram::getId() const
{
	return this->m_shaderProgramId;
}

int ShaderProgram::getUniformLocation(const char *name) const
{
	for (auto &uniform : this->m_uniforms)
	{
		if (std::strcmp(uniform.first, name) == 0)
			return uniform.second;
	}

	return -1;
}
