//
// Created by masy on 02.03.20.
//

#include "cedar/Model.h"
#include "glad/glad.h"

using namespace cedar;

ModelException::ModelException(const std::string &message) : XException(message)
{}

ModelCreationException::ModelCreationException(const std::string &message) : ModelException(message)
{}

ModelUploadException::ModelUploadException(const std::string &message) : ModelException(message)
{}

ModelUpdateException::ModelUpdateException(const std::string &message) : ModelException(message)
{}

Model::Model(const unsigned int drawingMode, const unsigned int vertexAttribCount)
{
	if (vertexAttribCount == 0)
		throw ModelCreationException("Could not create model. Vertex attribute count must be greater than 0!");

	int maxVertexAttribs = 0;
	glGetIntegerv(GL_MAX_VERTEX_ATTRIBS, &maxVertexAttribs);
	if (vertexAttribCount > static_cast<unsigned int>(maxVertexAttribs))
		throw ModelCreationException("Could not create model. Vertex attribute count exceeds the maximum number of vertex attribute arrays supported by the driver!");

	this->m_vaoId = 0;
	this->m_indexVboId = 0;
	this->m_vertexVboId = 0;
	this->m_drawingMode = drawingMode;
	this->m_indexCount = 0;
	this->m_indexType = CEDAR_UNSIGNED_INT;
	this->m_vertexAttribCount = vertexAttribCount;
}

Model::~Model()
{
	glDeleteBuffers(2, &this->m_indexVboId);
	glDeleteVertexArrays(1, &this->m_vaoId);
}

void Model::upload(const unsigned int vertexDataSize, const void *vertexData, const unsigned int indexDataSize, const void *indexData,
				   const unsigned int indexType)
{
	switch (indexType)
	{
		case CEDAR_UNSIGNED_INT:
			this->m_indexCount = indexDataSize >> 2U; // divide by 4
			break;

		case CEDAR_UNSIGNED_SHORT:
			this->m_indexCount = indexDataSize >> 1U; // divide by 2
			break;

		case CEDAR_UNSIGNED_BYTE:
			this->m_indexCount = indexDataSize;
			break;

		default:
			throw ModelUploadException("Could not bake model. Index type must be an unsigned data type!");
	}
	this->m_indexType = indexType;

	if (this->m_vaoId == 0)
		glGenVertexArrays(1, &this->m_vaoId);

	glBindVertexArray(this->m_vaoId);

	if (this->m_indexVboId != 0)
	{
		glDeleteBuffers(2, &this->m_indexVboId);
	}

	glGenBuffers(2, &this->m_indexVboId);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->m_indexVboId);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indexDataSize, indexData, GL_STATIC_DRAW);

	glBindBuffer(GL_ARRAY_BUFFER, this->m_vertexVboId);
	glBufferData(GL_ARRAY_BUFFER, vertexDataSize, vertexData, GL_STATIC_DRAW);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);

}

void Model::update(const unsigned int offset, const unsigned int vertexDataSize, const void *vertexData) {
	if (this->m_vaoId == 0)
		throw ModelUpdateException("Could not update model. The model is not initialized yet!");

	if (this->m_vertexVboId == 0)
		throw ModelUpdateException("Could not update model. The model is not initialized yet!");

	glBindBuffer(GL_ARRAY_BUFFER, this->m_vertexVboId);
	glBufferSubData(GL_ARRAY_BUFFER, offset, vertexDataSize, vertexData);
}

void Model::render() const
{
	if (this->m_indexCount)
	{
		glBindVertexArray(this->m_vaoId);
		for (unsigned int n = 0; n < this->m_vertexAttribCount; n++)
		{
			glEnableVertexAttribArray(n);
		}
		glDrawElements(this->m_drawingMode, this->m_indexCount, this->m_indexType, nullptr);
		for (unsigned int n = 0; n < this->m_vertexAttribCount; n++)
		{
			glDisableVertexAttribArray(n);
		}
	}
}

unsigned int Model::getVertexArrayId() const
{
	return this->m_vaoId;
}

unsigned int Model::getVertexBufferId() const
{
	return this->m_vertexVboId;
}

unsigned int Model::getIndexBufferId() const
{
	return this->m_indexVboId;
}

unsigned int Model::getVertexAttribCount() const {
	return this->m_vertexAttribCount;
}

void Model::setVertexAttribCount(unsigned int newVertexAttribCount) {
	if (newVertexAttribCount == 0)
		throw ModelUpdateException("Could not set vertex attribute count. The count must be greater than 0!");

	this->m_vertexAttribCount = newVertexAttribCount;
}

bool Model::operator==(const Model &rhs) {
	return this->m_vaoId == rhs.m_vaoId;
}
