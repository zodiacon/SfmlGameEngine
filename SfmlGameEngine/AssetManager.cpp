#include "pch.h"
#include "AssetManager.h"
#include "SfmlHelpers.h"
#include <algorithm>
#include <cassert>

AssetManager::AssetManager(AssetManager* parent) : m_Parent(parent) {
	char path[MAX_PATH];
	::GetModuleFileNameA(nullptr, path, _countof(path));
	*strrchr(path, L'\\') = 0;
	m_TexturesDir = std::string(path) + "\\Textures\\";
	m_FontsDir = std::string(path) + "\\Fonts\\";
	m_AudioDir = std::string(path) + "\\Audio\\";
}

bool AssetManager::LoadTexture(std::string const& fileName, std::string name) {
	sf::Texture texture;
	if (!texture.loadFromFile(m_TexturesDir + fileName))
		return false;

	if (name.empty()) {
		name = Sfml::GetNameFromFileName(fileName);
	}
	return m_Textures.try_emplace(std::move(name), texture).second;
}

sf::Texture const* AssetManager::GetTexture(std::string const& name) const {
	if (auto it = m_Textures.find(name); it != m_Textures.end())
		return &it->second;
	return m_Parent ? m_Parent->GetTexture(name) : nullptr;
}

sf::Texture const& AssetManager::Texture(std::string const& name) const {
	return *GetTexture(name);
}

bool AssetManager::LoadFont(std::string const& fileName, std::string name) {
	sf::Font font;
	if (!font.openFromFile(m_FontsDir + fileName)) {
		assert(("Failed to load font ", false));
		return false;
	}

	if (name.empty()) {
		name = Sfml::GetNameFromFileName(fileName);
	}

	return m_Fonts.try_emplace(std::move(name), std::move(font)).second;
}

sf::Font const* AssetManager::GetFont(std::string const& name) const {
	if (auto it = m_Fonts.find(name); it != m_Fonts.end())
		return &it->second;
	return m_Parent ? m_Parent->GetFont(name) : nullptr;
}

sf::Font const& AssetManager::Font(std::string const& name) const {
	return *GetFont(name);
}

bool AssetManager::LoadSound(std::string const& fileName, std::string name) {
	sf::SoundBuffer sound;
	if (!sound.loadFromFile(m_AudioDir + fileName))
		return false;

	if (name.empty()) {
		name = Sfml::GetNameFromFileName(fileName);
	}
	return m_Audio.try_emplace(std::move(name), sound).second;
}

sf::SoundBuffer const* AssetManager::GetSound(std::string const& name) const {
	if (auto it = m_Audio.find(name); it != m_Audio.end())
		return &it->second;
	return m_Parent ? m_Parent->GetSound(name) : nullptr;
}

sf::SoundBuffer const& AssetManager::Sound(std::string const& name) const {
	return *GetSound(name);
}

