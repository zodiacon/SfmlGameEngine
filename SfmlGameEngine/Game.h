#pragma once

#include "SceneManager.h"
#include "AssetManager.h"
#include <SFML/Graphics.hpp>

class Game {
public:
	virtual ~Game() = default;
	virtual bool Init(int width, int height, const std::string& title, sf::Uint32 style = sf::Style::Close | sf::Style::Titlebar);
	virtual void Run();

	bool LoadTexture(std::string const& fileName, std::string name = "");
	sf::Texture const& Texture(std::string const& name) const;

	bool LoadFont(std::string const& fileName, std::string name = "");
	sf::Font const& Font(std::string const& name) const;

	void PushScene(std::unique_ptr<Scene> scene, bool replace = false);
	template<typename T>
	void PushScene() {
		PushScene(std::make_unique<T>(*this));
	}

	Scene* ActiveScene();
	AssetManager& Assets();
	sf::RenderWindow& Window();

private:
	SceneManager m_SceneManager;
	AssetManager m_AssetsManager;
	sf::RenderWindow m_Window;
	sf::Clock m_Clock;
};

