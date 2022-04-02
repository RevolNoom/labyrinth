#include "TransPlatform.h"
#include "World/Maze/MazeLayoutGenerator.h"



TransPlatform::TransPlatform(Maze *targetMaze, float cooldownTime) :
	Trap(ResourceManagers::GetInstance()->GetTexture("TrapEnable.tga")),
	_targetMaze(targetMaze),
	_cacheLayout(MazeLayoutGenerator::GetInstance()->Generate(_targetMaze)),
	_remainingTime(0),
	_body(nullptr)
{
	SetEnabled(true);
	SetCooldownTimer(cooldownTime);
	auto mazeSize = _targetMaze->GetLayout().GetSize();
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

void TransPlatform::TargetMaze(Maze *targetMaze)
{
	_targetMaze = targetMaze;
}

void TransPlatform::Trigger()
{
	_remainingTime = _maxTime;
	SetEnabled(false);

	auto &layout = _targetMaze->GetLayout();
	_targetMaze->SetLayout(_cacheLayout);
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

std::shared_ptr<PhysicObject> TransPlatform::Clone()
{
	auto newClone = std::make_shared<TransPlatform>(_targetMaze, _maxTime);
	newClone->SetRotation(GetRotation());
	newClone->SetPosition(GetPosition());
	newClone->SetEnabled(IsEnabled());
	newClone->SetSize(GetSize());

	return newClone;
}
