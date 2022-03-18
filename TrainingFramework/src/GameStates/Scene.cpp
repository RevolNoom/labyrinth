/*
#include "GSIntro.h"
#include "GSMenu.h"
*/
#include "GSPlay.h"
#include "GSIntro.h"
#include "GSMenu.h"

#include "Scene.h"

Scene::Scene(StateType stateType) : m_stateType(stateType)
{}

std::shared_ptr<Scene> Scene::CreateState(StateType stt)
{
	std::shared_ptr<Scene> gs = nullptr;
	switch (stt)
	{
	case StateType::STATE_INVALID:
		break;
	case StateType::STATE_INTRO:
		gs = std::make_shared<GSIntro>();
		break;
	case StateType::STATE_MENU:
		gs = std::make_shared<GSMenu>();
		break;
	case StateType::STATE_PLAY:
		gs = std::make_shared<GSPlay>();
		break;
	default:
		break;
	}
	return gs;
}

StateType Scene::GetGameStateType()
{
	return m_stateType;
}