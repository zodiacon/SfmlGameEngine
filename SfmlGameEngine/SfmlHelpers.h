#pragma once

#include <windef.h>
#include <string>
#include <SFML\Graphics.hpp>

namespace Sfml {
	[[nodiscard]] std::string GetNameFromFileName(std::string const& fileName);
	[[nodiscard]] float CenterX(sf::Text const& text, sf::RenderTarget& target);
	[[nodiscard]] float CenterY(sf::Text const& text, sf::RenderTarget& target);
	[[nodiscard]] sf::Vector2f Center(sf::Text const& text, sf::RenderTarget& target);
	void SetSpriteSizeCentered(sf::Sprite& sprite, sf::Vector2f const& size);
	bool SetWindowIcon(sf::Window const& win, HICON hIcon);
	bool SetWindowIcon(sf::Window const& win, UINT id, HINSTANCE hInstance = nullptr);
	bool SetWindowIcon(sf::Window const& win, PCTSTR id, HINSTANCE hInstance = nullptr);
	void SetWindowFullSize(sf::RenderWindow& win, sf::Vector2u const& size);

	struct StringNoCaseEqual {
		bool operator()(std::string const& lhs, std::string const& rhs) const;
	};
};

