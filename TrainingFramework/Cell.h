#pragma once

#include "World/SolidObject.hpp"
#include "ResourceManagers.h"
// Contains information of possible 
// sites adjacent to it
class Cell
{
public:

	// Enumerated in Clockwise direction

	enum Wall
	{
		// WALL
		W = 0x1,
		N = 0x2,
		E = 0x4,
		S = 0x8,

		MASK = 0xF,

		// CORNERS
		CORNER_WN = 0x3,
		CORNER_NE = 0x6,
		CORNER_ES = 0xC,
		CORNER_SW = 0x9,

		RANDOMIZED = 0x80
	};

	enum WallDirection
	{
		WEST = 0,
		NORTH = 1,
		EAST = 2,
		SOUTH = 3
	};

	Cell(Vector2 initPos);

	void Draw();
	
	void SetWalls(int wallBits);

	bool IsRandomized();

private:
	int _wallDirection;
	std::shared_ptr<Sprite2D> _floorObj;
	std::shared_ptr<SolidObject> _wallObj;
};
