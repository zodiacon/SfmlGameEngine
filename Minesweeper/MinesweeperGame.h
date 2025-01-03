#pragma once

#include <memory>
#include <vector>

enum class CellState {
	Empty,
	Open,
	Flag,
	Mine,
	Invalid,
};

struct CellItem {
	CellState State;
	int MinesAround;
};

class MinesweeperGame {
public:
	bool Init(int width, int height);
	void PlaceMines(int count);
	void PlaceMinesPercent(float percent);

	void Clear();

	CellItem const& GetCell(int x, int y) const;

	int OpenCell(int x, int y);
	bool SetFlag(int x, int y);
	bool ToggleFlag(int x, int y);
	int GetWidth() const;
	int GetHeight() const;
	int GetTotalFlags() const;
	int GetTotalMines() const;

private:
	std::vector<int> Randomize(int mines) const;
	int GetRandom(int size) const;
	void SetCell(int x, int y, CellState state, int mineCount = 0);

private:
	int m_TotalMines, m_TotalFlags, m_TotalOpen;
	int m_Width, m_Height;
	std::unique_ptr<CellItem[]> m_Cells;
};

