#include "Maze.hpp"

Maze::Maze(int width, int height)
{
	_mzl = MazeLayoutGenerator().Generate(width, height);
}


void Maze::Draw()
{
	_mzl->Draw();
}
