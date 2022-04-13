#pragma once
#include "World/Maze/Item/Trap.h"
#include "GameObject/Timer.h"
#include "SpriteAnimation.h"
#include "GameScenes/Music.hpp"

// I cannot create an independent Wanderer class
// Because I can't clone SpriteAnimation.
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
	virtual void Draw() override;

	virtual Vector2 GetPosition() const override;
	virtual void SetPosition(Vector2 newPos) override;

	virtual float GetRotation() const override;
	virtual void SetRotation(float angle) override;

	virtual void SetSize(Vector2 size) override;
	virtual Vector2 GetSize() const override;

	void MoveSpriteToBody();

	Vector2 GetVelocity();
	void SetVelocity(Vector2 velo);

private:
	void GoRampant();



protected:
	std::shared_ptr<SpriteAnimation> _anim;
	// The Bat won't go rampant and hit people 
	// while it's still in startup phase
	Timer _startupTimer;

	Vector2 _velo;

	// When the timer goes off, they squeak
	//Timer _squeakTimer;
	//Music _squeak;



private:
	Vector2 _size;
};

