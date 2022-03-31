#include "Maze.hpp"

Maze::Maze(int width, int height) : _size({ width, height })
{
	_cells.reserve(width * height);
	for (int iii = 0; iii < width * height; ++iii)
		_cells.push_back(Cell(ResourceManagers::GetInstance()->GetTexture("Tile.tga"),
							ResourceManagers::GetInstance()->GetTexture("WallVertical.tga")));

	SetPosition(Vector2(0, 0));
	SetLayout(MazeLayoutGenerator::GetInstance()->Generate(this));
}


Maze::Maze(Coordinate size): Maze(size.first, size.second)
{
}


void Maze::RegisterToWorld(b2World* world)
{
	for (auto& c : _cells)
		c.RegisterToWorld(world);
}


void Maze::SetEnabled(bool enable)
{
	for (auto& c : _cells)
		c.SetEnabled(enable);
}


bool Maze::IsEnabled() const
{
	return GetCell({ 0, 0 }).IsEnabled();
}

void Maze::SetRotation(float angle)
{
	// TODO: uh.... :))))
	std::cout << "Maze::SetRotation not implemented yet\n";
}

float Maze::GetRotation() const
{
	return GetCell({ 0, 0 }).GetRotation();
}

void Maze::SetPosition(Vector2 center)
{
	_center = center;
	auto cellSize = GetCellSize();
	for (int col = 0; col < _size.first; ++col)
		for (int row = 0; row < _size.second; ++row)
		{
			Vector2 offset(cellSize.x * (col - 0.5 - float(_size.first) / 2), 
							cellSize.y * (row - 0.5 - float(_size.second) / 2));

			Vector2 cellPos = _center + offset;

			GetCell({ col, row }).SetPosition(cellPos); 
		}
}

Vector2 Maze::GetPosition() const
{
	return _center;
}


void Maze::SetSize(Vector2 size)
{
	auto layoutDims = GetLayout()->GetSize();
	SetCellSize(Vector2(size.x / layoutDims.first, size.y / layoutDims.second));
}


Vector2 Maze::GetSize() const
{
	auto cellSize = GetCellSize();
	auto layoutDims = GetLayout()->GetSize();
	return Vector2(cellSize.x * layoutDims.first, cellSize.y * layoutDims.second);
}

void Maze::SetCellSize(Vector2 size)
{
	for (auto& c : _cells)
		c.SetSize(size);
	SetPosition(GetPosition());
}

Vector2 Maze::GetCellSize() const
{
	return GetCell({ 0, 0 }).GetSize();
}

void Maze::SetLayout(std::shared_ptr<MazeLayout> l)
{
	if (l->GetSize() != _size)
	{
		std::cout << "Incompatible size: Maze " << _size.first << "x" << _size.second
			<< " vs Layout " << l->GetSize().first << "x" << l->GetSize().second << "\n";
		return;
	}

	_currentLayout = l;

	for (int col = 0; col < _size.first; ++col)
		for (int row = 0; row < _size.second; ++row)
			GetCell({ col, row }).SetProfile(l->GetCell({ col, row }));
}

std::shared_ptr<MazeLayout> Maze::GetLayout() const
{
	return _currentLayout;
}


void Maze::Draw()
{
	for (auto& c : _cells)
		c.Draw();
}


Cell& Maze::GetCell(Coordinate c)
{
	return _cells.at(_size.first * c.second + c.first);
}

const Cell& Maze::GetCell(Coordinate c) const
{
	return _cells.at(_size.first * c.second + c.first);
}

MazeLayout::Coordinate Maze::GetDimensions() const
{
	return _size;
}
