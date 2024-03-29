#pragma once

#include "World/SolidObject.h"
#include "ResourceManagers.h"
#include "World/Maze/CellProfile.h"
#include <array>

// Contains information of
// walls and corners wrapping it
class Cell : public PhysicObject
{
public:
	// Very dangerous. 
	// Don't forget to replace it with a properly constructed one
	//Cell(){}

	Cell(std::shared_ptr<Texture> floorTxtr, std::shared_ptr<Texture> verticalWallTxtr);

	virtual void RegisterToWorld(b2World* world) override;

	virtual void SetEnabled(bool enable) override;
	virtual bool IsEnabled() const override;

	virtual void SetPosition(Vector2 pos) override;
	virtual Vector2 GetPosition() const override;

	virtual void SetRotation(float angle) override;
	virtual float GetRotation() const override;

	virtual void SetSize(Vector2 size) override;
	virtual Vector2 GetSize() const override;

	void SetProfile(CellProfile org);
	CellProfile GetProfile();

	virtual std::shared_ptr<PhysicObject> Clone() override;

	virtual void Draw() override;

private:
	enum
	{
		// ARRAY INDEX
		WEST = 0,
		NORTH = 1,
		EAST = 2,
		SOUTH = 3,
	};

	void BuildWalls(std::shared_ptr<Texture> verticalWallTxtr);
	void DrawWalls();

	void SetWallPositions(Vector2 pos);


	Vector2 GetCornerSize();
	Vector2 GetVerticalWallSize();

private:
	std::shared_ptr<Sprite2D> _floor;

	bool _enabled;
	CellProfile _worg;
	std::shared_ptr<Texture> _wallTxtr, _floorTxtr;
	std::array<std::shared_ptr<SolidObject>, 4> _wallObj;
};
