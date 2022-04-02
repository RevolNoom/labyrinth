#ifndef TRANS_PLAT_FORM_H
#define TRANS_PLAT_FORM_H


#include "World/Maze/Maze.hpp"
#include "World/Maze/Item/Trap.h"
#include "box2d/b2_world_callbacks.h"


class TransPlatform :
	public Trap
{
public:
	TransPlatform(Maze *targetMaze, float cooldownTime);
	void TargetMaze(Maze *targetMaze);
	void SetCooldownTimer(float cooldownTime);

	virtual void SetEnabled(bool enable) override;

	virtual void Trigger() override;
	virtual void Update(float delta) override;
	virtual std::shared_ptr<PhysicObject> Clone() override;

private:
	Maze *_targetMaze;

	MazeLayout<CellProfile> _cacheLayout;

	// TODO: Refactor into Timer class?
	float _maxTime;
	float _remainingTime;

	b2Body* _body;
}; 

#endif /* TRANS_PLAT_FORM_H */