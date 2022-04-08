#include "Bat.h"
#include <algorithm>
#include "GameScenes/ScenePlayLogicServer.h"
#include "ServiceLocator.h"

Bat::Bat() :
	Trap(nullptr),
	_startupTimer(2),
	_squeakTimer(5 + (std::rand() % 5000) / 1000.0),
	_squeak(Music("snd_bat.wav"))
{
	_anim = std::make_shared<SpriteAnimation>(
					ResourceManagers::GetInstance()->GetModel("Sprite2d.nfg"),
					ResourceManagers::GetInstance()->GetShader("Animation"),
					ResourceManagers::GetInstance()->GetTexture("bat.tga"),
					2, 1, 0, 0.1);
	SetEnabled(false);

	_startupTimer.Start();
}

void Bat::RegisterToWorld(b2World* world)
{
	b2BodyDef body;
	body.type = b2BodyType::b2_kinematicBody;	// difference from Trap::RegisterToWorld()
	body.position = ToPhysicCoordinate(GetPosition());
	body.enabled = false; // I want an inactive duration during which it does not kill the player

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

	_squeakTimer.Start();
}


void Bat::Trigger()
{
	// No, the bat does not die. The player does.
	ScenePlayLogicServer::GetInstance()->Die();
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
	_anim->Update(delta);

	if (_startupTimer.TimeOut() )
	{
		if (!IsEnabled())
			GoRampant();
	}
	else 
		_startupTimer.Update(delta);

	if (_body)
	{
		auto velo = _body->GetLinearVelocity();
		if ((GetPosition().x < 0 && velo.x < 0) ||
			(GetPosition().x > Globals::screenWidth && velo.x > 0))
		{
			velo.x = -velo.x;
		}
		if ((GetPosition().y < 0 && velo.y < 0) || 
			(GetPosition().y > Globals::screenHeight && velo.y > 0))
		{
			velo.y = -velo.y;
		}
		_body->SetLinearVelocity(velo);

		MoveSpriteToBody();

		_squeakTimer.Update(delta);
		if (_squeakTimer.TimeOut())
		{
			_squeakTimer.Reset();
			_squeakTimer.Start();
			ServiceLocator::GetInstance()->GetSoundEffectAudioPlayer()->Play(_squeak);
		}
		//std::cout << "Bat at " << GetPosition().x << ", " << GetPosition().y << "\n";
	}
}


void Bat::MoveSpriteToBody()
{
	auto newPos = ToGraphicCoordinate(_body->GetPosition());
	_anim->Set2DPosition(newPos.x, newPos.y);
}


void Bat::Draw()
{
	_anim->Draw();
}

Vector2 Bat::GetPosition() const
{
	return _anim->Get2DPosition();
}

void Bat::SetPosition(Vector2 newPos)
{
	_anim->Set2DPosition(newPos.x, newPos.y);
	if (_body)
		_body->SetTransform(ToPhysicCoordinate(newPos), GetRotation());
}

float Bat::GetRotation() const
{
	return _anim->GetRotation().z;
}

void Bat::SetRotation(float angle)
{
	_anim->SetRotation(Vector3(0, 0, angle));
	if (_body)
		_body->SetTransform(_body->GetPosition(), angle);
}

void Bat::SetSize(Vector2 size)
{
	_size = size;
	_anim->SetSize(size.x, size.y);
	if (_body)
	{
		auto world = _body->GetWorld();
		world->DestroyBody(_body);
		RegisterToWorld(world);
	}
}

Vector2 Bat::GetSize() const
{
	return _size;
}

void Bat::GoRampant()
{
	SetEnabled(true);
	auto direction = Vector2((-500 + std::rand() % 1000),
							(-500 + std::rand() % 1000)).Normalize();

	// WHERE TF ARE STD::MIN MAX? <ALGORITHM> DOES NOT HAVE THEM
	auto speed = min(Globals::screenWidth, Globals::screenHeight) / 5 +
				std::rand() % max(Globals::screenWidth, Globals::screenHeight) / 7;
	_body->SetLinearVelocity(ToPhysicCoordinate(direction * speed));
}
