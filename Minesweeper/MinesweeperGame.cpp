#include "pch.h"
#include "MinesweeperGame.h"
#include <cassert>
#include <random>
#include <ranges>

bool MinesweeperGame::Init(int width, int height) {
	Clear();

	m_Cells = std::make_unique<CellItem[]>(width * height);
	if (!m_Cells)
		return false;

	m_Width = width;
	m_Height = height;

	for (int y = 0; y < height; y++)
		for (int x = 0; x < width; x++)
			SetCell(x, y, CellState::Empty, 0);

	return true;
}

void MinesweeperGame::PlaceMines(int mines) {
	m_TotalMines = mines;
	auto locations = Randomize(mines);
	for(auto pos : locations) {
		assert(pos < m_Width * m_Height);
		SetCell(pos % m_Width, pos / m_Width, CellState::Empty, -1);
	}
}

void MinesweeperGame::PlaceMinesPercent(float percent) {
	PlaceMines(int(m_Width * m_Height * percent / 100));
}

int MinesweeperGame::GetWidth() const {
	return m_Width;
}

int MinesweeperGame::GetHeight() const {
	return m_Height;
}

int MinesweeperGame::GetTotalFlags() const {
	return m_TotalFlags;
}

int MinesweeperGame::GetTotalMines() const {
	return m_TotalMines;
}

void MinesweeperGame::Clear() {
	m_Cells.reset();
	m_TotalFlags = m_TotalMines = m_TotalOpen = 0;
}

CellItem const& MinesweeperGame::GetCell(int x, int y) const {
	static const CellItem invalid{ CellState::Invalid };

	if (x < 0 || x >= m_Width || y < 0 || y >= m_Height)
		return invalid;

	assert(m_Cells);
	int index = y * m_Width + x;
	return m_Cells[index];
}

int MinesweeperGame::OpenCell(int x, int y) {
	if (GetCell(x, y).MinesAround < 0)
		return -1;

	switch (GetCell(x, y).State) {
		case CellState::Mine:
			return -1;      // mine

		case CellState::Open:
			return GetCell(x, y).MinesAround;

	}

	SetCell(x, y, CellState::Open);
	m_TotalOpen++;

	int mines = 0;
	for (int xx = x - 1; xx <= x + 1; xx++)
		for (int yy = y - 1; yy <= y + 1; yy++)
			if (xx != x || yy != y) {
				auto& cell = GetCell(xx, yy);
				if (cell.MinesAround == -1)
					mines++;
			}

	SetCell(x, y, CellState::Open, mines);
	if (mines == 0) {
		for (int xx = x - 1; xx <= x + 1; xx++)
			for (int yy = y - 1; yy <= y + 1; yy++) {
				if (xx == x && yy == y)
					continue;
				if (GetCell(xx, yy).State == CellState::Empty)
					OpenCell(xx, yy);
			}
	}
	return mines;
}

bool MinesweeperGame::SetFlag(int x, int y) {
	if (GetCell(x, y).State == CellState::Flag)
		return false;

	SetCell(x, y, CellState::Flag);
	m_TotalFlags++;
	return true;
}

bool MinesweeperGame::ToggleFlag(int x, int y) {
	auto& cell = GetCell(x, y);
	if (cell.State == CellState::Open)
		return false;

	if (cell.State != CellState::Flag) {
		SetCell(x, y, CellState::Flag);
		m_TotalFlags++;
	}
	else {
		if (m_TotalFlags == m_TotalMines)
			return false;

		SetCell(x, y, CellState::Empty);
		m_TotalFlags--;
	}
	return true;
}

void MinesweeperGame::SetCell(int x, int y, CellState state, int mineCount) {
	assert(m_Cells);
	int index = y * m_Width + x;
	m_Cells[index].State = state;
	if(mineCount)
		m_Cells[index].MinesAround = mineCount;
}

std::vector<int> MinesweeperGame::Randomize(int mines) const {
	using namespace std;
	using namespace std::ranges;
	using namespace std::views;

	auto total = m_Width * m_Height;
	auto range = iota(0, total) | to<vector>();
	for (int i = 0; i < total; i++)
		std::swap(range[GetRandom(total)], range[GetRandom(total)]);
	return range | take(mines) | to<vector>();
}

int MinesweeperGame::GetRandom(int size) const {
	static std::random_device dev;
	static std::default_random_engine engine(dev());
	std::uniform_int_distribution<> dist(0, size - 1);
	return dist(engine);
}
