//
// Created by masy on 02.03.20.
//

#include <fstream>

#include "cedar/ModelRegistry.h"
#include "cedar/Cedar.h"

using namespace cedar;

/**
 * The map of all loaded models.
 */
std::map<std::string, Model *> LOADED_MODELS = std::map<std::string, Model *>();

ModelLoadException::ModelLoadException(const std::string &message) : ModelException(message)
{}

bool ModelRegistry::registerModel(const std::string &name, Model *model)
{
	auto it = LOADED_MODELS.find(name);
	if (it != LOADED_MODELS.end())
	{
		return false;
	}

	LOADED_MODELS.insert(std::make_pair(name, model));
	return true;
}

Model *ModelRegistry::loadBMFModel(const std::string &name, const std::string &path, unsigned char *bitMask)
{
	auto it = LOADED_MODELS.find(name);
	if (it != LOADED_MODELS.end())
	{
		std::string message = "Could not load model ";
		message.append(name);
		message.append(". A model with that name already exists!");
		throw ModelLoadException(message);
	}

	std::ifstream modelFile;
	modelFile.open(path, std::ifstream::binary | std::ifstream::ate);
	if (!modelFile.is_open())
	{
		std::string message = "Could not load model ";
		message.append(name);
		message.append(". Could not open file \"");
		message.append(path);
		message.append("\"!");
		throw ModelLoadException(message);
	}

	unsigned int fileSize = modelFile.tellg();
	modelFile.seekg(0, std::ios_base::beg);

	unsigned char mode = 0;
	unsigned int vertexAttribCount = 1;
	unsigned int vertexCount = 0;
	unsigned int indexCount = 0;

	modelFile.read(reinterpret_cast<char *>(&mode), 1);
	modelFile.read(reinterpret_cast<char *>(bitMask), 1);
	modelFile.read(reinterpret_cast<char *>(&vertexCount), 4);
	modelFile.read(reinterpret_cast<char *>(&indexCount), 4);

	unsigned int vertexSize = 12;

	if (*bitMask & 0x01u) // uvs
	{
		vertexSize += 8;
		vertexAttribCount++;
	}

	if ((*bitMask >> 0x01u) & 0x01u) // normals
	{
		vertexSize += 12;
		vertexAttribCount++;
	}

	if ((*bitMask >> 0x02u) & 0x01u) // color
	{
		vertexSize += 12;
		vertexAttribCount++;
	}

	if ((*bitMask >> 0x03u) & 0x01u) // alpha
	{
		vertexSize += 12;
		vertexAttribCount++;
	}

	if ((*bitMask >> 0x04u) & 0x01u) // stencil
	{
		vertexSize += 1;
		vertexAttribCount++;
	}

	if ((*bitMask >> 0x05u) & 0x01u) // displacement
	{
		vertexSize += 4;
		vertexAttribCount++;
	}

	unsigned int vertexDataSize = vertexCount * vertexSize;
	unsigned int indexDataSize = indexCount * 4;

	Cedar::getCoreLogger()->info("Loaded model with %d vertices and %d indices. Mode: %x; Bitmask: %x", vertexCount, indexCount, mode, *bitMask);

	unsigned int expectedFileSize = vertexDataSize + indexDataSize + 10;
	if (fileSize < expectedFileSize)
	{
		modelFile.close();

		std::string message = "Could not load model ";
		message.append(name);
		message.append(". The model file \"");
		message.append(path);
		message.append("\" is either corrupted or is not a model file! ");
		message.append("Read vertex count: ");
		message.append(std::to_string(vertexCount));
		message.append(". Read index count: ");
		message.append(std::to_string(indexCount));
		message.append(". VertexSize: ");
		message.append(std::to_string(vertexSize));
		message.append(". Mode: ");
		message.append(std::to_string(mode));
		message.append(". BitMask: ");
		message.append(std::to_string(*bitMask));
		message.append(".");
		throw ModelLoadException(message);
	}


	char *vertexData = new char[vertexDataSize];
	char *indexData = new char[indexDataSize];

	modelFile.read(vertexData, vertexDataSize);
	modelFile.read(indexData, indexDataSize);
	modelFile.close();

	unsigned int drawingMode = 0;
	switch (mode)
	{
		case 0x00:
			drawingMode = CEDAR_LINES;
			break;

		case 0x01:
			drawingMode = CEDAR_LINE_STRIP;
			break;

		case 0x02:
			drawingMode = CEDAR_TRIANGLES;
			break;

		case 0x03:
			drawingMode = CEDAR_TRIANGLE_STRIP;
			break;

		default:
			drawingMode = CEDAR_POINTS;
			break;
	}

	Model *model = new Model(drawingMode, vertexAttribCount);
	model->upload(vertexDataSize, vertexData, indexDataSize, indexData);
	delete[] vertexData;
	delete[] indexData;

	LOADED_MODELS.insert(std::make_pair(name, model));
	return model;
}

Model *ModelRegistry::getModel(const std::string &name)
{
	auto it = LOADED_MODELS.find(name);
	return it != LOADED_MODELS.end() ? it->second : nullptr;
}

void ModelRegistry::cleanup()
{
	for (const auto &pair : LOADED_MODELS)
	{
		delete pair.second;
	}
	LOADED_MODELS.clear();
}

void ModelRegistry::cleanup(const std::string &name)
{
	auto it = LOADED_MODELS.find(name);
	if (it != LOADED_MODELS.end())
	{
		delete it->second;
		LOADED_MODELS.erase(it);
	}
}
