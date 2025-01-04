#pragma once

#include <unordered_map>
#include <string>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

namespace sf {
	class Texture;
	class Font;
}

class AssetManager {
public:
	AssetManager();
	AssetManager(AssetManager const&) = delete;
	AssetManager& operator=(AssetManager const&) = delete;
	AssetManager(AssetManager&&) = default;
	AssetManager& operator=(AssetManager&&) = default;

	bool LoadTexture(std::string const& fileName, std::string name = "");
	sf::Texture const& Texture(std::string const& name) const;
	sf::Texture& Texture(std::string const& name);

	bool LoadFont(std::string const& fileName, std::string name = "");
	sf::Font const& Font(std::string const& name) const;

	bool LoadSound(std::string const& fileName, std::string name = "");
	sf::SoundBuffer const& Sound(std::string const& name) const;

private:
	struct NoCaseHash {
		size_t operator()(std::string const& str) const;
	};
	struct StringNoCaseEqual {
		bool operator()(std::string const& lhs, std::string const& rhs) const;
	};

	std::unordered_map<std::string, sf::Texture, NoCaseHash, StringNoCaseEqual> m_Textures;
	std::unordered_map<std::string, sf::Font, NoCaseHash, StringNoCaseEqual> m_Fonts;
	std::unordered_map<std::string, sf::SoundBuffer, NoCaseHash, StringNoCaseEqual> m_Audio;
	std::string m_TexturesDir, m_FontsDir, m_AudioDir;
};

