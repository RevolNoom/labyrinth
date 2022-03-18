#include "SceneIntro.h"

SceneIntro::SceneIntro() : m_time(0.0f)
{
}


SceneIntro::~SceneIntro()
{
}


void SceneIntro::Init()
{
	auto model = ResourceManagers::GetInstance()->GetModel("Sprite2D.nfg");
	auto shader = ResourceManagers::GetInstance()->GetShader("TextureShader");
	auto texture = ResourceManagers::GetInstance()->GetTexture("logo.tga");

	auto logo = std::make_shared<Sprite2D>(model, shader, texture);
	logo->Set2DPosition((float)Globals::screenWidth / 2, (float)Globals::screenHeight / 2);
	logo->SetSize(150, 150);
	_canvas.Insert(1, logo);
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