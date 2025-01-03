#pragma once

#include <stack>
#include <memory>
#include <functional>

class Game;
class AssetManager;

namespace sf {
	class RenderWindow;
	class Event;
}

class Scene {
public:
	explicit Scene(Game& game);

	std::function<void(float dt)> Update;
	std::function<void(sf::RenderWindow&, float)> Draw;
	std::function<bool(sf::Event const&)> HandleEvent;

	Game& GetGame() const;

protected:
	virtual void OnUpdate(float dt);
	virtual void OnDraw(sf::RenderWindow& win, float dt);

private:
	Game& m_Game;
	friend class Game;
};

class SceneManager {
public:
	void PushScene(std::unique_ptr<Scene> scene, bool replace = false);
	Scene* GetCurrentScene();
	void Pop();

private:
	std::stack<std::unique_ptr<Scene>> m_Scenes;
};

