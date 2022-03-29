#pragma once

// Probably it's for the best that 
// this class remains an interface

#ifndef PHYSIC_OBJECT_HPP
#define PHYSIC_OBJECT_HPP

#include "box2d/b2_body.h"
#include "TopdownWorld.hpp"
#include "box2d/b2_polygon_shape.h"
#include "GameManager/ResourceManagers.h"

 

// Objects that do physic collisions 
// and Graphical <-> Physic World size conversion
// Pattern: Adapter
class PhysicObject
{
public:


	// One PhysicObject may have many children b2Body
	// Each class will register all of them to this World
	// This is second-step in initialization.
	// Create objects and arrange them in Graphical World first
	// This will set objects up in Physic World
	virtual void RegisterToWorld(b2World* world) = 0;

	// OVERRIDE ME
	virtual void SetVelocity(Vector2 velocity) {};

	b2Vec2 ToPhysicCoordinate(Vector2 graphicalWorldCoord);
	b2Vec2 ToPhysicCoordinate(Vector3 graphicalWorldCoord);
	Vector2 ToGraphicCoordinate(b2Vec2 physicalWorldCoord);

private:

	static constexpr float GRAPHIC_TO_PHYSIC_SIZE_RATIO = 100;


	// virtual void GetPosition() = 0

	// void SetEnable?

	// Rev's Mod
	// Return the Sprite size in... uhhh... pixels?
	// TODO: Need to take into account of m_scale. 
	//Vector2	GetSize() const;

};

#endif /* PHYSIC_OBJECT_HPP */