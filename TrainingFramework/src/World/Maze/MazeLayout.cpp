#include "MazeLayout.hpp"

MazeLayout::MazeLayout(int width, int height)
{
	if (width < 1 || height < 1)
	{
		std::string msg = std::string("Invalid matrix dimension: ") + std::to_string(width) + "x" + std::to_string(height);
		std::cout << msg << "\n";
		throw std::exception(msg.c_str());
	}
	_size = { width, height };
	
	_layout.resize(width * height);
}


MazeLayout::MazeLayout(Coordinate size) : MazeLayout(size.first, size.second)
{
}


CellProfile& MazeLayout::GetCell(Coordinate c)
{
	return _layout[_size.first * c.second + c.first];
}


MazeLayout::Coordinate MazeLayout::GetSize() const
{
	return _size;
}