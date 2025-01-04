#pragma once

#include <stack>
#include <memory>

class Game;
class AssetManager;
class Scene;

namespace sf {
	class RenderWindow;
	class Event;
}

class SceneManager {
public:
	void PushScene(std::shared_ptr<Scene> scene, bool replace = false);
	std::shared_ptr<Scene> GetCurrentScene();
	std::shared_ptr<Scene> Pop();

private:
	std::stack<std::shared_ptr<Scene>> m_Scenes;
};

