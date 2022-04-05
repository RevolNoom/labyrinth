#ifndef MAZE_HPP
#define MAZE_HPP

#include "World/PhysicObject.h"
#include "World/Maze/MazeLayoutGenerator.h"
#include <vector>
#include <memory>


class Maze: public PhysicObject
{
public:
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

	void SetLayout(const MazeLayout<CellProfile> &l);
	const MazeLayout<CellProfile> &GetLayout() const;

	Coordinate GetDimensions() const;

	virtual void Update(float delta) override;

	virtual std::shared_ptr<PhysicObject> Clone() override;

private:
	// Maybe I should expose Maze's Item Generator
	// To be modified openly?
	void GenerateItems();

private:

	MazeLayout<std::shared_ptr<Cell>> _cells;
	MazeLayout<CellProfile> _currentLayout;
	MazeLayout<std::shared_ptr<PhysicObject>> _itemLayout;

	Coordinate _size;

	Vector2 _center;

	std::shared_ptr<Texture> _wallTxtr, _floorTxtr;
};

// class ItemGenerator;

#endif /* MAZE_HPP */
