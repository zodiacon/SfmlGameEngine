#include "pch.h"
#include <Game.h>
#include "MinesweeperGame.h"
#include <SfmlGameEngine.h>
#include <format>
#include <TGUI/TGUI.hpp>
#include <TGUI/Backend/SFML-Graphics.hpp>
#include "Resource.h"

using namespace tgui;

struct LevelData {
	const char* text;
	int width, height;
	float percent;
};

_Use_decl_annotations_
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
	MinesweeperGame ms;
	Game game;
	game.Init(800, 600, "SFML Minesweeper");
	SfmlHelpers::SetWindowIcon(game.Window(), IDI_MINESWEEPER);

	auto main = std::make_shared<Scene>(game);
	game.LoadTexture("mine.png");
	game.LoadTexture("flag.png");
	game.LoadFont("arial.ttf");
	game.LoadFont("space.ttf");

	bool gameOver = false, gameWon = false;
	unsigned cellSize = 40;
	auto statHeight = 40, xoffset = 20;
	auto& flag = game.Texture("flag");
	sf::Sprite flagSprite(flag);
	SfmlHelpers::SetSpriteSizeCentered(flagSprite, sf::Vector2f((float)cellSize, (float)cellSize) * .8f);

	auto& mine = game.Texture("mine");
	sf::Sprite mineSprite(mine);
	SfmlHelpers::SetSpriteSizeCentered(mineSprite, sf::Vector2f((float)cellSize, (float)cellSize) * .9f);

	auto font = game.Font("arial");
	sf::Text mineCountText(font, "0", int(cellSize * .8f));
	mineCountText.setOutlineColor(sf::Color::White);

	auto space = game.Font("space");
	auto emptyCellColor = Colors::LightBlue;

	main->Update = [&](auto dt) {
		if (ms.IsGridFull()) {
			// game over, win!
			gameWon = true;
			gameOver = true;
			game.Pause();
		}
		};

	main->HandleEvent = [&](sf::Event const& evt) {
		if (gameOver)
			return false;

		if (evt.is<sf::Event::MouseButtonReleased>()) {
			auto params = evt.getIf<sf::Event::MouseButtonReleased>();
			int x = params->position.x, y = params->position.y;
			auto cx = (x - xoffset) / cellSize, cy = (y - statHeight) / cellSize;
			auto& cell = ms.GetCell(x, y);
			if (params->button == sf::Mouse::Button::Right) {
				ms.ToggleFlag(cx, cy);
				if (ms.GetTotalFlags() == ms.GetTotalMines()) {
					// all flags placed
				}
				return true;
			}
			else if (params->button == sf::Mouse::Button::Left) {
				if (ms.OpenCell(cx, cy) < 0) {
					// bomb! game over
					gameOver = true;
					game.Pause();
				}
				return true;
			}
		}
		return false;
		};

	main->Draw = [&](auto& win, auto dt) {
		sf::RectangleShape r(sf::Vector2f(cellSize - 2.f, cellSize - 2.f));
		r.setOutlineColor(sf::Color::Blue);
		r.setOutlineThickness(1.0f);

		sf::Text stats(space, std::format("Time: {} Flags: {} Left: {}",
			(int)game.GetTime().asSeconds(), ms.GetTotalFlags(), ms.GetTotalMines() - ms.GetTotalFlags()), 25);
		stats.setPosition(sf::Vector2f(SfmlHelpers::CenterX(stats, win), 4));
		stats.setFillColor(Colors::Yellow);
		win.draw(stats);

		for (int y = 0; y < ms.GetHeight(); y++) {
			for (int x = 0; x < ms.GetWidth(); x++) {
				r.setPosition(Vector2f(x * cellSize + 1.f + xoffset, y * cellSize + 1.f + statHeight));
				auto state = ms.GetCell(x, y).State;
				switch (state) {
					case CellState::Flag:
						r.setFillColor(sf::Color::Transparent);
						win.draw(r);
						flagSprite.setPosition(r.getPosition() + sf::Vector2f(cellSize / 2.f, cellSize / 2.f));
						flagSprite.setColor(gameOver ? Colors::Gray : Colors::White);
						win.draw(flagSprite);
						break;

					case CellState::Open:
					{
						r.setFillColor(sf::Color::Transparent);
						win.draw(r, sf::RenderStates::Default);
						auto mines = ms.GetCell(x, y).MinesAround;
						if (mines) {
							mineCountText.setString(std::to_string(mines));
							mineCountText.setPosition(r.getPosition() + sf::Vector2f(10, 1));
							mineCountText.setFillColor(gameOver ? Colors::Gray : Colors::White);
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
				if (gameOver && !gameWon && ms.GetCell(x, y).MinesAround < 0) {
					r.setFillColor(state != CellState::Flag ? sf::Color::Red : sf::Color::Transparent);
					win.draw(r, sf::RenderStates::Default);
					mineSprite.setPosition(r.getPosition() + sf::Vector2f(cellSize / 2.f, cellSize / 2.f));
					win.draw(mineSprite, sf::RenderStates::Default);
				}
			}
		}
		if (gameWon) {
			sf::Text gameOver(space, "  GAME OVER  \nYou have won!", 40);
			gameOver.setStyle(sf::Text::Bold);
			gameOver.setFillColor(Colors::LightGreen);
			gameOver.setPosition(SfmlHelpers::Center(gameOver, win));
			win.draw(gameOver, sf::RenderStates::Default);
		}
		};

	auto menu = std::make_shared<Scene>(game);

	char path[MAX_PATH];
	::GetModuleFileNameA(nullptr, path, _countof(path));
	*strrchr(path, '\\') = 0;
	strcat_s(path, "\\Themes\\black.txt");
	Theme::setDefault(path);

	Gui gui(game.Window());
	menu->SetWindowSize(600, 600);
	LevelData levels[] = {
		{ "Beginner", 10, 10, 15 },
		{ "Intermediate", 15, 15, 20 },
		{ "Expert", 20, 20, 20 },
		{ "Master", 30, 20, 20 },
		{ "Superhuman", 35, 25, 25 },
	};

	int i = 0;
	static int selectedLevel = 1;
	for (auto& level : levels) {
		auto radio = RadioButton::create();
		radio->setText(level.text);
		radio->setTextSize(25);
		radio->setOrigin(.5f, .5f);
		radio->setPosition("30%", 100 + i++ * 35);
		radio->setChecked(i == selectedLevel);
		radio->setUserData(i);
		radio->onCheck([=] {
			selectedLevel = radio->getUserData<int>();
			});
		gui.add(radio);
	}

	auto newGame = Button::create("Start");
	newGame->setOrigin(.5f, .5f);
	newGame->setPosition("50%", 500);
	newGame->setTextSize(30);

	gui.add(newGame);
	newGame->onPress([&] {
		gameOver = gameWon = false;
		auto& level = levels[selectedLevel - 1];
		int width = level.width, height = level.height;
		auto winSize = sf::Vector2u(width * cellSize + xoffset * 2, height * cellSize + statHeight + xoffset);
		main->SetWindowSize(winSize);
		ms.Init(width, height);
		ms.PlaceMinesPercent(level.percent);
		game.Window().setTitle(std::format("SFML Minesweeper ({})", level.text));
		game.PopScene();
		});
	menu->HandleEvent = [&](auto& evt) {
		return gui.handleEvent(evt);
		};

	sf::Text title(font, "MINESWEEPER - SFML edition", 30);
	title.setFillColor(Colors::Yellow);
	menu->Draw = [&](auto& win, auto dt) {
		title.setPosition(sf::Vector2f(SfmlHelpers::CenterX(title, game.Window()), 20));
		win.draw(title);
		gui.draw();
		};

	game.PushScene(main);
	game.PushScene(menu);
	game.Run();

	return 0;
}

