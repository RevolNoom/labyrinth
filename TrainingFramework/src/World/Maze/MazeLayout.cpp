#include "MazeLayout.hpp"

MazeLayout::MazeLayout(int width, int height, Vector2 initPos)
{
	if (width < 1 || height < 1)
	{
		std::string msg = std::string("Invalid matrix dimension: ") + std::to_string(width) + "x" + std::to_string(height);
		throw std::exception(msg.c_str());
	}
	_width = width;
	_height = height;

	_layout.resize(width * height);
	for (auto& l : _layout)
		l = std::make_shared<Cell>();

	Set2DPosition(initPos);
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

void MazeLayout::Set2DPosition(Vector2 topLeftCornerPos)
{
	for (int row = 0; row < _width; ++row)
		for (int col = 0; col < _height; ++col)
		{
			Vector2 offset = Vector2(Cell::CELL_SIZE * (col + 0.5), Cell::CELL_SIZE * (row + 0.5));
			Vector2 cellPos = topLeftCornerPos + offset;
			_layout[_width * row + col]->Set2DPosition(cellPos);
		}
}