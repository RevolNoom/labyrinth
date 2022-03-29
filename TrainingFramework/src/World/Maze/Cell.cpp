#include "Cell.h"
#include "World/Maze/Wall.h"
#include <tuple>

Cell::Cell():
Sprite2D(ResourceManagers::GetInstance()->GetTexture("Tile1.tga")),
_worg(WallOrganization())
{
	SetSize(CELL_SIZE, CELL_SIZE);
	BuildWalls();
}

void Cell::RegisterToWorld(b2World* world)
{
	for (auto& w : _wallObj)
		w->RegisterToWorld(world);
}

void Cell::BuildWalls()
{
	auto wallTxtr = ResourceManagers::GetInstance()->GetTexture("WallVertical.tga");

	for (auto& w : _wallObj)
	{
		w = std::make_shared<Wall>(wallTxtr);
		w->SetSize(WALL_WIDTH, WALL_HEIGHT);
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
}

WallOrganization Cell::GetOrganization()
{
	return _worg;
}


void Cell::DrawWalls()
{
	using WALL_BIT = WallOrganization::Direction;
	using WALL_INDEX = int;
	std::pair<WALL_BIT, WALL_INDEX> wall[]{
									{WallOrganization::Direction::W, WEST},
									{WallOrganization::Direction::N, NORTH},
									{WallOrganization::Direction::E, EAST},
									{WallOrganization::Direction::S ,SOUTH} };

	//std::cout << "Draw wall: " << _worg.Value() << "\n";
	for (auto& w : wall)
	{
		if (_worg.HasWalls(w.first))
			_wallObj[w.second]->Draw();
	}
}

void Cell::SetOrganization(WallOrganization org)
{
	// TODO: Disable/Enable walls
	_worg = org;
}



void Cell::Set2DPosition(Vector2 pos)
{
	Sprite2D::Set2DPosition(pos);

	SetWallPositions(pos);
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