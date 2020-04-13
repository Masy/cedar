//
// Created by masy on 13.04.20.
//

#include "cedar/TextureRegistry.hpp"
#include "cedar/ImageLoader.hpp"

using namespace cedar;

TextureRegisterException::TextureRegisterException(const std::string &message) : XException(message)
{}

std::map<std::string, std::shared_ptr<Texture>> TextureRegistry::m_loadedTextures = std::map<std::string, std::shared_ptr<Texture>>();

TextureRegistry::TextureRegistry()
= default;

std::shared_ptr<Texture> TextureRegistry::registerTexture(const std::string &name, Texture *texture)
{
	if (name.empty())
		throw TextureRegisterException("Could not register texture! The name of the texture can't be empty!");

	if (m_loadedTextures.find(name) != m_loadedTextures.end())
		throw TextureRegisterException("Could not register texture! A texture with name " + name + " is already registered!");

	std::shared_ptr<Texture> sharedPtr = std::shared_ptr<Texture>(texture);
	m_loadedTextures.insert(std::make_pair(name, sharedPtr));
	return sharedPtr;
}

std::shared_ptr<Texture> TextureRegistry::loadTexture(const std::string &name, const std::string &path) {
	if (name.empty())
		throw TextureRegisterException("Could not register texture! The name of the texture can't be empty!");

	if (m_loadedTextures.find(name) != m_loadedTextures.end())
		throw TextureRegisterException("Could not load texture! A texture with name " + name + " is already registered!");

	std::shared_ptr<Texture> sharedPtr = std::shared_ptr<Texture>(ImageLoader::loadTexture(path, 0));
	m_loadedTextures.insert(std::make_pair(name, sharedPtr));

	return sharedPtr;
}

std::shared_ptr<Texture> TextureRegistry::getTexture(const std::string &name) {
	auto it = m_loadedTextures.find(name);
	if (it != m_loadedTextures.end())
		return it->second;
	else
		return nullptr;
}

void TextureRegistry::cleanup(const std::string &name) {
	m_loadedTextures.erase(name);
}

void TextureRegistry::cleanup() {
	m_loadedTextures.clear();
}
