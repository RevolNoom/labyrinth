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
	MazeLayout(int width, int height);//, Vector2 initPos = Vector2(0, 0));

	//void Draw();

	// Return the wall organization of this cell
	// with O at the Top Left corner
	WallOrganization& GetCell(int x, int y);

	// Return <width, height>
	Coordinate GetSize() const;

	// Set the position of the layout's Top Left corner
	// void Set2DPosition(Vector2 topLeftCornerPos);

private:

	Vector2 _pos;

	Coordinate _size;
	std::vector<WallOrganization> _layout;
};

#endif /* MAZE_LAYOUT_HPP */
