#ifndef MAZE_HPP
#define MAZE_HPP

#include "World/PhysicObject.h"
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
class Maze: public PhysicObject
{
public:
	using Coordinate = MazeLayout::Coordinate;

	// TODO
	Maze(int width, int height);
	Maze(Coordinate size);

	virtual void RegisterToWorld(b2World* world) override;

	virtual void SetEnabled(bool enable) override;
	virtual bool IsEnabled() const override;

	virtual void SetRotation(float angle) override;
	virtual float GetRotation() const override;

	virtual void SetPosition(Vector2 center) override;
	virtual Vector2 GetPosition() const override;

	// An expensive operation
	// Because box2d does not support scaling.
	// We have to destroy and re-create physic bodies.
	// Don't do this often!
	virtual void SetSize(Vector2 size) override;
	virtual Vector2 GetSize() const override;

	virtual void SetCellSize(Vector2 size);
	virtual Vector2 GetCellSize() const;

	virtual void Draw() override;
	void SetLayout(std::shared_ptr<MazeLayout> l);
	std::shared_ptr<MazeLayout> GetLayout() const;

	const Cell& GetCell(Coordinate c) const;
	Coordinate GetDimensions() const;

private:
	Cell& GetCell(Coordinate c);

	std::shared_ptr<MazeLayout> _currentLayout;
	std::vector<Cell> _cells;
	Coordinate _size;

	Vector2 _center;
};



// class ItemGenerator;

#endif /* MAZE_HPP */
