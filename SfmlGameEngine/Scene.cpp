#include "pch.h"
#include "Scene.h"

Scene::Scene(Game& game) : m_Game(game) {
}

Game& Scene::GetGame() const {
	return m_Game;
}

sf::Color const& Scene::GetBackColor() const {
	return m_BackColor;
}

void Scene::SetBackColor(sf::Color color) {
	m_BackColor = color;
}

void Scene::SetWindowSize(sf::Vector2u size) {
	m_WindowSize = size;
}

void Scene::SetWindowSize(float sx, float sy) {
	SetWindowSize(sf::Vector2u(sx, sy));
}

sf::Vector2u const& Scene::GetWindowSize() const {
	return m_WindowSize;
}

void Scene::OnUpdate(float dt) {
	if (Update)
		Update(dt);

	for (auto& comp : m_Components) {
		if (comp->IsEnabled())
			comp->Update(dt);
	}
}

void Scene::OnDraw(sf::RenderWindow& win, float dt) {
	if (Draw)
		Draw(win, dt);

	for (auto& comp : m_Components) {
		if (comp->IsEnabled() && comp->IsVisible())
			comp->Draw(win, dt);
	}
}
