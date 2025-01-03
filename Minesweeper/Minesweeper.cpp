#include "pch.h"
#include <Game.h>
#include "MinesweeperGame.h"
#include <SfmlHelpers.h>
#include "Resource.h"
#include <StandardColors.h>

_Use_decl_annotations_
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
	Game game;
	game.Init(800, 600, "SFML Minesweeper");
	auto hIcon = ::LoadIcon(::GetModuleHandle(nullptr), MAKEINTRESOURCE(IDI_MINESWEEPER));

	::SendMessage(game.Window().getSystemHandle(), WM_SETICON, 1, reinterpret_cast<LPARAM>(hIcon));
	::SendMessage(game.Window().getSystemHandle(), WM_SETICON, 0, reinterpret_cast<LPARAM>(hIcon));

	auto main = std::make_unique<Scene>(game);
	game.LoadTexture("mine.png");
	game.LoadTexture("flag.png");
	game.LoadFont("arial.ttf");

	MinesweeperGame ms;
	int width = 30, height = 20;
	unsigned cellSize = 40;
	auto winSize = sf::Vector2u(width * cellSize, height * cellSize);
	game.Window().setSize(winSize);
	sf::View view(sf::Vector2f(winSize) / 2.f, sf::Vector2f(winSize));
	game.Window().setView(view);
	ms.Init(width, height);
	ms.PlaceMinesPercent(20);
	bool gameOver = false;

	auto& flag = game.Texture("flag");
	sf::Sprite flagSprite(flag);
	SfmlHelpers::SetSpriteSizeCentered(flagSprite, sf::Vector2f((float)cellSize, (float)cellSize) * .8f);

	auto& mine = game.Texture("mine");
	sf::Sprite mineSprite(mine);
	SfmlHelpers::SetSpriteSizeCentered(mineSprite, sf::Vector2f((float)cellSize, (float)cellSize) * .9f);

	sf::Text mineCountText("0", game.Font("arial"), int(cellSize * .8f));
	mineCountText.setOutlineColor(sf::Color::White);

	auto emptyCellColor = Colors::LightBlue;

	main->HandleEvent = [&](auto& evt) {
		if (gameOver)
			return false;

		switch (evt.type) {
			case sf::Event::MouseButtonReleased:
				int x = evt.mouseButton.x, y = evt.mouseButton.y;
				auto cx = x / cellSize, cy = y / cellSize;
				auto& cell = ms.GetCell(x, y);
				if (evt.mouseButton.button == sf::Mouse::Right) {
					ms.ToggleFlag(cx, cy);
					if (ms.GetTotalFlags() == ms.GetTotalMines()) {
						// all flags placed
					}
					return true;
				}
				else if (evt.mouseButton.button == sf::Mouse::Left) {
					if (ms.OpenCell(cx, cy) < 0) {
						// bomb! game over
						gameOver = true;
					}
					return true;
				}
				break;
		}
		return false;
		};

	main->Draw = [&](auto& win, auto dt) {
		sf::RectangleShape r(sf::Vector2f(cellSize - 2.f, cellSize - 2.f));
		r.setOutlineColor(sf::Color::Blue);
		r.setOutlineThickness(1.0f);
		for (int y = 0; y < ms.GetHeight(); y++) {
			for (int x = 0; x < ms.GetWidth(); x++) {
				r.setPosition(x * cellSize + 1.f, y * cellSize + 1.f);
				auto state = ms.GetCell(x, y).State;
				switch (state) {
					case CellState::Flag:
						r.setFillColor(sf::Color::Black);
						win.draw(r, sf::RenderStates::Default);
						flagSprite.setPosition(r.getPosition() + sf::Vector2f(cellSize / 2.f, cellSize / 2.f));
						win.draw(flagSprite, sf::RenderStates::Default);
						break;

					case CellState::Open:
					{
						r.setFillColor(sf::Color::Black);
						win.draw(r, sf::RenderStates::Default);
						auto mines = ms.GetCell(x, y).MinesAround;
						if (mines) {
							mineCountText.setString(std::to_string(mines));
							mineCountText.setPosition(r.getPosition() + sf::Vector2f(10, 1));
							win.draw(mineCountText, sf::RenderStates::Default);
						}
						else {
							r.setFillColor(sf::Color::Black);
							win.draw(r, sf::RenderStates::Default);
							r.setFillColor(emptyCellColor);
						}
						break;
					}

					default:
						r.setFillColor(emptyCellColor);
						win.draw(r, sf::RenderStates::Default);
						break;
				}
				if (gameOver && ms.GetCell(x, y).MinesAround < 0) {
					r.setFillColor(sf::Color::Red);
					win.draw(r, sf::RenderStates::Default);
					mineSprite.setPosition(r.getPosition() + sf::Vector2f(cellSize / 2.f, cellSize / 2.f));
					win.draw(mineSprite, sf::RenderStates::Default);
				}
			}
		}
		};

	game.PushScene(std::move(main));
	game.Run();

	return 0;
}
