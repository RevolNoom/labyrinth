#include "Cell.h"
#include <tuple>

Cell::Cell(Vector2 initPos):
Sprite2D(ResourceManagers::GetInstance()->GetTexture("Tile1.tga")), 
_wallDirection(Wall::MASK)
{
	Set2DPosition(initPos);
	SetSize(CELL_SIZE, CELL_SIZE);

	BuildCorners();
	BuildWalls();
}

void Cell::BuildCorners()
{
	auto ThreeHalfCorner = 3.5 * CORNER_SIZE;

	using DIRECTION = int;
	using OFFSET = Vector2;

	std::tuple<DIRECTION, OFFSET> corner[]{
		{ CORNER_WN, Vector2(-ThreeHalfCorner, -ThreeHalfCorner)},
		{ CORNER_NE, Vector2(+ThreeHalfCorner, -ThreeHalfCorner)},
		{ CORNER_ES, Vector2(+ThreeHalfCorner, +ThreeHalfCorner)},
		{ CORNER_SW, Vector2(-ThreeHalfCorner, +ThreeHalfCorner)}
	};

	Vector2 cellPosition = Vector2(GetPosition().x, GetPosition().y);

	auto cornerTxtr = ResourceManagers::GetInstance()->GetTexture("Corner.tga");

	for (auto &c : corner)
	{
		int direction = std::get<0>(c);
		Vector2 offset = std::get<1>(c);
		_cornerObj[direction] = std::make_shared<SolidObject>(cornerTxtr, cellPosition + offset);
		_cornerObj[direction]->SetSize(CORNER_SIZE, CORNER_SIZE);
	}
}

Vector2 Cell::GetSize() const
{
	return { CELL_SIZE, CELL_SIZE };
}


void Cell::BuildWalls()
{
	auto ThreeHalfCorner = 3.5 * CORNER_SIZE;

	using DIRECTION = int;
	using OFFSET = Vector2;
	using ROTATION = Vector3;

	std::tuple<DIRECTION, OFFSET, ROTATION> wall[]{
		{ NORTH, Vector2(0, -ThreeHalfCorner), Vector3(0, 0, PI / 2)},
		{ EAST , Vector2(+ThreeHalfCorner, 0), Vector3(0, 0, 0)},
		{ SOUTH, Vector2(0, +ThreeHalfCorner), Vector3(0, 0, PI / 2)},
		{ WEST , Vector2(-ThreeHalfCorner, 0), Vector3(0, 0, 0)}
	}; 

	Vector2 cellPosition = Vector2(GetPosition().x, GetPosition().y);

	auto wallTxtr = ResourceManagers::GetInstance()->GetTexture("WallVertical.tga");

	for (auto &w : wall)
	{
		int direction = std::get<0>(w);
		Vector2 offset = std::get<1>(w);
		Vector3 rot = std::get<2>(w);
		_wallObj[direction] = std::make_shared<SolidObject>(wallTxtr, cellPosition + offset);
		_wallObj[direction]->SetSize(WALL_WIDTH, WALL_HEIGHT);
		_wallObj[direction]->SetRotation(rot);
	}
}

void Cell::DrawCorners()
{
	using CORNER_BIT = int;
	using CORNER_INDEX = int;
	std::pair<CORNER_BIT, CORNER_INDEX> corner[]{
									{WN, CORNER_WN},
									{NE, CORNER_NE},
									{ES, CORNER_ES},
									{SW, CORNER_SW} };

	for (auto& c : corner)
		if (_wallDirection & c.first)
			_cornerObj[c.second]->Draw();
}


void Cell::Draw()
{
	// Draw the floor
	Sprite2D::Draw();

	DrawWalls();
	DrawCorners();
}


void Cell::DrawWalls()
{
	using WALL_BIT = int;
	using WALL_INDEX = int;
	std::pair<WALL_BIT, WALL_INDEX> wall[]{
									{W, WEST},
									{N, NORTH},
									{E, EAST},
									{S ,SOUTH} };

	for (auto& w : wall)
		if (_wallDirection & w.first)
			_wallObj[w.second]->Draw();
}



void Cell::SetWalls(int wallBits)
{
	_wallDirection = wallBits & Wall::MASK;
}