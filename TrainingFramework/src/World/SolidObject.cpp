#include "SolidObject.h"
#include "ResourceManagers.h"

SolidObject::SolidObject(std::shared_ptr<Texture> texture): _body(nullptr), _texture(texture)
{
	_sprite = std::make_shared<Sprite2D>(ResourceManagers::GetInstance()->GetModel("Sprite2D.nfg"),
										ResourceManagers::GetInstance()->GetShader("TextureShader"),
										texture);
}

void SolidObject::RegisterToWorld(b2World* world)
{
	// yeeted right out of the Documentation

	//std::cout << "Solid Object registering: " << this << "\n";
	// Specify the initial position of the body
	b2BodyDef groundBodyDef;
	groundBodyDef.type = b2BodyType::b2_staticBody;// Solid Objects don't move
	groundBodyDef.enabled = IsEnabled();


	auto phyPos = ToPhysicCoordinate(GetPosition());
	groundBodyDef.position.Set(phyPos.x, phyPos.y);
	groundBodyDef.angle = GetRotation();


	// Create a body from definition. The World will contain it
	_body = world->CreateBody(&groundBodyDef);


	// Create the collision shape for this body
	b2PolygonShape groundBox;
	auto phySize = ToPhysicCoordinate(GetSize()/2);
	groundBox.SetAsBox(phySize.x, phySize.y);


	// Attach the body to the shape
	_body->CreateFixture(&groundBox, 0);
}

void SolidObject::SetEnabled(bool enable)
{
	if (_body)
		_body->SetEnabled(enable);
}


bool SolidObject::IsEnabled() const
{
	if (_body)
		return _body->IsEnabled();
	return true;
}


void SolidObject::SetRotation(float angle)
{
	_sprite->SetRotation(Vector3(0, 0, angle));
	if (_body)
		_body->SetTransform(_body->GetPosition(), angle);
}


float SolidObject::GetRotation() const
{
	return _sprite->GetRotation().z;
}


void SolidObject::SetPosition(Vector2 pos)
{
	_sprite->Set2DPosition(pos.x, pos.y);
	if (_body)
		_body->SetTransform(ToPhysicCoordinate(pos), GetRotation());
}


Vector2 SolidObject::GetPosition() const
{
	auto pos = _sprite->GetPosition();
	return Vector2(pos.x, pos.y);
}


void SolidObject::SetSize(Vector2 size)
{
	_sprite->SetSize(size.x, size.y);
	if (_body)
	{
		auto world = _body->GetWorld();
		world->DestroyBody(_body);
		this->RegisterToWorld(world);
	}
}


Vector2 SolidObject::GetSize() const
{
	return _sprite->GetSize();
}

std::shared_ptr<PhysicObject> SolidObject::Clone()
{
	auto newClone = std::make_shared<SolidObject>(_texture);
	newClone->SetRotation(GetRotation());
	newClone->SetPosition(GetPosition());
	newClone->SetEnabled(IsEnabled());
	newClone->SetSize(GetSize());

	return newClone;
}


void SolidObject::Draw()
{
	_sprite->Draw();
}
