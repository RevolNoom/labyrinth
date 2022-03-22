#ifndef MAZE_LAYOUT_HPP
#define MAZE_LAYOUT_HPP

#include <vector>
#include "Cell.h"

//Contains the layout of cells in a Maze
class MazeLayout
{
public:

	// Create a Maze of width x height
	// Width, height > 0
	MazeLayout(Vector2 initPos, int width, int height);

	void Draw();


	// Return the cell on plane Oxy
	// with O at the Top Left corner
	std::shared_ptr<Cell> GetCell(int x, int y);


	// Return <width, height>
	std::pair<int, int> GetSize() const;

private:
	int _width, _height;
	std::vector<std::shared_ptr<Cell>> _layout;
};

#endif /* MAZE_LAYOUT_HPP */
