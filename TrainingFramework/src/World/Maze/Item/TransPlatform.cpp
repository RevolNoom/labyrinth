#include "TransPlatform.h"
#include "World/Maze/MazeLayoutGenerator.h"

TransPlatform::TransPlatform(std::shared_ptr<Maze> targetMaze, float cooldownTime) :
	Trap(ResourceManagers::GetInstance()->GetTexture("TrapEnable.tga")),
	_targetMaze(targetMaze),
	_remainingTime(0)
{
	SetEnabled(true);
	SetCooldownTimer(cooldownTime);
	auto mazeSize = _targetMaze.lock()->GetLayout()->GetSize();
	_cacheLayout = MazeLayoutGenerator::GetInstance()->Generate(_targetMaze.lock().get());
}


void TransPlatform::RegisterToWorld(b2World* world)
{
	b2BodyDef body;
	body.type = b2BodyType::b2_staticBody;
	body.position = ToPhysicCoordinate(GetPosition());

	_body = world->CreateBody(&body);

	b2PolygonShape shape;
	auto size = ToPhysicCoordinate(GetSize()/2);
	shape.SetAsBox(size.x, size.y);

	b2FixtureDef fdef;
	fdef.isSensor = true;
	fdef.density = 0;
	fdef.friction = 0;
	fdef.shape = &shape; 

	// Let this fixture contains its parent
	fdef.userData.pointer = reinterpret_cast<uintptr_t>(static_cast<Trap*>(this));

	_body->CreateFixture(&fdef);

	SetEnabled(true);
}


void TransPlatform::SetEnabled(bool enable)
{
	if (enable)
		_sprite->SetTexture(ResourceManagers::GetInstance()->GetTexture("TrapEnable.tga"));
	else
		_sprite->SetTexture(ResourceManagers::GetInstance()->GetTexture("TrapDisable.tga"));

	if (_body)
		_body->SetEnabled(enable);
}

void TransPlatform::TargetMaze(std::shared_ptr<Maze> targetMaze)
{
	_targetMaze = targetMaze;
}

void TransPlatform::Trigger()
{
	_remainingTime = _maxTime;
	SetEnabled(false);

	auto layout = _targetMaze.lock()->GetLayout();
	_targetMaze.lock()->SetLayout(_cacheLayout);
	_cacheLayout = layout;
}

void TransPlatform::SetCooldownTimer(float cooldownTime)
{
	if (cooldownTime < 0.5)
		cooldownTime = 0.5;
	_maxTime = cooldownTime;
	if (_remainingTime > _maxTime)
		_remainingTime = _maxTime;
}

void TransPlatform::Update(float delta)
{
	if (_remainingTime > 0)
	{
		_remainingTime -= delta;
		if (_remainingTime < 0)
		{
			_remainingTime = 0;
			SetEnabled(true);
		}
	}
}
