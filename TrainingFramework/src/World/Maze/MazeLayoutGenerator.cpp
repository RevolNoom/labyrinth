#include "MazeLayoutGenerator.h"
#include "World/Maze/Maze.hpp"
#include <queue>
#include <functional>
#include <ctime>
#include <list>

using MLG = MazeLayoutGenerator;


std::shared_ptr<MazeLayout> MLG::Generate(const Maze * mz)
{
	auto newLayout = std::make_shared<MazeLayout>(mz->GetDimensions());
	
	auto entrances = PickEntrances(1, newLayout);

	DigTunnels(newLayout, entrances);

	/*
	std::cout << "Entrance: (" << entrances[0].first << ", " << entrances[0].second << ")\n";
	std::cout << "Generated: ";
	for (int iii = 0; iii < width; ++iii)
		for (int jjj = 0; jjj < height; ++jjj)
			std::cout << newLayout->GetCell({ iii, jjj }).Value() << " ";*/	

	return newLayout;
}

std::vector<MLG::Coordinate> MLG::PickEntrances(int numOfEntrances, std::shared_ptr<MazeLayout> layout)
{
	int width = layout->GetSize().first;
	int height= layout->GetSize().second;

	auto entrances = std::vector<Coordinate>(numOfEntrances, { -1, -1 });

	auto possibleEntrances = std::list<Coordinate>();

	for (int col = 0; col < width; ++col)
		for (int row = 0; row < height; ++row)
			if (row == 0 || col == 0 || row == width - 1 || col == height - 1)
				possibleEntrances.push_back({ col, row });

	for (int iii = 0; iii < numOfEntrances; ++iii)
	{
		auto it = std::next(possibleEntrances.begin(), std::rand() % possibleEntrances.size());// TODO: RANDOM HEREindex);
		entrances[iii] = *it;
		possibleEntrances.erase(it);
	}

	for (auto& e : entrances)
	{
		if (e.first == 0)
			layout->GetCell(e).RemoveWalls(CellProfile::Bit::W);
		else if (e.first == width-1)
			layout->GetCell(e).RemoveWalls(CellProfile::Bit::E);
		else if (e.second == 0)
			layout->GetCell(e).RemoveWalls(CellProfile::Bit::N);
		else
			layout->GetCell(e).RemoveWalls(CellProfile::Bit::S);
	}

	return entrances;
}


void MLG::DigTunnels(std::shared_ptr<MazeLayout> layout, std::vector<Coordinate> entrances)
{
	std::queue<Coordinate> diggingCords;

	std::vector<std::vector<bool>> discovered(layout->GetSize().second, 
											std::vector<bool>(layout->GetSize().first, false));


	
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


void MazeLayoutGenerator::ConnectTwoCells(std::shared_ptr<MazeLayout> layout, Coordinate from, Coordinate to)
{
	auto &cellFrom = layout->GetCell(from);
	auto &cellTo = layout->GetCell(to);

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

std::vector<MLG::Coordinate> MazeLayoutGenerator::SurroundingCells(std::shared_ptr<MazeLayout> layout, Coordinate cell)
{
	Coordinate cells[]{ Coordinate(cell.first - 1, cell.second),
						Coordinate(cell.first, cell.second - 1),
						Coordinate(cell.first, cell.second + 1),
						Coordinate(cell.first + 1, cell.second) };
	
	std::vector<Coordinate> result;
	result.reserve(4);

	for (auto& c : cells)
		if (c.first >= 0 && c.first < layout->GetSize().first &&
			c.second >= 0 && c.second < layout->GetSize().second)
			result.push_back(c);
	return result;
}