#include "ScenePlayLogicServer.h"
#include "World/Player/Unit.hpp"


void ScenePlayLogicServer::SetUpPrize(Prize* prize)
{
	_prize = prize;
}


void ScenePlayLogicServer::PickUpPrize()
{
	_prize->SetEnabled(false);
	_escape->EnableExit();
	_escape->SetEnabled(true);
}


void ScenePlayLogicServer::SetUpExitStair(ExitStair* escape)
{
	_escape = escape;
}


void ScenePlayLogicServer::EscapeMaze()
{
	_escape->Escaped();
	_scenePlay->DonePlaying();
	_result = Result::WIN;
}


void ScenePlayLogicServer::Die()
{
	_scenePlay->DonePlaying();
	_result = Result::LOSE;
}

void ScenePlayLogicServer::SetUpScenePlay(ScenePlay* sp)
{
	_scenePlay = sp;
}

void ScenePlayLogicServer::SetupPlayer(Unit* player)
{
	_player = player;
}


Unit* ScenePlayLogicServer::GetPlayer()
{
	return _player;
}

void ScenePlayLogicServer::StartPlaying()
{
	_prize->SetEnabled(true);
	_escape->SetEnabled(false);
}

ScenePlayLogicServer::Result ScenePlayLogicServer::GetGameResult()
{
	return _result;
}
