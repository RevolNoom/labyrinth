#pragma once
#ifndef MAZE_LAYOUT_GEN_HPP
#define MAZE_LAYOUT_GEN_HPP

#include "World/Maze/MazeLayout.hpp"
#include <vector>

// Randomly generate some maze layouts
// Should I make it a Singleton?
// I read a few opinions complaining about 
// using too much Singleton could be harmful

class MazeLayoutGenerator
{
public:
	MazeLayoutGenerator(){}

	std::shared_ptr<MazeLayout> Generate(int width, int height);

private:
	using X = int;
	using Y = int;
	using Coordinate = std::pair < X, Y>;

	// Pick Entrances and smash a way in
	std::vector<Coordinate> PickEntrances(int numOfEntrances, std::shared_ptr<MazeLayout> layout);

	void DigTunnels(std::shared_ptr<MazeLayout> layout, std::vector<Coordinate> entrances);

	// Returns the cells:
	// +) In 4 adjacent positions: up left down right
	// +) Not outside the maze
	std::vector<Coordinate> SurroundingCells(std::shared_ptr<MazeLayout> layout, Coordinate cell);
};

#endif /* MAZE_LAYOUT_GEN_HPP */