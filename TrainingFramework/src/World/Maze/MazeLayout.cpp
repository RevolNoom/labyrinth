#include "MazeLayout.hpp"

MazeLayout::MazeLayout(int width, int height)
{
	if (width < 1 || height < 1)
	{
		std::string msg = std::string("Invalid matrix dimension: ") + std::to_string(width) + "x" + std::to_string(height);
		throw std::exception(msg.c_str());
	}
	_size = { width, height };

	_layout = std::vector<WallOrganization>(width*height, WallOrganization());
}

WallOrganization& MazeLayout::GetCell(int x, int y)
{
	return _layout[_size.first * y + x];
}

MazeLayout::Coordinate MazeLayout::GetSize() const
{
	return _size;
}