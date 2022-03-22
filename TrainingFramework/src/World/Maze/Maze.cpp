#include "Maze.hpp"

Maze::Maze(Vector2 initPos, int width, int height): _mzl(initPos, width, height)
{
}


void Maze::Draw()
{
	_mzl.Draw();
}
