#include "Cell.h"
#include <tuple>

Cell::Cell():
Sprite2D(ResourceManagers::GetInstance()->GetTexture("Tile1.tga"))
{
	SetSize(CELL_SIZE, CELL_SIZE);
	AddWalls(Wall::ALLWALL);
	BuildWalls();
	BuildCorners();
}


void Cell::AddWalls(int wallBits)
{
	_wallDirection |= (wallBits & Wall::ALLWALL);
}


void Cell::BuildWalls()
{
	auto wallTxtr = ResourceManagers::GetInstance()->GetTexture("WallVertical.tga");

	for (auto& w : _wallObj)
	{
		w = std::make_shared<SolidObject>(wallTxtr);
		w->SetSize(CORNER_SIZE, CORNER_SIZE);
	}
}


void Cell::BuildCorners()
{
	auto ThreeHalfCorner = 3.5 * CORNER_SIZE;

	auto cornerTxtr = ResourceManagers::GetInstance()->GetTexture("Corner.tga");

	for (auto& c : _cornerObj)
	{
		c = std::make_shared<SolidObject>(cornerTxtr);
		c->SetSize(CORNER_SIZE, CORNER_SIZE);
	}
}


Vector2 Cell::GetSize() const
{
	return { CELL_SIZE, CELL_SIZE };
}


void Cell::Draw()
{
	// Draw the floor
	Sprite2D::Draw();

	DrawWalls();
	DrawCorners();
}

int Cell::GetWalls()
{
	return _wallDirection & Wall::ALLWALL;
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
	_wallDirection = wallBits & Wall::ALLWALL;
}

void Cell::RemoveWalls(int wallBits)
{
	_wallDirection &= ~wallBits;
}



void Cell::Set2DPosition(Vector2 pos)
{
	Sprite2D::Set2DPosition(pos);

	SetWallPositions(pos);
	SetCornerPositions(pos);
}


void Cell::SetWallPositions(Vector2 pos)
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

	for (auto& w : wall)
	{
		int direction = std::get<0>(w);
		Vector2 offset = std::get<1>(w);
		Vector3 rot = std::get<2>(w);
		_wallObj[direction]->SetSize(WALL_WIDTH, WALL_HEIGHT);
		_wallObj[direction]->SetRotation(rot);
		_wallObj[direction]->Set2DPosition(pos + offset);
	}
}


void Cell::SetCornerPositions(Vector2 pos)
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

	for (auto& c : corner)
	{
		int direction = std::get<0>(c);
		Vector2 offset = std::get<1>(c);
		_cornerObj[direction]->Set2DPosition(pos + offset);
	}
}
