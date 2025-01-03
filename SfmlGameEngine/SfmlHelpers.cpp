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
