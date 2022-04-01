#pragma once

#ifndef SOLID_OBJECT_H
#define SOLID_OBJECT_H

#include "World/PhysicObject.h"

class SolidObject : public PhysicObject
{
public:
	SolidObject(std::shared_ptr<Texture> texture);

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

	virtual std::shared_ptr<PhysicObject> Clone() override;

	virtual void Draw() override;

protected:
	std::shared_ptr<Sprite2D> _sprite;
	std::shared_ptr<Texture> _texture;
	b2Body* _body;
};


#endif  // SOLID_OBJECT_H