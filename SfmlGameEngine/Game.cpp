#include "pch.h"
#include "Game.h"
#include "Scene.h"
#include "SfmlHelpers.h"

bool Game::Init(uint32_t width, uint32_t height, const std::string& title, uint32_t style) {
	sf::VideoMode mode(sf::Vector2u(width, height));
	m_Window.create(mode, sf::String(title), style);
	m_Window.setFramerateLimit(60);
	return true;
}

void Game::Run() {
	while (m_Window.isOpen()) {
		auto scene = ActiveScene();
		auto time = m_Clock.restart();
		while (m_Window.isOpen()) {
			while (auto const event = m_Window.pollEvent()) {
				if (scene == nullptr || scene->HandleEvent == nullptr || !scene->HandleEvent(*event)) {
					if (event->is<sf::Event::Closed>()) {
						m_Window.close();
					}
				}
			}
			if (scene) {
				auto& color = scene->GetBackColor();
				m_Window.clear(color == sf::Color::Transparent ? m_BackColor : color);
				auto dt = time.asSeconds();
				scene->OnUpdate(dt);
				scene->OnDraw(m_Window, dt);
			}
			else {
				m_Window.clear(m_BackColor);
				auto dt = time.asSeconds();
				if(Update)
					Update(dt);
				if(Draw)
					Draw(m_Window, dt);
			}
			m_Window.display();
		}
		if(!m_Paused)
			m_Time += time;
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

void Game::PushScene(std::shared_ptr<Scene> scene, bool replace) {
	if (scene->GetWindowSize().x)
		SfmlHelpers::SetWindowFullSize(m_Window, scene->GetWindowSize());
	m_SceneManager.PushScene(std::move(scene), replace);
}

std::shared_ptr<Scene> Game::ActiveScene() {
	return m_SceneManager.GetCurrentScene();
}

AssetManager& Game::Assets() {
	return m_AssetsManager;
}

AssetManager const& Game::Assets() const {
	return m_AssetsManager;
}

sf::RenderWindow& Game::Window() {
	return m_Window;
}

void Game::Pause() {
	m_Paused = true;
}

void Game::Resume() {
	m_Paused = false;
}

bool Game::IsPaused() const {
	return m_Paused;
}

sf::Time const& Game::GetTime() const {
	return m_Time;
}

sf::Time Game::GetElapsedTime() const {
	return m_Clock.getElapsedTime();
}

std::shared_ptr<Scene> Game::PopScene() {
	auto scene = m_SceneManager.Pop();
	auto current = ActiveScene();
	if(current && current->GetWindowSize().x)
			SfmlHelpers::SetWindowFullSize(m_Window, current->GetWindowSize());
	return scene;
}