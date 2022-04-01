#include "Maze.hpp"
#include "World/Maze/ItemGenerator.h"
#include "World/Maze/Item/TransPlatform.h"

Maze::Maze(int width, int height) : 
	_size({ width, height }), 
	_currentLayout(Coordinate(width, height)),
	_itemLayout(Coordinate(width, height)),
	_cells(Coordinate(width, height))
{
	auto clone = Cell(ResourceManagers::GetInstance()->GetTexture("Tile.tga"),
		ResourceManagers::GetInstance()->GetTexture("WallVertical.tga"));

	for (int col = 0; col < _size.first; ++col)
		for (int row = 0; row < _size.second; ++row)
		{
			_cells.GetCell({ col, row }) = std::dynamic_pointer_cast<Cell>(clone.Clone());
		}

	SetPosition(Vector2(0, 0));
	SetLayout(MazeLayoutGenerator::GetInstance()->Generate(this));
	GenerateItems();
}


Maze::Maze(Coordinate size): Maze(size.first, size.second)
{
}


void Maze::RegisterToWorld(b2World* world)
{
	for (int col = 0; col < _size.first; ++col)
		for (int row = 0; row < _size.second; ++row)
		{
			_cells.GetCell({ col, row })->RegisterToWorld(world);

			std::shared_ptr<PhysicObject> &item = _itemLayout.GetCell({ col, row });
			if (item != nullptr)
				item->RegisterToWorld(world);
		}
}


void Maze::SetEnabled(bool enable)
{
	for (int col = 0; col < _size.first; ++col)
		for (int row = 0; row < _size.second; ++row)
		{
			_cells.GetCell({ col, row })->SetEnabled(enable);
		}
}


bool Maze::IsEnabled() const
{
	return _cells.GetCell({ 0, 0 })->IsEnabled();
}

void Maze::SetRotation(float angle)
{
	// TODO: uh.... :))))
	std::cout << "Maze::SetRotation not implemented yet\n";
}

float Maze::GetRotation() const
{
	return _cells.GetCell({ 0, 0 })->GetRotation();
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

			_cells.GetCell({ col, row })->SetPosition(cellPos);
			
			auto &item = _itemLayout.GetCell({ col, row });
			if (item != nullptr)
				item->SetPosition(cellPos);
		}
}

Vector2 Maze::GetPosition() const
{
	return _center;
}


void Maze::SetSize(Vector2 size)
{
	auto layoutDims = GetLayout().GetSize();
	SetCellSize(Vector2(size.x / layoutDims.first, size.y / layoutDims.second));
}


Vector2 Maze::GetSize() const
{
	auto cellSize = GetCellSize();
	auto layoutDims = GetLayout().GetSize();
	return Vector2(cellSize.x * layoutDims.first, cellSize.y * layoutDims.second);
}

void Maze::SetCellSize(Vector2 size)
{
	for (int col = 0; col < _size.first; ++col)
		for (int row = 0; row < _size.second; ++row)
		{
			_cells.GetCell({ col, row })->SetSize(size);
		}
	SetPosition(GetPosition());
}

Vector2 Maze::GetCellSize() const
{
	return _cells.GetCell({ 0, 0 })->GetSize();
}

void Maze::SetLayout(const MazeLayout<CellProfile> &l)
{
	if (l.GetSize() != _size)
	{
		std::cout << "Incompatible size: Maze " << _size.first << "x" << _size.second
			<< " vs Layout " << l.GetSize().first << "x" << l.GetSize().second << "\n";
		return;
	}

	_currentLayout = l;

	for (int col = 0; col < _size.first; ++col)
		for (int row = 0; row < _size.second; ++row)
			_cells.GetCell({ col, row })->SetProfile(l.GetCell({ col, row }));
}

const MazeLayout<CellProfile>& Maze::GetLayout() const
{
	return _currentLayout;
}


void Maze::Draw()
{
	for (int iii = 0; iii < _size.first; ++iii)
		for (int jjj = 0; jjj < _size.second; ++jjj)
		{
			auto &cell = _cells.GetCell({ iii, jjj });
			cell->Draw();

			auto &item = _itemLayout.GetCell({ iii, jjj });
			if (item != nullptr)
			{
				item->Draw();
			}
		}
}


void Maze::GenerateItems()
{
	ItemGenerator itg; 
	
	auto transplatform = std::make_shared<TransPlatform>(this, 3);
	transplatform->SetSize(GetCellSize() / 2);
	itg.AddMandatory(transplatform, 2);

	_itemLayout = itg.Generate(this);
}

Coordinate Maze::GetDimensions() const
{
	return _size;
}

void Maze::Update(float delta)
{
	for (int col = 0; col < _size.first; ++col)
		for (int row = 0; row < _size.second; ++row)
		{
			auto& item = _itemLayout.GetCell({ col, row });
			if (item != nullptr)
				item->Update(delta);
		}
}

std::shared_ptr<PhysicObject> Maze::Clone()
{
	auto newClone = std::make_shared<Maze>(GetDimensions());

	newClone->SetRotation(GetRotation());
	newClone->SetPosition(GetPosition());
	newClone->SetEnabled(IsEnabled());
	newClone->SetSize(GetSize());

	newClone->SetLayout(GetLayout());

	return newClone;
}
