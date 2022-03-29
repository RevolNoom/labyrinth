#pragma once

#ifndef UNIT_HPP
#define UNIT_HPP

#include "SpriteAnimation.h"
#include "World/PhysicObject.hpp"

// Unit is our hero, controlled by the player
// Has all the functionalities of SpriteAnim
// Added with input processings
class Unit: public Sprite2D, public PhysicObject
{
public:
	Unit();//std::string animTextrName, Vector2 initPos);

	void Init() {}

	virtual void RegisterToWorld(b2World* world) override;

	virtual void SetSize(GLint width, GLint height) override;

	virtual void Draw() override;
	virtual void Update(float delta) override;

	virtual bool HandleKeyPress(const InputEventKeyPress* ev) override;

	b2Body* body() { return _body; }

private:
	std::shared_ptr<SpriteAnimation> GetCurrentAnim();

private:

	enum ANIM
	{
		RUN = 0,
		IDLE = 1,
		MAX_ANIM,
	};


	int _currentAnim;

	std::vector<std::shared_ptr<SpriteAnimation>> _anims;

	b2Body* _body;
};

#endif /* Unit_HPP */