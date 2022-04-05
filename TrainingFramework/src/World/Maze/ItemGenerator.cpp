#include "ItemGenerator.h"
#include <algorithm>

ItemGenerator::ItemGenerator(): _mandatory(0), _random(0), _totalWeight(0)
{
}

MazeLayout<std::shared_ptr<PhysicObject>> ItemGenerator::Generate(const Maze* mz)
{
	auto newLayout = MazeLayout<std::shared_ptr<PhysicObject>>(mz->GetDimensions());

	if (_mandatory > newLayout.GetCellAmount())
		return newLayout;

	FillMandatory(newLayout);
	FillRandomly(newLayout);
	newLayout.Shuffle();

	return newLayout;
}

void ItemGenerator::AddMandatory(std::shared_ptr<PhysicObject> item, AMOUNT amount)
{
	_mandatory += amount;
	_mandatoryQ[item] = amount;
}

void ItemGenerator::AddRandom(std::shared_ptr<PhysicObject> item, WEIGHT weight)
{
	_totalWeight += weight;
	_randomQ[item] = weight;
}

int ItemGenerator::GetItemAmount()
{
	return _mandatory + _random;
}

void ItemGenerator::SetRandomItemAmount(AMOUNT amount)
{
	_random = amount;
}

void ItemGenerator::FillMandatory(MazeLayout<std::shared_ptr<PhysicObject>>& layout)
{
	Coordinate currentPos{ 0, 0 };

	for (auto it = _mandatoryQ.begin(); it!=_mandatoryQ.end(); ++it)
		for (int iii = 0; iii < it->second; ++iii)
		{
			layout.GetCell(currentPos) = it->first->Clone();

			++currentPos.first;
			if (currentPos.first >= layout.GetSize().first)
			{
				++currentPos.second;
				currentPos.first = 0;
			}
		}
}

void ItemGenerator::FillRandomly(MazeLayout<std::shared_ptr<PhysicObject>>& layout)
{
	Coordinate currentPos{layout.GetSize().first - 1, layout.GetSize().second - 1};

	for (int iii = 0; 
		iii < _random && 
		iii < layout.GetCellAmount() &&
		layout.GetCell(currentPos) == nullptr;
		++iii)
	{
		layout.GetCell(currentPos) = RollARandomItem();

		--currentPos.first;
		if (currentPos.first < 0)
		{
			--currentPos.second;
			currentPos.first = layout.GetSize().first - 1;
		}
	}
}

std::shared_ptr<PhysicObject> ItemGenerator::RollARandomItem()
{
	// Roll a random amount of fuel
	int fuel = std::rand() % _totalWeight;

	// And then see how far we can go.
	// Get the item we see when we stop
	for (auto it = _randomQ.begin(); it != _randomQ.end(); ++it)
	{
		fuel -= it->second;
		if (fuel <= 0)
			return it->first->Clone();
	}

	// This case probably won't happen
	// But in case we stray too far, get the last item.
	return _randomQ.cbegin()->first->Clone();
}