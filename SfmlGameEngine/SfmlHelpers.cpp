#include "pch.h"
#include "SfmlHelpers.h"

std::string SfmlHelpers::GetNameFromFileName(std::string const& fileName) {
	auto bs = fileName.find_last_of("/\\");
	std::string name;
	if (bs == std::string::npos)
		name = fileName.substr(0, fileName.find_last_of('.'));
	else 
		name = fileName.substr(bs + 1);
	return name;
}

float SfmlHelpers::CenterX(sf::Text& text, sf::RenderTarget& target) {
	return (target.getSize().x - text.getLocalBounds().width) / 2;
}

float SfmlHelpers::CenterY(sf::Text& text, sf::RenderTarget& target) {
	return (target.getSize().y - text.getLocalBounds().height) / 2;
}

sf::Vector2f SfmlHelpers::Center(sf::Text& text, sf::RenderTarget& target) {
	return sf::Vector2f(CenterX(text, target), CenterY(text, target));
}

void SfmlHelpers::SetSpriteSizeCentered(sf::Sprite& sprite, sf::Vector2f const& size) {
	auto tsize = sprite.getTexture()->getSize();
	sprite.setScale(size.x / tsize.x, size.y / tsize.y);
	sprite.setOrigin(tsize.x / 2.f, tsize.y / 2.f);
}

bool SfmlHelpers::SetWindowIcon(sf::Window& win, HICON hIcon, HINSTANCE hInstance) {
	::SendMessage(win.getSystemHandle(), WM_SETICON, 1, reinterpret_cast<LPARAM>(hIcon));
	::SendMessage(win.getSystemHandle(), WM_SETICON, 0, reinterpret_cast<LPARAM>(hIcon));
	return true;
}

bool SfmlHelpers::SetWindowIcon(sf::Window& win, UINT id, HINSTANCE hInstance) {
	auto hIcon = ::LoadIcon(hInstance ? hInstance : ::GetModuleHandle(nullptr), MAKEINTRESOURCE(id));
	return hIcon ? SetWindowIcon(win, hIcon) : false;
}

bool SfmlHelpers::SetWindowIcon(sf::Window& win, PCTSTR id, HINSTANCE hInstance) {
	auto hIcon = ::LoadIcon(hInstance ? hInstance : ::GetModuleHandle(nullptr), id);
	return hIcon ? SetWindowIcon(win, hIcon) : false;
}

void SfmlHelpers::SetWindowFullSize(sf::RenderWindow& win, sf::Vector2u const& size) {
	win.setSize(size);
	sf::View view(sf::Vector2f(size) / 2.f, sf::Vector2f(size));
	win.setView(view);
}
