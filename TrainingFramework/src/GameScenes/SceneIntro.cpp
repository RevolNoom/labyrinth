#include "SceneIntro.h"
#include "World/Maze/Cell.h"

SceneIntro::SceneIntro() : m_time(0.0f)
{
	Init();
}


SceneIntro::~SceneIntro()
{
}


void SceneIntro::Init()
{/*
	auto texture = ResourceManagers::GetInstance()->GetTexture("logo.tga");

	auto logo = std::make_shared<SolidObject>(texture);
	logo->Set2DPosition((float)Globals::screenWidth / 2, (float)Globals::screenHeight / 2);
	logo->SetSize(150, 150);
	_canvas.Insert(1, logo);*/

}

void SceneIntro::Update(float deltaTime)
{
	m_time += deltaTime;
	if (m_time > 1.5)
	{
		m_time = 0;
		SceneDirector::GetInstance()->PushScene(SCENE_ID::SCENE_MENU);
	}
}