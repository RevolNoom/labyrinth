#pragma once

#ifndef THESEUS_HPP
#define THESEUS_HPP

#include "SpriteAnimation.h"
#include "World/SolidObject.hpp"

// Theseus is our hero, controlled by the player
// Has all the functionalities of SpriteAnim
// Added with input processings
class Theseus: public SolidObject
{
public:
	Theseus(std::string animTextrName, Vector2 initPos);

	virtual void Draw() override;
	virtual void Update(float delta) override;


private:
	std::shared_ptr<SpriteAnimation> _anim;
};

#endif /* THESEUS_HPP */