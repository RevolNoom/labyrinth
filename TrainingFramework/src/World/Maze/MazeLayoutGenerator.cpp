#include "MazeLayoutGenerator.h"
#include "World/Maze/Maze.hpp"
#include <queue>
#include <functional>
#include <ctime>
#include <list>

using MLG = MazeLayoutGenerator;

MazeLayout<CellProfile> MLG::Generate(const Maze * mz)
{
	MazeLayout<CellProfile> newLayout(mz->GetDimensions());
	
	auto entrances = PickStartingPoint(1, newLayout);

	DigTunnels(newLayout, entrances);

	/*
	std::cout << "Entrance: (" << entrances[0].first << ", " << entrances[0].second << ")\n";
	std::cout << "Generated:\n";

	auto it = newLayout.GetIterator();
	while (it.HasNext())
	{
		std::cout << it.Next().Value() << " ";
	}*/
	

	return newLayout;
}

std::vector<Coordinate> MLG::PickStartingPoint(int numOfEntrances, MazeLayout<CellProfile> &layout)
{
	int width = layout.GetSize().first;
	int height= layout.GetSize().second;

	auto entrances = std::vector<Coordinate>(numOfEntrances);

	auto possibleEntrances = std::list<Coordinate>();

	for (int col = 0; col < width; ++col)
		for (int row = 0; row < height; ++row)
			possibleEntrances.push_back({ col, row });

	for (int iii = 0; iii < numOfEntrances; ++iii)
	{
		auto it = std::next(possibleEntrances.begin(), std::rand() % possibleEntrances.size());
		entrances[iii] = *it;
		possibleEntrances.erase(it);
	}

	/* Don't pop a way outside anymore
	*  I made an ExitStair to win the game instead
	* 
	for (auto& e : entrances)
	{
		auto &cell = layout.GetCell(e);
		if (e.first == 0)
			cell.RemoveWalls(CellProfile::Bit::W);
		else if (e.first == width-1)
			cell.RemoveWalls(CellProfile::Bit::E);
		else if (e.second == 0)
			cell.RemoveWalls(CellProfile::Bit::N);
		else
			cell.RemoveWalls(CellProfile::Bit::S);
	}*/

	return entrances;
}


void MLG::DigTunnels(MazeLayout<CellProfile> &layout, std::vector<Coordinate> entrances)
{
	std::queue<Coordinate> diggingCords;

	std::vector<std::vector<bool>> discovered(layout.GetSize().second, 
											std::vector<bool>(layout.GetSize().first, false));


	
	for (auto& e : entrances)
	{
		discovered[e.second][e.first] = true;
		for (auto& cell : SurroundingCells(layout, e))
			diggingCords.push(cell);
	}


	while (!diggingCords.empty())
	{
		auto undigged = diggingCords.front();
		diggingCords.pop(); 

		if (discovered[undigged.second][undigged.first])
			continue; 
		discovered[undigged.second][undigged.first] = true;

		auto surrounding = SurroundingCells(layout, undigged);

		for (auto& e : surrounding)
			diggingCords.push(e);

		// Connect to random discovered cell
		std::vector<Coordinate> randomDiscovered;

		for (auto& cell : surrounding)
			if (discovered[cell.second][cell.first])
				randomDiscovered.push_back(cell);

		if (!randomDiscovered.empty())
			ConnectTwoCells(layout, undigged, randomDiscovered[std::rand() % randomDiscovered.size()]);
	}

}


void MazeLayoutGenerator::ConnectTwoCells(MazeLayout<CellProfile> &layout, Coordinate from, Coordinate to)
{
	auto &cellFrom = layout.GetCell(from);
	auto &cellTo = layout.GetCell(to);

	using CONDITION = int;
	using BREAK_WALL_FROM = CellProfile::Bit;
	using BREAK_WALL_TO = CellProfile::Bit;

	std::tuple<CONDITION, BREAK_WALL_FROM, BREAK_WALL_TO> tup[]
	{ 
		{from.first - to.first, CellProfile::Bit::W, CellProfile::Bit::E},	// [TO] [FROM]

		{from.second - to.second, CellProfile::Bit::N, CellProfile::Bit::S},//  [TO]
																			// [FROM]

		{to.second - from.second, CellProfile::Bit::S, CellProfile::Bit::N},// [FROM]
																			//  [TO]

		{to.first - from.first, CellProfile::Bit::E, CellProfile::Bit::W},  // [FROM] [TO]
	};

	for (auto& t : tup)
	{
		if (std::get<0>(t) == 1)
		{
			cellFrom.RemoveWalls(std::get<1>(t));
			cellTo.RemoveWalls(std::get<2>(t));
		}
	}
}

std::vector<Coordinate> MazeLayoutGenerator::SurroundingCells(const MazeLayout<CellProfile> &layout, Coordinate cell)
{
	Coordinate cells[]{ Coordinate(cell.first - 1, cell.second),
						Coordinate(cell.first, cell.second - 1),
						Coordinate(cell.first, cell.second + 1),
						Coordinate(cell.first + 1, cell.second) };
	
	std::vector<Coordinate> result;
	result.reserve(4);

	for (auto& c : cells)
		if (c.first >= 0 && c.first < layout.GetSize().first &&
			c.second >= 0 && c.second < layout.GetSize().second)
			result.push_back(c);
	return result;
}