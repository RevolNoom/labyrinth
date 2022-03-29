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
class Maze: public Sprite2D, public PhysicObject
{
public:
	Maze(int width, int height);

	virtual void RegisterToWorld(b2World* world);

	void SwapLayout(std::shared_ptr<MazeLayout> l);

	void Init() override {}

	void Draw() override;

	virtual void SetEnable(bool enable) override;
	virtual void Set2DPosition(Vector2 newPos) override;

	// TODO: Put this back to private after debugging
	Cell& GetCell(int row, int col);
private:

	MazeLayout::Coordinate _size;
	std::vector<Cell> _cells;
};



// class ItemGenerator;

#endif /* MAZE_HPP */
