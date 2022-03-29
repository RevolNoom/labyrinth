#pragma once

#include "World/PhysicObject.hpp"
#include "World/Maze/Wall.h"
#include "ResourceManagers.h"
#include <array>

class WallOrganization
{
public:
	// Enumerated in Clockwise direction
	enum Direction
	{
		// BITS
		W = 0x1,
		N = 0x2,
		E = 0x4,
		S = 0x8,

		NO_WALL = 0x0, 
		ALLWALL = 0xF,
	};

	WallOrganization(): WallOrganization(ALLWALL)
	{}

	WallOrganization(int directions): _wallDirection(directions)
	{}

	// TODO: This is Debugging value
	// Destroy after done
	int Value() { return _wallDirection; }

	// Return true if this org contains walls in all specified directions
	bool HasWalls(Direction dirs)
	{
		return (_wallDirection & dirs) == dirs;
	}

	// Set the walls into this configuration
	void SetWalls(Direction wallBits)
	{
		_wallDirection = wallBits;
	}

	// Add walls in specified positions, if they haven't been there already
	void AddWalls(Direction wallBits)
	{
		_wallDirection |= wallBits;
	}

	// Remove the walls in specified positions, if they are still there
	void RemoveWalls(Direction wallBits)
	{
		_wallDirection &= ~wallBits;
	}

private:
	int _wallDirection;
};

// Contains information of
// walls and corners wrapping it
class Cell : public Sprite2D, public PhysicObject
{
public:

	static constexpr int CORNER_SIZE = 10;
	static constexpr int CELL_SIZE = 8 * CORNER_SIZE;
	static constexpr int WALL_WIDTH = CORNER_SIZE;
	static constexpr int WALL_HEIGHT = 8 * CORNER_SIZE;


	Cell();


	void RegisterToWorld(b2World* world) override;

	void Init() {}

	void Draw();

	void SetOrganization(WallOrganization wo);
	WallOrganization GetOrganization();

	// The size in... uhhh... pixels (?) of this Cell
	// TODO: I may remove it if I deem it useless
	Vector2 GetSize() const;

	virtual void Set2DPosition(Vector2 pos) override;

	// Debugging
	std::shared_ptr<Wall> wall() { return _wallObj[0]; };
private:
	enum
	{
		// ARRAY INDEX
		WEST = 0,
		NORTH = 1,
		EAST = 2,
		SOUTH = 3,
	};

	// Create objects
	void BuildWalls();
	void DrawWalls();

	void SetWallPositions(Vector2 pos);


private:
	WallOrganization _worg;
	std::array<std::shared_ptr<Wall>, 4> _wallObj;
};
