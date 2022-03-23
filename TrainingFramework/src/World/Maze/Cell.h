#pragma once

#include "World/SolidObject.hpp"
#include "ResourceManagers.h"
#include <array>


// Contains information of
// walls and corners wrapping it
class Cell : public Sprite2D
{
public:

	static constexpr int CORNER_SIZE = 2;
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

		ALLWALL = 0xF,
	}; 

	Cell();

	void Init() {}

	void Draw();

	// Return the wall bits of this cell
	int GetWalls();

	// Set the walls into this configuration
	void SetWalls(int wallBits);

	// Add walls in specified positions, if they haven't been there already
	void AddWalls(int wallBits);

	// Remove the walls in specified positions, if they are still there
	void RemoveWalls(int wallBits);


	// The size in... uhhh... pixels (?) of this Cell
	// TODO: I may remove it if I deem it useless
	Vector2 GetSize() const;

	virtual void Set2DPosition(Vector2 pos) override;



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


	// Create objects
	void BuildWalls();
	void BuildCorners();

	void DrawCorners();
	void DrawWalls();

	void SetWallPositions(Vector2 pos);
	void SetCornerPositions(Vector2 pos);
private:


	int _wallDirection;
	std::array<std::shared_ptr<SolidObject>, 4> _wallObj;
	std::array<std::shared_ptr<SolidObject>, 4> _cornerObj;
};
