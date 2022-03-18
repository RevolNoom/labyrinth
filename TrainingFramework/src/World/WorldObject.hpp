#pragma once

#ifndef WORLD_OBJECT_HPP
#define WORLD_OBJECT_HPP

#include "Sprite2D.h"
#include "box2d/b2_body.h"
#include "TopdownWorld.hpp"
#include "box2d/b2_polygon_shape.h"

// An object that exists in a game world.
// Tie Sprite and collision detection together
// Pattern: Adapter? 
class WorldObject: public Sprite2D
{
public:
	WorldObject(std::shared_ptr<Texture> texture):
		Sprite2D(ResourceManagers::GetInstance()->GetModel("Sprite2D.nfg"),
				ResourceManagers::GetInstance()->GetShader("TextureShader"),
				texture)
	{
		RegisterToWorld();
	}

private:
	void RegisterToWorld()
	{
		// yeeted right out of the Documentation
		
		// TODO: Maybe I miscalculated. Each scene
		// should have an independent World
		
		// Specify the initial position of the body
		b2BodyDef groundBodyDef;
		// TODO: Set the position according to sprite 
		groundBodyDef.position.Set(0, 0);

		// Create a body from definition. The World will contain it
		_body = TopdownWorld::get_instance()->CreateBody(&groundBodyDef);

		// Create the collision shape for this body
		// TODO: Set the Size of this body according to the sprite
		b2PolygonShape groundBox;
		groundBox.SetAsBox(50.0f, 10.0f);

		// Attach the body to the shape
		_body->CreateFixture(&groundBox, 0.0f);

		// TODO: A conversion from pixel to meter is needed.
	}

	std::shared_ptr<Sprite2D> _sprite;

	// Can't use shared_ptr here because
	// b2World manage memory for this body already
	// I guess?
	b2Body *_body;
};

#endif /* WORLD_OBJECT_HPP */