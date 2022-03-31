#ifndef TRANS_PLAT_FORM_H
#define TRANS_PLAT_FORM_H


#include "World/Maze/Maze.hpp"
#include "World/SolidObject.h"
#include "box2d/b2_world_callbacks.h"


class Trap :
	public SolidObject
{
public:
	Trap(std::shared_ptr<Texture> txtr): SolidObject(txtr)
	{}

	// Called in b2ContactListener
	virtual void Trigger() = 0;
};


class TransPlatform :
	public Trap
{
public:
	TransPlatform(std::shared_ptr<Maze> targetMaze, float cooldownTime);
	void TargetMaze(std::shared_ptr<Maze> targetMaze);
	void SetCooldownTimer(float cooldownTime);

	virtual void RegisterToWorld(b2World* world) override;
	virtual void SetEnabled(bool enable) override;

	void Trigger();

	virtual void Update(float delta) override;

private:
	std::weak_ptr<Maze> _targetMaze;

	std::shared_ptr<MazeLayout> _cacheLayout;

	// TODO: Refactor into Timer class?
	float _maxTime;
	float _remainingTime;

	b2Body* _body;
}; 

#endif /* TRANS_PLAT_FORM_H */