#include "Maze.hpp"

Maze::Maze(int width, int height) : _size({ width, height })
{
	_cells = std::vector<Cell>(width * height);
	Set2DPosition(Vector2(0, 0));
	//std::cout << "Swapping:\n";
	SwapLayout(MazeLayoutGenerator().Generate(width, height));
	//std::cout << "Swapped:\n";
}

void Maze::RegisterToWorld(b2World* world)
{
	for (auto& c : _cells)
		c.RegisterToWorld(world);
}

void Maze::SwapLayout(std::shared_ptr<MazeLayout> l)
{
	if (l->GetSize() != _size)
	{
		std::cerr << "Incompatible size: Maze " << _size.first << "x" << _size.second
			<< " vs Layout " << l->GetSize().first << "x" << l->GetSize().second << "\n";
		return;
	}

	/*
	std::cout << "Before swapping: ";
	for (int row = 0; row < _size.first; ++row)
		for (int col = 0; col < _size.second; ++col)
			std::cout<<GetCell(row, col).GetOrganization().Value()<<" ";


	std::cout << "After swapping: ";
	for (int row = 0; row < _size.first; ++row)
		for (int col = 0; col < _size.second; ++col)
			std::cout << GetCell(row, col).GetOrganization().Value() << " ";*/
	for (int col = 0; col < _size.first; ++col)
		for (int row = 0; row < _size.second; ++row)
			GetCell(col, row).SetOrganization(l->GetCell(col, row));
}


void Maze::Draw()
{
	for (int col = 0; col < _size.first; ++col)
		for (int row = 0; row < _size.second; ++row)
		{
			GetCell(col, row).Draw();
		}
}


void Maze::SetEnable(bool enable)
{
	for (auto& c : _cells)
		c.SetEnable(enable);
}

void Maze::Set2DPosition(Vector2 topLeftCornerPos)
{
	for (int col = 0; col < _size.first; ++col)
		for (int row = 0; row < _size.second; ++row)
		{
			Vector2 offset = Vector2(Cell::CELL_SIZE * (col + 0.5), Cell::CELL_SIZE * (row + 0.5));
			Vector2 cellPos = topLeftCornerPos + offset;
			GetCell(col, row).Set2DPosition(cellPos);
		}
}

Cell& Maze::GetCell(int col, int row)
{
	return _cells[_size.first * row + col];
}