//
// Created by masy on 02.03.20.
//

#include <fstream>

#include "cedar/ModelRegistry.h"

using namespace cedar;

/**
 * The map of all loaded models.
 */
std::map<std::string, Model *> LOADED_MODELS = std::map<std::string, Model *>();

ModelLoadException::ModelLoadException(const std::string &message) : ModelException(message)
{}

Model *ModelRegistry::loadModel(const std::string &name, const std::string &path, const unsigned int drawingMode)
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

	unsigned int vertexCount = 0;
	unsigned int indexCount = 0;

	modelFile.read(reinterpret_cast<char *>(&vertexCount), 4);
	modelFile.read(reinterpret_cast<char *>(&indexCount), 4);
	unsigned int vertexDataSize = vertexCount * 6 * 4;
	unsigned int indexDataSize = indexCount * 4;

	unsigned int expectedFileSize = vertexDataSize + indexDataSize + 8; // + 8 = the 2 size ints
	if (fileSize < expectedFileSize)
	{
		modelFile.close();

		std::string message = "Could not load model ";
		message.append(name);
		message.append(". The model file \"");
		message.append(path);
		message.append("\" is either corrupted or is not a model file!");
		throw ModelLoadException(message);
	}

	char *vertexData = new char[vertexDataSize];
	char *indexData = new char[indexDataSize];

	modelFile.read(vertexData, vertexDataSize);
	modelFile.read(indexData, indexDataSize);
	modelFile.close();

	Model *model = new Model(drawingMode);
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
