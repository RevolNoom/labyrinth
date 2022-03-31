#include "Cell.h"
#include <tuple>


Cell::Cell(std::shared_ptr<Texture> floorTxtr, std::shared_ptr<Texture> verticalWallTxtr)
{
	_floor = std::make_shared<Sprite2D>(floorTxtr);
	BuildWalls(verticalWallTxtr);
}


void Cell::RegisterToWorld(b2World* world)
{
	for (auto& w : _wallObj)
		w->RegisterToWorld(world);
	SetEnabled(true);
}


void Cell::SetEnabled(bool enable)
{
	_worg.SetEnabled(enable);

	using WALL_BIT = CellProfile::Bit;
	using WALL_INDEX = int;
	std::pair<WALL_BIT, WALL_INDEX> wall[]{
									{CellProfile::Bit::W, WEST},
									{CellProfile::Bit::N, NORTH},
									{CellProfile::Bit::E, EAST},
									{CellProfile::Bit::S ,SOUTH} };
	for (auto& w : wall)
		_wallObj[w.second]->SetEnabled(enable && _worg.HasWalls(w.first));
}


bool Cell::IsEnabled() const
{
	return _worg.IsEnabled();
}

void Cell::SetPosition(Vector2 pos)
{
	_floor->Set2DPosition(pos.x, pos.y);
	SetWallPositions(pos);

	//SetItemPosition(pos);
}

Vector2 Cell::GetPosition() const
{
	auto result = _floor->GetPosition();
	return Vector2(result.x, result.y);
}

void Cell::SetRotation(float angle)
{
	// TODO: I guess I won't be needing this for a while :P
	std::cout << "Cell::SetRotation not implemented yet\n";
}

float Cell::GetRotation() const
{
	return _floor->GetRotation().z;
}


void Cell::SetSize(Vector2 size)
{
	_floor->SetSize(size.x/2, size.y/2);

	for (auto& w : _wallObj)
		w->SetSize(GetVerticalWallSize());

	SetWallPositions(GetPosition());
}


Vector2 Cell::GetSize() const
{
	return _floor->GetSize();
}


CellProfile Cell::GetProfile()
{
	return _worg;
}


void Cell::SetProfile(CellProfile org)
{
	_worg = org;
	SetEnabled(IsEnabled());
}


void Cell::Draw()
{
	_floor->Draw();
	DrawWalls();
	//_item->Draw();
}


void Cell::BuildWalls(std::shared_ptr<Texture> verticalWallTxtr)
{
	for (auto& w : _wallObj)
	{
		w = std::make_shared<SolidObject>(verticalWallTxtr);
		w->SetSize(GetVerticalWallSize());
	}
}


void Cell::DrawWalls()
{
	using WALL_BIT = CellProfile::Bit;
	using WALL_INDEX = int;
	std::pair<WALL_BIT, WALL_INDEX> wall[]{
									{CellProfile::Bit::W, WEST},
									{CellProfile::Bit::N, NORTH},
									{CellProfile::Bit::E, EAST},
									{CellProfile::Bit::S ,SOUTH} };

	for (auto& w : wall)
	{
		if (_worg.HasWalls(w.first))
			_wallObj[w.second]->Draw();
	}
}


void Cell::SetWallPositions(Vector2 pos)
{
	auto ThreeHalfCorner = 3.5 * GetCornerSize().x;

	using DIRECTION = int;
	using OFFSET = Vector2;
	using ROTATION = float;

	std::tuple<DIRECTION, OFFSET, ROTATION> wall[]{
		{ NORTH, Vector2(0, -ThreeHalfCorner),+PI / 2},
		{ EAST , Vector2(+ThreeHalfCorner, 0), 0},
		{ SOUTH, Vector2(0, +ThreeHalfCorner),-PI / 2},
		{ WEST , Vector2(-ThreeHalfCorner, 0), 0}
	};

	for (auto& w : wall)
	{
		int direction = std::get<0>(w);
		Vector2 offset = std::get<1>(w);
		float rot = std::get<2>(w);
		_wallObj[direction]->SetSize(GetVerticalWallSize());
		_wallObj[direction]->SetPosition(pos + offset);
		_wallObj[direction]->SetRotation(rot);
	}
}


Vector2 Cell::GetCornerSize()
{
	return GetSize() / 8;
}


Vector2 Cell::GetVerticalWallSize()
{
	auto corner = GetCornerSize();
	return Vector2(corner.x, 8 * corner.y);
}


/*
bool Cell::PutIn(std::shared_ptr<BaseObject> newItem)
{
	if (_item != nullptr)
		return false;
	_item = newItem;

	// Align item to the center
	SetItemPosition(Vector2(GetPosition().x, GetPosition().y));
	return true;
}
}*/