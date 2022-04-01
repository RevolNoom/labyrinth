#pragma once
#include "World/Maze/Maze.hpp"
#include "World/PhysicObject.h"
#include <tuple>
#include <map>

class ItemGenerator
{
	using AMOUNT = unsigned int;
	using WEIGHT = unsigned int;

public:
	ItemGenerator();

	// Generate Items
	// Return a MazeLayout with items on it
	// If the maze does not have enough space to hold all items:
	// +) Return empty maze layout (no items generated on it) if
	//		there is not enough space for mandatory items
	// +) Return a maze layout filled with mandatory items, and 
	//	as much random items as it can fit
	MazeLayout<std::shared_ptr<PhysicObject>> Generate(const Maze* mz);

	// Add a new item type to mandatory queue
	// NOTICE: Have you implemented your concrete PhysicObject::Clone()?
	void AddMandatory(std::shared_ptr<PhysicObject> item, AMOUNT amount);

	// Add a new item type to random queue
	// NOTICE: Have you implemented your concrete PhysicObject::Clone()?
	void AddRandom(std::shared_ptr<PhysicObject> item, WEIGHT weight);

	// Get the total amount of Items that will be generated
	int GetItemAmount();

	// Set the number of random items generated
	// after generating Mandatory items
	void SetRandomItemAmount(AMOUNT amount);

private:
	// Generate lower bound of items
	void FillMandatory(MazeLayout<std::shared_ptr<PhysicObject>>& layout);

	// After that, generate item based on "weight"
	// The higher the weight, 
	// the more likely that item is going to be rolled
	void FillRandomly(MazeLayout<std::shared_ptr<PhysicObject>>& layout);

	std::shared_ptr<PhysicObject> RollARandomItem();

private:
	AMOUNT _mandatory;
	std::map<std::shared_ptr<PhysicObject>, AMOUNT> _mandatoryQ;

	WEIGHT _totalWeight;
	AMOUNT _random;
	std::map<std::shared_ptr<PhysicObject>, WEIGHT> _randomQ;
};

