//
// Created by masy on 03.03.20.
//

#include <map>
#include <regex>

#include "cedar/FontRegistry.hpp"
#include "cedar/FreeTypeFont.hpp"
#include "cedar/PTFFont.hpp"

using namespace cedar;

std::map<std::string, Font*> LOADED_FONTS = std::map<std::string, Font*>();

Font *FontRegistry::loadFont(const std::string &name, const std::string &path, const unsigned int size, const unsigned int firstCharacter,
							 const unsigned int lastCharacter, const unsigned int renderingMode)
{
	std::regex ptfPattern("^.*(\\.ptf)$");
	std::smatch matcher;
	std::regex_match(path, matcher, ptfPattern);

	if (!matcher.empty())
	{
		Font *font = new PTFFont(name, path, size);
		font->generateGlyphs(firstCharacter, lastCharacter);
		LOADED_FONTS.insert(std::make_pair(name, font));
		return font;
	}

	Font *font = new FreeTypeFont(name, path, size, renderingMode);
	font->generateGlyphs(firstCharacter, lastCharacter);
	LOADED_FONTS.insert(std::make_pair(name, font));
	return font;
}

Font *FontRegistry::getFont(const std::string &name)
{
	auto it = LOADED_FONTS.find(name);
	return it != LOADED_FONTS.end() ? it->second : nullptr;
}

void FontRegistry::cleanup()
{
	for (const auto &pair : LOADED_FONTS)
	{
		delete pair.second;
	}
	LOADED_FONTS.clear();
}

void FontRegistry::cleanup(const std::string &name)
{
	auto it = LOADED_FONTS.find(name);
	if (it != LOADED_FONTS.end())
	{
		delete it->second;
		LOADED_FONTS.erase(it);
	}
}