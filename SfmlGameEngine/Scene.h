#pragma once

#include <functional>
#include "GameComponent.h"

class Game;

class Scene {
public:
	explicit Scene(Game& game);

	std::function<void(float dt)> Update;
	std::function<void(sf::RenderWindow&, float)> Draw;
	std::function<bool(sf::Event const&)> HandleEvent;
	std::function<void()> Init;

	Game& GetGame() const;
	void SetBackColor(sf::Color color);
	[[nodiscard]] sf::Color const& GetBackColor() const;
	void SetWindowSize(sf::Vector2u size);
	[[nodiscard]] sf::Vector2u const& WindowSize() const;

protected:
	virtual void OnUpdate(float dt);
	virtual void OnDraw(sf::RenderWindow& win, float dt);
	virtual void OnInit();

private:
	sf::Vector2u m_WindowSize{ 0,0 };
	Game& m_Game;
	std::vector<std::unique_ptr<GameComponent>> m_Components;
	sf::Color m_BackColor{ sf::Color::Transparent };
	friend class Game;
	friend class SceneManager;
};
