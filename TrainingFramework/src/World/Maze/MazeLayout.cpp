#include "MazeLayout.hpp"

MazeLayout::MazeLayout(Vector2 initPos, int width, int height)
{
	if (width < 1 || height < 1)
	{
		std::string msg = std::string("Invalid matrix dimension: ") + std::to_string(width) + "x" + std::to_string(height);
		throw std::exception(msg.c_str());
	}
	_width = width;
	_height = height;
	_layout.resize(width * height);

	for (int row = 0; row < width; ++row)
		for (int col = 0; col < height; ++col)
		{
			Vector2 offset = Vector2(Cell::CELL_SIZE * (col+0.5), Cell::CELL_SIZE * (row + 0.5));
			_layout[_width * row + col] = std::make_shared<Cell>(initPos + offset);
		}
}

void MazeLayout::Draw()
{
	for (auto& cell: _layout)
		cell->Draw();
}

std::shared_ptr<Cell> MazeLayout::GetCell(int x, int y)
{
	return _layout[_width * y + x];
}

std::pair<int, int> MazeLayout::GetSize() const
{
	return {_width, _height};
}
