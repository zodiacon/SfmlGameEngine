#pragma once

#include <windef.h>
#include <string>
#include <SFML/Graphics.hpp>

struct SfmlHelpers abstract final {
	static std::string GetNameFromFileName(std::string const& fileName);
	static float CenterX(sf::Text& text, sf::RenderTarget& target);
	static float CenterY(sf::Text& text, sf::RenderTarget& target);
	static sf::Vector2f Center(sf::Text& text, sf::RenderTarget& target);
	static void SetSpriteSizeCentered(sf::Sprite& sprite, sf::Vector2f const& size);
	static bool SetWindowIcon(sf::Window& win, HICON hIcon, HINSTANCE hInstance = nullptr);
	static bool SetWindowIcon(sf::Window& win, UINT id, HINSTANCE hInstance = nullptr);
	static bool SetWindowIcon(sf::Window& win, PCTSTR id, HINSTANCE hInstance = nullptr);
	static void SetWindowFullSize(sf::RenderWindow& win, sf::Vector2u const& size);
};

