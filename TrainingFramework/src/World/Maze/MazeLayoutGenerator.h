#pragma once
#ifndef MAZE_LAYOUT_GEN_HPP
#define MAZE_LAYOUT_GEN_HPP

#include "World/Maze/MazeLayout.h"
#include <vector>

// Randomly generate some maze layouts
// Should I make it a Singleton?
// I read a few opinions complaining about 
// using too much Singleton could be harmful

class Maze;

class MazeLayoutGenerator: public CSingleton<MazeLayoutGenerator>
{
public:
	MazeLayoutGenerator()
	{
		std::srand(std::time(0));
	}

	MazeLayout<CellProfile> Generate(const Maze* maze);

private:
	// Pick Entrances and smash a way in
	std::vector<Coordinate> PickEntrances(int numOfEntrances, MazeLayout<CellProfile>& layout);

	void DigTunnels(MazeLayout<CellProfile> &layout, std::vector<Coordinate> entrances);

	void ConnectTwoCells(MazeLayout<CellProfile> &layout, Coordinate from, Coordinate to);
	// Returns the cells:
	// +) In 4 adjacent positions: up left down right
	// +) Not outside the maze
	std::vector<Coordinate> SurroundingCells(const MazeLayout<CellProfile> &layout, Coordinate cell);
};

#endif /* MAZE_LAYOUT_GEN_HPP */