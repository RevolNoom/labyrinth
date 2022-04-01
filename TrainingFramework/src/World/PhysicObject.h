#pragma once

// Probably it's for the best that 
// this class remains an interface

#ifndef PHYSIC_OBJECT_H
#define PHYSIC_OBJECT_H

#include "box2d/b2_body.h"
#include "box2d/b2_world.h"
#include "box2d/b2_fixture.h"
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

	virtual void SetEnabled(bool enable) = 0;
	virtual bool IsEnabled() const = 0;

	virtual void SetPosition(Vector2 pos) = 0;
	virtual Vector2 GetPosition() const = 0;

	virtual void SetRotation(float angle) = 0;
	virtual float GetRotation() const = 0;

	virtual void SetSize(Vector2 size) = 0;
	virtual Vector2 GetSize() const = 0;

	virtual void Update(float delta) {}
	virtual void Draw() = 0;

	virtual std::shared_ptr<PhysicObject> Clone() = 0;

	virtual bool HandleKeyPress(const InputEventKeyPress* ev) { return false; }
	virtual bool HandleMouseClick(const InputEventMouseClick* ev) { return false; }
	virtual bool HandleMouseMotion(const InputEventMouseMotion* ev) { return false; }

protected:

	static b2Vec2 ToPhysicCoordinate(Vector2 graphicalWorldCoord);
	static b2Vec2 ToPhysicCoordinate(Vector3 graphicalWorldCoord);
	static Vector2 ToGraphicCoordinate(b2Vec2 physicalWorldCoord);
	static constexpr float GRAPHIC_TO_PHYSIC_SIZE_RATIO = 100;
};



#endif /* PHYSIC_OBJECT_HPP */