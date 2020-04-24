//
// Created by masy on 03.03.20.
//

#include <map>
#include <regex>

#include "cedar/FontRegistry.hpp"
#include "cedar/FreeTypeFont.hpp"
#include "cedar/PTFFont.hpp"

using namespace cedar;

std::map<std::string, std::shared_ptr<Font>> FontRegistry::m_loadedFonts = std::map<std::string, std::shared_ptr<Font>>();

std::shared_ptr<Font> FontRegistry::loadFont(const std::string &name, const std::string &path, const unsigned int size, const unsigned int firstCharacter,
							 const unsigned int lastCharacter, const unsigned int renderingMode)
{
	std::regex ptfPattern("^.*(\\.ptf)$");
	std::smatch matcher;
	std::regex_match(path, matcher, ptfPattern);

	if (!matcher.empty())
	{
		std::shared_ptr<Font> font = std::shared_ptr<Font>(new PTFFont(name, path, size));
		font->generateGlyphs(firstCharacter, lastCharacter);
		m_loadedFonts.insert(std::make_pair(name, font));
		return font;
	}

	std::shared_ptr<Font> font = std::shared_ptr<Font>(new FreeTypeFont(name, path, size, renderingMode));
	font->generateGlyphs(firstCharacter, lastCharacter);
	m_loadedFonts.insert(std::make_pair(name, font));
	return font;
}

std::shared_ptr<Font> FontRegistry::getFont(const std::string &name)
{
	auto it = m_loadedFonts.find(name);
	return it != m_loadedFonts.end() ? it->second : nullptr;
}

void FontRegistry::cleanup()
{
	m_loadedFonts.clear();
}

void FontRegistry::cleanup(const std::string &name)
{
	auto it = m_loadedFonts.find(name);
	if (it != m_loadedFonts.end())
	{
		m_loadedFonts.erase(it);
	}
}