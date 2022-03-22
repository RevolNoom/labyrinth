#pragma once

#ifndef WORLD_OBJECT_HPP
#define WORLD_OBJECT_HPP

#include "Sprite2D.h"
#include "box2d/b2_body.h"
#include "TopdownWorld.hpp"
#include "box2d/b2_polygon_shape.h"
#include "GameManager/ResourceManagers.h"

// An object that does not move
// Pattern: Adapter? 
class SolidObject: public Sprite2D
{
public:
	SolidObject(std::shared_ptr<Texture> texture, Vector2 pos);

private:
	void RegisterToWorld(Vector2 pos);


	// Rev's Mod
	// Return the Sprite size in... uhhh... pixels?
	// TODO: Need to take into account of m_scale. 
	Vector2	GetSize() const;

	// Can't use shared_ptr here because
	// b2World manage memory for this body already
	// I guess?
	b2Body *_body;
};

#endif /* WORLD_OBJECT_HPP */