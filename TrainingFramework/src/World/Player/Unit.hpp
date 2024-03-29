#pragma once

#ifndef UNIT_HPP
#define UNIT_HPP

#include "SpriteAnimation.h"
#include "World/PhysicObject.h"

// Unit is our hero, controlled by the player
// Has all the functionalities of SpriteAnim
// Added with input processings
class Unit: public PhysicObject
{
public:
	Unit();

	virtual void RegisterToWorld(b2World* world) override;

	virtual void SetEnabled(bool enable) override;
	virtual bool IsEnabled() const override;

	virtual void SetRotation(float angle) override;
	virtual float GetRotation() const override;

	virtual void SetPosition(Vector2 pos) override;
	virtual Vector2 GetPosition() const override;

	// An expensive operation
	// Because box2d does not support scaling.
	// We have to destroy and re-create physic body.
	// Don't do this often!
	virtual void SetSize(Vector2 size) override;
	virtual Vector2 GetSize() const override;

	virtual void Update(float delta) override;
	virtual void Draw() override;


	//TODO: Does not clone velocity, animation. 
	virtual std::shared_ptr<PhysicObject> Clone() override;

	Vector2 GetMaxVelocity();
	void SetMaxVelocity(Vector2 velo);
private:
	void ProcessInput();

	std::shared_ptr<SpriteAnimation> GetCurrentAnim() const;

	void MoveSpriteToBody();

	// TODO: Refactoring functions with Bat needed?
	Vector2 GetVelocity();
	void SetVelocity(Vector2 velo);

private:

	enum ANIM
	{
		RUN_LEFT = 0,
		RUN_RIGHT = 1,
		IDLE = 2,
		MAX_ANIM,
	};


	int _currentAnim;

	std::vector<std::shared_ptr<SpriteAnimation>> _anims;

	b2Body* _body;

	b2Vec2 _force;

	Vector2 _size;

	Vector2 _maxVelo;
	Vector2 _velo;

	// Because, obviously, I can't put my faith
	// into SpriteAnimation Get2DPosition()
	// Set2DPosition still work fine though. 
	// Thank the stars!
	Vector2 _position;
};

#endif /* Unit_HPP */