#include "World/Maze/Item/ExitStair.h"
#include "GameScenes/ScenePlayLogicServer.h"

ExitStair::ExitStair() :
	Trap(ResourceManagers::GetInstance()->GetTexture("ExitStair.tga"))
{
	ScenePlayLogicServer::GetInstance()->SetUpExitStair(this);
}

void ExitStair::Draw()
{
	if (IsEnabled())
		Trap::Draw();
}

void ExitStair::Trigger()
{
	std::cout << "Escape!\n";
	if (IsEnabled())
		ScenePlayLogicServer::GetInstance()->EscapeMaze();
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
