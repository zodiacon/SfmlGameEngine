#define NOMINMAX

#include <Windows.h>
#include <SfmlGameEngine.h>

using namespace std;

_Use_decl_annotations_
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
	Game game;
	game.Init(800, 600, "Hello");
	game.LoadFont("arial.ttf");

	auto empty = make_unique<Scene>(game);
	empty->Draw = [&](auto& win, auto dt) {
		win.clear();

		auto& font = game.Font("Arial");
		sf::Text text(font, "Hello, SFML Engine!", 40);
		text.setPosition(Sfml::Center(text, win));

		sf::RectangleShape r;
		r.setFillColor(Colors::Aqua);
		r.setRotation(sf::degrees(45));
		r.setPosition(sf::Vector2f(100, 100));
		r.setSize(sf::Vector2f(50, 50));

		win.draw(r);

		win.draw(text);
		};

	game.PushScene(move(empty));
	game.Run();

	return 0;
}
