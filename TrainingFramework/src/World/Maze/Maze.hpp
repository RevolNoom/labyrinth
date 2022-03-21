#ifndef MAZE_HPP
#define MAZE_HPP

#include <vector>
#include <memory>

/*
 * How a maze is generated:
 * +) Randomly generate a few layouts
 * +) Randomly pick a few parameter cells for entrances
 * +) Randomly pick one cell for destination (Ariadne)
 * +) Randomly generates Items across the Maze
 */
class Maze
{
};




// Defines the routes in a Maze
// How a Maze layout is created:
// +) Create an entrance
// +) Apply BFS algorithm:
// 	-) Find all undiscovered cells next to discovered ones
// 	-) Pick one undiscovered cell randomly
// 	-) Connect that undiscovered cell to a random adjacent discovered one
// 	-) Mark that cell as discovered
class MazeLayout
{
public:

private:
//	std::vector<std::vector<std::shared_ptr<Site>>> _layout;
};

// class LayoutGenerator;

// class ItemGenerator;

#endif /* MAZE_HPP */
