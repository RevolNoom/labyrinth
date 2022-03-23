#ifndef MAZE_LAYOUT_HPP
#define MAZE_LAYOUT_HPP

#include "Cell.h"
#include <vector>

//Contains the layout of cells in a Maze
class MazeLayout
{
public:

	// Create a Maze of width x height
	// Width, height > 0
	MazeLayout(int width, int height, Vector2 initPos = Vector2(0, 0));

	void Draw();

	// Return the cell on plane Oxy
	// with O at the Top Left corner
	std::shared_ptr<Cell> GetCell(int x, int y);

	// Return <width, height>
	std::pair<int, int> GetSize() const;

	// Set the position of the layout's Top Left corner
	void Set2DPosition(Vector2 topLeftCornerPos);

private:

	Vector2 _pos;

	int _width, _height;
	std::vector<std::shared_ptr<Cell>> _layout;
};

#endif /* MAZE_LAYOUT_HPP */
