#include "Unit.hpp"
#include "Keyboard.h"

Unit::Unit(): _body(nullptr)
{
	auto model = ResourceManagers::GetInstance()->GetModel("Sprite2D.nfg");
	auto shader = ResourceManagers::GetInstance()->GetShader("Animation");
	auto texture = ResourceManagers::GetInstance()->GetTexture("Rogue.tga");

	_currentAnim = IDLE;

	for (int iii = 0; iii < ANIM::MAX_ANIM; ++iii)
	{
		auto anim = std::make_shared<SpriteAnimation>(model, shader, texture, 6, 3, iii, 0.07);
		_anims.push_back(anim);
	}
}

void Unit::SetSize(Vector2 size)
{
	_size = size;
	for (int iii = 0; iii < ANIM::MAX_ANIM; ++iii)
		_anims[iii]->SetSize(size.x, size.y);
	if (_body)
	{
		auto world = _body->GetWorld();
		world->DestroyBody(_body);
		this->RegisterToWorld(world);
	}
}

Vector2 Unit::GetSize() const
{
	return _size;
}

void Unit::RegisterToWorld(b2World* world)
{
	// Bla bla bla
	// Go to Wall.cpp for more detailed comments
	b2BodyDef groundBodyDef;
	groundBodyDef.type = b2BodyType::b2_dynamicBody;
	auto phyPos = ToPhysicCoordinate(GetPosition());
	groundBodyDef.position.Set(phyPos.x, phyPos.y);
	groundBodyDef.fixedRotation = true;
	groundBodyDef.userData.pointer = reinterpret_cast<uintptr_t>(dynamic_cast<PhysicObject*>(this));
	//groundBodyDef.linearDamping = 0.5;

	_body = world->CreateBody(&groundBodyDef);

	b2PolygonShape groundBox;
	auto phySize = ToPhysicCoordinate(GetSize()/2);
	groundBox.SetAsBox(phySize.x, phySize.y);

	b2FixtureDef fixtureDef;
	fixtureDef.shape = &groundBox;
	fixtureDef.density = 1.0f;
	fixtureDef.friction = 0.3f;

	// Attach the body to the shape
	_body->CreateFixture(&fixtureDef);

}


void Unit::Draw()
{
	GetCurrentAnim()->Draw();
}


void Unit::Update(float delta)
{
	ProcessInput();

	GetCurrentAnim()->Update(delta);

	MoveSpriteToBody();
}


void Unit::SetEnabled(bool enable)
{
	if (_body)
		_body->SetEnabled(enable);
}

bool Unit::IsEnabled() const
{
	if (_body)
		return _body->IsEnabled();
	return false;
}

void Unit::SetRotation(float angle)
{
	_body->SetTransform(ToPhysicCoordinate(GetPosition()), angle);
	for (auto& a : _anims)
		a->SetRotation({ 0, 0, angle });
}

float Unit::GetRotation() const
{
	return GetCurrentAnim()->GetRotation().z;
}


void Unit::SetPosition(Vector2 newPos)
{

	if (_body)
		_body->SetTransform(ToPhysicCoordinate(newPos), GetRotation());

	for (auto& a : _anims)
		a->Set2DPosition(newPos.x, newPos.y);

	_position = newPos;


}

Vector2 Unit::GetPosition() const
{
	return GetCurrentAnim()->Get2DPosition();
}


std::shared_ptr<SpriteAnimation> Unit::GetCurrentAnim() const
{
	return _anims[_currentAnim];
}

void Unit::MoveSpriteToBody()
{
	auto newPos = ToGraphicCoordinate(_body->GetPosition());
	for (auto& a : _anims)
		a->Set2DPosition(newPos.x, newPos.y);
	_position = newPos;
}


void Unit::ProcessInput()
{
	// TODO: Let outsider sets this unit's velocity?
	b2Vec2 maxVelo(ToPhysicCoordinate(Vector2(130, 130)));
	b2Vec2 velo = b2Vec2_zero;

	if (Keyboard::GetInstance()->IsPressing(KEY_MOVE_LEFT))
		velo.x = -maxVelo.x;

	if (Keyboard::GetInstance()->IsPressing(KEY_MOVE_RIGHT))
		velo.x = +maxVelo.x;

	if (Keyboard::GetInstance()->IsPressing(KEY_MOVE_BACKWARD))
		velo.y = +maxVelo.y;

	if (Keyboard::GetInstance()->IsPressing(KEY_MOVE_FORWARD))
		velo.y = -maxVelo.y;

	_body->SetLinearVelocity(velo);

	if (velo.x < 0)
		_currentAnim = ANIM::RUN_LEFT;
	else if (velo != b2Vec2_zero)
		_currentAnim = ANIM::RUN_RIGHT;
	else
		_currentAnim = ANIM::IDLE;
}

std::shared_ptr<PhysicObject> Unit::Clone()
{
	auto newClone = std::make_shared<Unit>();
	newClone->SetRotation(GetRotation());
	newClone->SetPosition(GetPosition());
	newClone->SetEnabled(IsEnabled());
	newClone->SetSize(GetSize());

	return newClone;
}
