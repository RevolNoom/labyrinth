#include "Bat.h"

Bat::Bat(): 
	Trap(nullptr), 
	_startupTimer(2)
{
	_batAnim = std::make_shared<SpriteAnimation>(
					ResourceManagers::GetInstance()->GetModel("Sprite2d.nfg"),
					ResourceManagers::GetInstance()->GetShader("TextureShader"),
					ResourceManagers::GetInstance()->GetTexture("Bat.tga"),
					2, 1, 0, 0.1);
	SetEnabled(false);
}

void Bat::RegisterToWorld(b2World* world)
{
	b2BodyDef body;
	body.type = b2BodyType::b2_kinematicBody;	// difference from Trap::RegisterToWorld()
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

	//SetEnabled(true);	// difference from Trap::RegisterToWorld()
}


void Bat::Trigger()
{
}


std::shared_ptr<PhysicObject> Bat::Clone()
{
	auto newClone = std::make_shared<Bat>();

	newClone->SetRotation(GetRotation());
	newClone->SetPosition(GetPosition());
	newClone->SetEnabled(IsEnabled());
	newClone->SetSize(GetSize());

	return newClone;
}


void Bat::Update(float delta)
{
	_startupTimer.Update(delta);
	if (_startupTimer.TimeOut())
	{
		// TODO
	}
}
