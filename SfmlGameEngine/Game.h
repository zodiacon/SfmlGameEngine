#pragma once

#include "SceneManager.h"
#include "AssetManager.h"
#include <SFML/Graphics.hpp>
#include "MoveOnly.h"

class Game : public MoveOnly {
public:
	virtual ~Game() = default;
	virtual bool Init(uint32_t width, uint32_t height, const std::string& title, uint32_t style = sf::Style::Close | sf::Style::Titlebar);
	virtual void Run();

	bool LoadTexture(std::string const& fileName, std::string name = "");
	sf::Texture const& Texture(std::string const& name) const;
	bool LoadFont(std::string const& fileName, std::string name = "");
	sf::Font const& Font(std::string const& name) const;

	void PushScene(std::shared_ptr<Scene> scene, bool replace = false);
	template<typename T>
	void PushScene() {
		PushScene(std::make_unique<T>(*this));
	}
	std::shared_ptr<Scene> PopScene();

	void Pause();
	void Resume();
	bool IsPaused() const;
	void Restart();

	sf::Time const& GetTime() const;
	sf::Time GetElapsedTime() const;

	std::shared_ptr<Scene> ActiveScene();
	AssetManager& Assets();
	AssetManager const& Assets() const;
	sf::RenderWindow& Window();

private:
	SceneManager m_SceneManager;
	AssetManager m_AssetsManager;
	sf::RenderWindow m_Window;
	sf::Clock m_Clock;
	sf::Time m_Time;
	sf::Color m_BackColor{ sf::Color::Black };
	bool m_Paused{ false };
};

