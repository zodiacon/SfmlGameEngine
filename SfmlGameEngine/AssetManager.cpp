#include "pch.h"
#include "AssetManager.h"
#include "SfmlHelpers.h"
#include <algorithm>
#include <SFML/Audio.hpp>
#include <cassert>

AssetManager::AssetManager() {
	char path[MAX_PATH];
	::GetModuleFileNameA(nullptr, path, _countof(path));
	*strrchr(path, L'\\') = 0;
	m_TexturesDir = std::string(path) + "\\Textures\\";
	m_FontsDir = std::string(path) + "\\Fonts\\";
}

bool AssetManager::LoadTexture(std::string const& fileName, std::string name) {
	sf::Texture texture;
	if (!texture.loadFromFile(m_TexturesDir + fileName))
		return false;

	if (name.empty()) {
		name = SfmlHelpers::GetNameFromFileName(fileName);
	}
	return m_Textures.try_emplace(std::move(name), texture).second;
}

sf::Texture const& AssetManager::Texture(std::string const& name) const {
	return m_Textures.at(name);
}

sf::Texture& AssetManager::Texture(std::string const& name) {
	return m_Textures.at(name);
}

bool AssetManager::LoadFont(std::string const& fileName, std::string name) {
	sf::Font font;
	if (!font.loadFromFile(m_FontsDir + fileName)) {
		assert(("Failed to load font ", false));
		return false;
	}

	if (name.empty()) {
		name = SfmlHelpers::GetNameFromFileName(fileName);
	}

	return m_Fonts.try_emplace(std::move(name), std::move(font)).second;
}

sf::Font const& AssetManager::Font(std::string const& name) const {
	return m_Fonts.at(name);
}

bool AssetManager::LoadSound(std::string const& fileName, std::string name) {
	sf::SoundBuffer sound;
	if (!sound.loadFromFile(m_AudioDir + fileName))
		return false;

	if (name.empty()) {
		name = SfmlHelpers::GetNameFromFileName(fileName);
	}
	return m_Audio.try_emplace(std::move(name), std::move(sound)).second;
}

size_t AssetManager::NoCaseHash::operator()(std::string const& str) const {
	std::string s1(str);
	std::transform(s1.begin(), s1.end(), s1.begin(), ::tolower);
	return std::hash<std::string>()(s1);
}

bool AssetManager::StringNoCaseEqual::operator()(std::string const& lhs, std::string const& rhs) const {
	return _stricmp(lhs.c_str(), rhs.c_str()) == 0;
}
