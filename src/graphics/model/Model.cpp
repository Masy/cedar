//
// Created by masy on 02.03.20.
//

#include "cedar/Model.h"
#include "glad/glad.h"

using namespace cedar;

ModelException::ModelException(const std::string &message) : XException(message)
{}

ModelUploadException::ModelUploadException(const std::string &message) : ModelException(message)
{}

Model::Model(const unsigned int drawingMode)
{
	this->m_vaoId = 0;
	this->m_indexVboId = 0;
	this->m_vertexVboId = 0;
	this->m_drawingMode = drawingMode;
	this->m_indexCount = 0;
	this->m_indexType = CEDAR_UNSIGNED_INT;
}

Model::~Model()
{
	glDeleteBuffers(2, &this->m_indexVboId);
	glDeleteVertexArrays(1, &this->m_vaoId);
}

void Model::upload(const unsigned int vertexDataSize, const void *vertexData, const unsigned int indexDataSize, const void *indexData, const unsigned int indexType)
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
	glVertexAttribPointer(0, 3, GL_FLOAT, false, sizeof(float) * 6, nullptr); // vertex position
	glVertexAttribPointer(1, 3, GL_FLOAT, false, sizeof(float) * 6, (const void*) 12); // vertex normal

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);

}

void Model::render() const
{
	if (this->m_indexCount)
	{
		glBindVertexArray(this->m_vaoId);
		glEnableVertexAttribArray(0);
		glEnableVertexAttribArray(1);
		glDrawElements(this->m_drawingMode, this->m_indexCount, this->m_indexType, nullptr);
		glDisableVertexAttribArray(0);
		glDisableVertexAttribArray(1);
	}
}
