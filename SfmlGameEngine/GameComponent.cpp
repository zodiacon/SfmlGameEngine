#include "pch.h"
#include "GameComponent.h"

bool GameComponent::IsEnabled() const {
	return m_Enabled;
}

bool GameComponent::IsVisible() const {
	return m_Visible;
}

void GameComponent::Enable(bool enable) {
	m_Enabled = enable;
}

void GameComponent::Show(bool visible) {
	m_Visible = visible;
}
