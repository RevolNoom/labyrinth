#include "World/Maze/Item/Trap.h"

Trap::Trap(std::shared_ptr<Texture> txtr) :
	SolidObject(txtr)
{
}

void Trap::RegisterToWorld(b2World* world)
{
	b2BodyDef body;
	body.type = b2BodyType::b2_staticBody;
	body.position = ToPhysicCoordinate(GetPosition());
	// Let this body contains its parent
	body.userData.pointer = reinterpret_cast<uintptr_t>(dynamic_cast<PhysicObject*>(this));

	_body = world->CreateBody(&body);

	b2PolygonShape shape;
	auto size = ToPhysicCoordinate(GetSize() / 2);
	shape.SetAsBox(size.x, size.y);

	b2FixtureDef fdef;
	fdef.isSensor = true;
	fdef.density = 0;
	fdef.friction = 0;
	fdef.shape = &shape;


	_body->CreateFixture(&fdef);

	SetEnabled(true);
}