#include "pch.h"
#include "SfmlHelpers.h"

namespace Sfml {
	std::string GetNameFromFileName(std::string const& fileName) {
		auto bs = fileName.find_last_of("/\\");
		std::string name;
		if (bs == std::string::npos)
			name = fileName.substr(0, fileName.find_last_of('.'));
		else
			name = fileName.substr(bs + 1);
		return name;
	}

	float CenterX(sf::Text const& text, sf::RenderTarget& target) {
		return (target.getSize().x - text.getLocalBounds().size.x) / 2;
	}

	float CenterY(sf::Text const& text, sf::RenderTarget& target) {
		return (target.getSize().y - text.getLocalBounds().size.y) / 2;
	}

	sf::Vector2f Center(sf::Text const& text, sf::RenderTarget& target) {
		return { CenterX(text, target), CenterY(text, target) };
	}

	void SetSpriteSizeCentered(sf::Sprite& sprite, sf::Vector2f const& size) {
		auto tsize = sprite.getTexture().getSize();
		sprite.setScale({ size.x / tsize.x, size.y / tsize.y });
		sprite.setOrigin({ tsize.x / 2.f, tsize.y / 2.f });
	}

	bool SetWindowIcon(sf::Window const& win, HICON hIcon) {
		::SendMessage(win.getNativeHandle(), WM_SETICON, 1, reinterpret_cast<LPARAM>(hIcon));
		::SendMessage(win.getNativeHandle(), WM_SETICON, 0, reinterpret_cast<LPARAM>(hIcon));
		return true;
	}

	bool SetWindowIcon(sf::Window const& win, UINT id, HINSTANCE hInstance) {
		auto hIcon = ::LoadIcon(hInstance ? hInstance : ::GetModuleHandle(nullptr), MAKEINTRESOURCE(id));
		return hIcon ? SetWindowIcon(win, hIcon) : false;
	}

	bool SetWindowIcon(sf::Window const& win, PCTSTR id, HINSTANCE hInstance) {
		auto hIcon = ::LoadIcon(hInstance ? hInstance : ::GetModuleHandle(nullptr), id);
		return hIcon ? SetWindowIcon(win, hIcon) : false;
	}

	void SetWindowFullSize(sf::RenderWindow& win, sf::Vector2u const& size) {
		win.setSize(size);
		sf::View view(sf::Vector2f(size) / 2.f, sf::Vector2f(size));
		win.setView(view);
	}

	bool StringNoCaseEqual::operator()(std::string const& lhs, std::string const& rhs) const {
		return _stricmp(lhs.c_str(), rhs.c_str()) < 0;
	}
}

