#define NOMINMAX

#include <Windows.h>
#include <SfmlHelpers.h>
#include <Game.h>

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
		sf::Text text("Hello, SFML Engine!", font, 40);
		text.setPosition(SfmlHelpers::Center(text, win));

		win.draw(text);
		};

	game.PushScene(move(empty));
	game.Run();

	return 0;
}