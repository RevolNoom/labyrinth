#pragma once
#include "World/Maze/Item/Trap.h"
#include "GameObject/Timer.h"
#include "SpriteAnimation.h"

class Bat :
    public Trap
{
public:
	Bat();

	virtual void RegisterToWorld(b2World* world) override;

	// Called in b2ContactListener
	virtual void Trigger() override;

	virtual std::shared_ptr<PhysicObject> Clone() override;
	virtual void Update(float delta) override;

private: 
	// The Bat won't go rampant and hit people 
	// while it's still in startup phase
	Timer _startupTimer;

	std::shared_ptr<SpriteAnimation> _batAnim;
};

