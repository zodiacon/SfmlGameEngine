#pragma once

#include <SFML/Graphics.hpp>

class GameComponent abstract {
public:
	virtual ~GameComponent() = default;

	bool IsEnabled() const;
	bool IsVisible() const;

	virtual void Enable(bool enable);
	virtual void Show(bool visible);

	virtual void Update(float dt) = 0;
	virtual void Draw(sf::Window& win, float dt) {}

protected:
	GameComponent() = default;

private:
	bool m_Visible{ true }, m_Enabled{ true };
};

