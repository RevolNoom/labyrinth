#include "Wraith.h"
#include "GameScenes/ScenePlayLogicServer.h"
#include "ServiceLocator.h"

Wraith::Wraith(): Bat()
{
	//_squeak = Music("snd_death.mp3");
	_squeakTimer = 6 + (std::rand() % 6000) / 1000.0;

	_anim = std::make_shared<SpriteAnimation>(
					ResourceManagers::GetInstance()->GetModel("Sprite2d.nfg"),
					ResourceManagers::GetInstance()->GetShader("Animation"),
					ResourceManagers::GetInstance()->GetTexture("wraith.tga"),
					7, 1, 0, 0.2);

	_startupTimer.Start();
}


std::shared_ptr<PhysicObject> Wraith::Clone()
{
	auto newClone = std::make_shared<Wraith>();

	newClone->SetRotation(GetRotation());
	newClone->SetPosition(GetPosition());
	newClone->SetEnabled(IsEnabled());
	newClone->SetSize(GetSize());

	return newClone;
}

void Wraith::Update(float delta)
{
	_anim->Update(delta);
	_startupTimer.Update(delta);

	if (_startupTimer.TimeOut())
	{
		if (!IsEnabled())
			SetEnabled(true);
		ChasePlayer();

		MoveSpriteToBody(); 
		
		_squeakTimer.Update(delta);
		if (_squeakTimer.TimeOut())
		{
			_squeakTimer.Reset();
			_squeakTimer.Start();
			ServiceLocator::GetInstance()->GetSoundEffectAudioPlayer()->Play(_squeak);
		}
	}
}


void Wraith::ChasePlayer()
{
	auto direction = ScenePlayLogicServer::GetInstance()->GetPlayer()->GetPosition() - GetPosition();
	auto maxSpeed = 40;
	_body->SetLinearVelocity(ToPhysicCoordinate(direction.Normalize() * maxSpeed));
}