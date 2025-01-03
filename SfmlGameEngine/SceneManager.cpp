#include "pch.h"
#include "SceneManager.h"
#include "Game.h"

void SceneManager::PushScene(std::unique_ptr<Scene> scene, bool replace) {
	if(m_Scenes.empty())
		m_Scenes.push(std::move(scene));
	else {
		if (replace)
			m_Scenes.pop();
		m_Scenes.push(std::move(scene));
	}
}

Scene* SceneManager::GetCurrentScene() {
	return m_Scenes.empty() ? nullptr : m_Scenes.top().get();
}

void SceneManager::Pop() {
	m_Scenes.pop();
}

Scene::Scene(Game& game) : m_Game(game) {
}

void Scene::OnUpdate(float dt) {
	if (Update)
		Update(dt);
}

void Scene::OnDraw(sf::RenderWindow& win, float dt) {
	if (Draw)
		Draw(win, dt);
}
