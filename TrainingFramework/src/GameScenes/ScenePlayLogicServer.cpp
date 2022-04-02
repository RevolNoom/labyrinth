#include "ScenePlayLogicServer.h"

void ScenePlayLogicServer::SetUpPrize(Prize* prize)
{
	_prize = prize;
	_prize->SetEnabled(true);
}

void ScenePlayLogicServer::PickUpPrize()
{
	_prize->SetEnabled(false);
	_escape->SetEnabled(true);
}



void ScenePlayLogicServer::SetUpExitStair(ExitStair* escape)
{
	_escape = escape;
	_escape->SetEnabled(false);
}

void ScenePlayLogicServer::EscapeMaze()
{
	_escape->SetEnabled(false);
	_scenePlay->WinGame();
}

void ScenePlayLogicServer::SetUpScenePlay(ScenePlay* sp)
{
	_scenePlay = sp;
}
