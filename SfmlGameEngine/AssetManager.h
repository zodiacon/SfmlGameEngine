#pragma once

#include <map>
#include <string>
#include "SfmlHelpers.h"
#include "MoveOnly.h"
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>

class AssetManager : public MoveOnly {
public:
	explicit AssetManager(AssetManager* parent = nullptr);

	bool LoadTexture(std::string const& fileName, std::string name = "");
	sf::Texture const* GetTexture(std::string const& name) const;
	sf::Texture const& Texture(std::string const& name) const;

	bool LoadFont(std::string const& fileName, std::string name = "");
	sf::Font const* GetFont(std::string const& name) const;
	sf::Font const& Font(std::string const& name) const;

	bool LoadSound(std::string const& fileName, std::string name = "");
	sf::SoundBuffer const* GetSound(std::string const& name) const;
	sf::SoundBuffer const& Sound(std::string const& name) const;

private:

	std::map<std::string, sf::Texture, Sfml::StringNoCaseEqual> m_Textures;
	std::map<std::string, sf::Font, Sfml::StringNoCaseEqual> m_Fonts;
	std::map<std::string, sf::SoundBuffer, Sfml::StringNoCaseEqual> m_Audio;
	std::string m_TexturesDir, m_FontsDir, m_AudioDir;
	AssetManager* m_Parent;
};

