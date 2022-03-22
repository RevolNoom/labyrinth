#ifndef MAZE_HPP
#define MAZE_HPP

#include <vector>
#include <memory>
#include "BaseObject.h"
#include "MazeLayout.hpp"


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
	Maze(Vector2 initPos, int width, int height);

	void Init() override {}

	void Draw() override;

private:
	MazeLayout _mzl;
};



// How a Maze layout is created:
// +) Create an entrance
// +) Apply BFS algorithm:
// 	-) Find all undiscovered cells next to discovered ones
// 	-) Pick one undiscovered cell randomly
// 	-) Connect that undiscovered cell to a random adjacent discovered one
// 	-) Mark that cell as discovered
// class LayoutGenerator;

// class ItemGenerator;

#endif /* MAZE_HPP */
