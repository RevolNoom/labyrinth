#include "World/Maze/Item/ExitStair.h"
#include "GameScenes/ScenePlayLogicServer.h"

ExitStair::ExitStair() :
	Trap(ResourceManagers::GetInstance()->GetTexture("ExitStair.tga")),
	_enableExit(false)
{
	ScenePlayLogicServer::GetInstance()->SetUpExitStair(this);
}

void ExitStair::Draw()
{
	if (_enableExit)
		Trap::Draw();
}

void ExitStair::Trigger()
{
	if (_enableExit)
		//std::cout << "Singleton problem\n";
		ScenePlayLogicServer::GetInstance()->EscapeMaze();
}

void ExitStair::EnableExit()
{
	_enableExit = true;
}

void ExitStair::Escaped()
{
	_enableExit = false;
}

std::shared_ptr<PhysicObject> ExitStair::Clone()
{
	auto newClone = std::make_shared<ExitStair>();
	newClone->SetRotation(GetRotation());
	newClone->SetPosition(GetPosition());
	newClone->SetEnabled(IsEnabled());
	newClone->SetSize(GetSize());

	return newClone;
}
