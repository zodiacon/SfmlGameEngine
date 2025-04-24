#include "pch.h"
#include "SceneManager.h"
#include "Game.h"
#include "GameComponent.h"
#include "Scene.h"

void SceneManager::PushScene(std::shared_ptr<Scene> scene, bool replace) {
	//if (!m_Scenes.empty())
	//	m_Scenes.top()->OnTerm();

	if (m_Scenes.empty())
		m_Scenes.push(std::move(scene));
	else {
		if (replace)
			m_Scenes.pop();
		m_Scenes.push(std::move(scene));
	}

	if (!m_Scenes.empty())
		m_Scenes.top()->OnInit();
}

std::shared_ptr<Scene> SceneManager::GetCurrentScene() {
	return m_Scenes.empty() ? nullptr : m_Scenes.top();
}

std::shared_ptr<Scene> SceneManager::Pop() {
	auto top = m_Scenes.top();
	m_Scenes.pop();
	if (!m_Scenes.empty())
		m_Scenes.top()->OnInit();
	return top;
}

