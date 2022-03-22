#pragma once

#include "World/SolidObject.hpp"
#include "ResourceManagers.h"
#include <array>


// Contains information of
// walls and corners wrapping it
class Cell : public Sprite2D
{
public:

	static constexpr int CORNER_SIZE = 25;
	static constexpr int CELL_SIZE = 8 * CORNER_SIZE;
	static constexpr int WALL_WIDTH = CORNER_SIZE;
	static constexpr int WALL_HEIGHT = 6 * CORNER_SIZE;

	// Enumerated in Clockwise direction
	enum Wall
	{
		// BITS
		W = 0x1,
		N = 0x2,
		E = 0x4,
		S = 0x8,

		// ARRAY INDEX
		WEST = 0,
		NORTH = 1,
		EAST = 2,
		SOUTH = 3,

		MASK = 0xF,
	}; 

	// Yes. This is the Only constructor.
	// Don't even try to make a default one.
	// A cell needs to communicate with the Box2D world
	// So it Must knows what initial position it's in
	explicit Cell(Vector2 initPos);

	void Init() {}

	void Draw();
	
	void SetWalls(int wallBits);

	Vector2 GetSize() const;

private:
	enum Corner
	{
		// If any of the bit is on
		// Then there's a corner
		WN = 0x3,
		NE = 0x6,
		ES = 0xC,
		SW = 0x9,

		// ARRAY INDEX
		CORNER_WN = 0,
		CORNER_NE = 1,
		CORNER_ES = 2,
		CORNER_SW = 3
	};


	void BuildCorners();
	void BuildWalls();

	void DrawCorners();
	void DrawWalls();

private:


	int _wallDirection;
	std::array<std::shared_ptr<SolidObject>, 4> _wallObj;
	std::array<std::shared_ptr<SolidObject>, 4> _cornerObj;
};
