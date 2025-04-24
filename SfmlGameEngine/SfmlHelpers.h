#pragma once

#include <windef.h>
#include <string>
#include <SFML/Graphics.hpp>

namespace Sfml {
	std::string GetNameFromFileName(std::string const& fileName);
	float CenterX(sf::Text& text, sf::RenderTarget& target);
	float CenterY(sf::Text& text, sf::RenderTarget& target);
	sf::Vector2f Center(sf::Text& text, sf::RenderTarget& target);
	void SetSpriteSizeCentered(sf::Sprite& sprite, sf::Vector2f const& size);
	bool SetWindowIcon(sf::Window& win, HICON hIcon, HINSTANCE hInstance = nullptr);
	bool SetWindowIcon(sf::Window& win, UINT id, HINSTANCE hInstance = nullptr);
	bool SetWindowIcon(sf::Window& win, PCTSTR id, HINSTANCE hInstance = nullptr);
	void SetWindowFullSize(sf::RenderWindow& win, sf::Vector2u const& size);
};

