#ifndef MAZE_LAYOUT_HPP
#define MAZE_LAYOUT_HPP

#include "Cell.h"
#include <vector>

//Contains the layout of cells in a Maze
class MazeLayout
{
public:
	using Coordinate = std::pair<int, int>;

	// Create a Maze of width x height
	// Width, height > 0
	MazeLayout(int width, int height);
	MazeLayout(Coordinate size);

	//void Draw();

	// Return the wall organization of this cell
	// with O at the Top Left corner
	CellProfile& GetCell(Coordinate c);

	// Return <width, height>
	Coordinate GetSize() const;

	// Set the position of the layout's Top Left corner
	// void Set2DPosition(Vector2 topLeftCornerPos);

private:

	Vector2 _pos;

	Coordinate _size;
	std::vector<CellProfile> _layout;
};

#endif /* MAZE_LAYOUT_HPP */
