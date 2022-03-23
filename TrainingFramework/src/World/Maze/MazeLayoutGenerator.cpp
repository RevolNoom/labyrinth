#include "MazeLayoutGenerator.h"
#include <queue>
#include <functional>
#include <ctime>

using MLG = MazeLayoutGenerator;

std::shared_ptr<MazeLayout> MLG::Generate(int width, int height)
{
	std::srand(std::time(nullptr));

	auto newLayout = std::make_shared<MazeLayout>(width, height);
	
	auto entrances = PickEntrances(1, newLayout);

	DigTunnels(newLayout, entrances);

	return newLayout;
}

std::vector<MLG::Coordinate> MLG::PickEntrances(int numOfEntrances, std::shared_ptr<MazeLayout> layout)
{
	int width = layout->GetSize().first;
	int height= layout->GetSize().second;

	auto entrances = std::vector<Coordinate>(numOfEntrances, { -1, -1 });

	std::array<Coordinate, 4> corners{			std::pair(0, 0),
																{0, height - 1}, 
														{width - 1, height - 1}, 
														{width - 1, 0} };

	for (auto& e : entrances)
	{
		constexpr bool A_New_Entrance_Hasnt_Been_Picked = true;
		while (A_New_Entrance_Hasnt_Been_Picked)
		{
			int x, y;

			// Randomly pick an entrance direction
			constexpr int LEFT = 0;
			constexpr int RIGHT = 1;
			constexpr int TOP = 2;
			constexpr int BOTTOM = 3;

			int random = std::rand();
			switch (std::rand() % 4)
			{
			case LEFT:
				x = 0;
				y = random % height;
				layout->GetCell(x, y)->RemoveWalls(Cell::Wall::W);
				break;

			case RIGHT:
				x = width - 1;
				y = random % height;
				layout->GetCell(x, y)->RemoveWalls(Cell::Wall::E);
				break;

			case TOP:
				y = 0;
				x = random % width;
				layout->GetCell(x, y)->RemoveWalls(Cell::Wall::N);
				break;

			case BOTTOM:// fallthrough
				y = height - 1;
				x = random % width;
				layout->GetCell(x, y)->RemoveWalls(Cell::Wall::S);
				break;
			}


			bool alreadyPicked = std::find(entrances.begin(), entrances.end(), std::pair(x, y)) != entrances.end();

			bool isAtCorner = std::find(corners.begin(), corners.end(), std::pair(x, y)) != corners.end();

			if (alreadyPicked || isAtCorner)
				continue;

			e = std::pair(x, y);
			break;
		}	
	}
	return entrances;
}


void MLG::DigTunnels(std::shared_ptr<MazeLayout> layout, std::vector<Coordinate> entrances)
{
	std::queue<MLG::Coordinate> diggingCords;

	auto pushToQueue = [&](std::vector<MLG::Coordinate>& newCells)
	{
		for (auto& e : newCells)
			diggingCords.push(e);
	};

	auto isDiscovered = [&](MLG::Coordinate cell) {
		return layout->GetCell(cell.first, cell.second)->GetWalls() != Cell::ALLWALL;
	};

	auto connect = [&](MLG::Coordinate cellFrom, MLG::Coordinate cellTo)
	{
		// To From
		if (cellFrom.first - cellTo.first == 1)
		{
			layout->GetCell(cellFrom.first, cellFrom.second)->RemoveWalls(Cell::Wall::W);
			layout->GetCell(cellTo.first, cellTo.second)->RemoveWalls(Cell::Wall::E);
		}

		// To  
		//From
		else if (cellFrom.second - cellTo.second == 1)
		{
			layout->GetCell(cellFrom.first, cellFrom.second)->RemoveWalls(Cell::Wall::N);
			layout->GetCell(cellTo.first, cellTo.second)->RemoveWalls(Cell::Wall::S);
		}

		//From
		// To  
		else if (cellFrom.second - cellTo.second == -1)
		{
			layout->GetCell(cellFrom.first, cellFrom.second)->RemoveWalls(Cell::Wall::S);
			layout->GetCell(cellTo.first, cellTo.second)->RemoveWalls(Cell::Wall::N);
		}

		// From To		& all other wrong cases
		else
		{
			layout->GetCell(cellFrom.first, cellFrom.second)->RemoveWalls(Cell::Wall::E);
			layout->GetCell(cellTo.first, cellTo.second)->RemoveWalls(Cell::Wall::W);
		}
	};

	auto connectToRandomDiscovered = [&](MLG::Coordinate cell) 
	{
		auto surrounding = SurroundingCells(layout, cell);
		std::vector<MLG::Coordinate> discovered;

		for (auto &cell: surrounding)
			if (isDiscovered(cell))
				discovered.push_back(cell);
		
		connect(cell, discovered[std::rand() % discovered.size()]);
	};


	for (auto &e: entrances)
		pushToQueue(SurroundingCells(layout, e));

	while (!diggingCords.empty())
	{
		auto undigged = diggingCords.front();
		diggingCords.pop(); 

		if (isDiscovered(undigged))
			continue;


		auto surrounding = SurroundingCells(layout, undigged);
		pushToQueue(surrounding);
		

		connectToRandomDiscovered(undigged);
	}

}


std::vector<MLG::Coordinate> MazeLayoutGenerator::SurroundingCells(std::shared_ptr<MazeLayout> layout, Coordinate cell)
{
	Coordinate cells[]{ std::pair(cell.first - 1, cell.second),
					std::pair(cell.first, cell.second - 1),
					std::pair(cell.first, cell.second + 1),
					std::pair(cell.first + 1, cell.second) };
	
	std::vector<Coordinate> result;

	for (auto& c : cells)
		if (c.first >= 0 && c.first < layout->GetSize().first &&
			c.second >= 0 && c.second < layout->GetSize().second)
			result.push_back(c);
	return result;
}