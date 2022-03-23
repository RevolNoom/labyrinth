#ifndef MAZE_HPP
#define MAZE_HPP

#include "BaseObject.h"
#include "World/Maze/MazeLayoutGenerator.h"
#include <vector>
#include <memory>


/*
 * How a maze is generated:
 * +) Randomly generate a few layouts
 * +) Randomly pick a few parameter cells for entrances
 * +) Randomly pick one cell for destination (Ariadne)
 * +) Randomly generates Items across the Maze
 */
class Maze: public BaseObject
{
public:
	Maze(int width, int height);

	void Init() override {}

	void Draw() override;

private:
	std::shared_ptr<MazeLayout> _mzl;
};



// class ItemGenerator;

#endif /* MAZE_HPP */
