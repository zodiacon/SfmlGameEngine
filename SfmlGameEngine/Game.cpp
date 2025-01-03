#include "pch.h"
#include "Game.h"

bool Game::Init(int width, int height, const std::string& title, sf::Uint32 style) {
	m_Window.create(sf::VideoMode(width, height), title, style);
	m_Window.setFramerateLimit(60);
	return true;
}

void Game::Run() {
	auto scene = ActiveScene();
	while (m_Window.isOpen()) {
		auto time = m_Clock.restart();
		sf::Event event;
		while (m_Window.pollEvent(event)) {
			if (scene == nullptr || scene->HandleEvent == nullptr || !scene->HandleEvent(event)) {
				if (event.type == sf::Event::Closed) {
					m_Window.close();
				}
			}
		}
		if (scene) {
			auto dt = time.asSeconds();
			scene->OnUpdate(dt);
			scene->OnDraw(m_Window, dt);
			m_Window.display();
		}
	}
}

bool Game::LoadTexture(std::string const& fileName, std::string name) {
	return m_AssetsManager.LoadTexture(fileName, std::move(name));
}

sf::Texture const& Game::Texture(std::string const& name) const {
	return m_AssetsManager.Texture(name);
}
bool Game::LoadFont(std::string const& fileName, std::string name) {
	return m_AssetsManager.LoadFont(fileName, std::move(name));
}

sf::Font const& Game::Font(std::string const& name) const {
	return m_AssetsManager.Font(name);
}

void Game::PushScene(std::unique_ptr<Scene> scene, bool replace) {
	m_SceneManager.PushScene(std::move(scene), replace);
}

Scene* Game::ActiveScene() {
	return m_SceneManager.GetCurrentScene();
}

AssetManager& Game::Assets() {
	return m_AssetsManager;
}

sf::RenderWindow& Game::Window() {
	return m_Window;
}