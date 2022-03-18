#include "GSIntro.h"

GSIntro::GSIntro() : Scene(StateType::STATE_INTRO), m_time(0.0f)
{
}


GSIntro::~GSIntro()
{
}


void GSIntro::Init()
{
	auto model = ResourceManagers::GetInstance()->GetModel("Sprite2D.nfg");
	auto shader = ResourceManagers::GetInstance()->GetShader("TextureShader");
	auto texture = ResourceManagers::GetInstance()->GetTexture("logo.tga");

	m_logo = std::make_shared<Sprite2D>(model, shader, texture);
	m_logo->Set2DPosition((float)Globals::screenWidth / 2, (float)Globals::screenHeight / 2);
	m_logo->SetSize(150, 150);
}

void GSIntro::Exit()
{
}


void GSIntro::Pause()
{
}

void GSIntro::Resume()
{
}


void GSIntro::HandleEvents()
{
}

void GSIntro::HandleKeyPress(const InputEventKeyPress* ev)
{
}

void GSIntro::HandleMouseClick(const InputEventMouseClick* ev)
{
}

void GSIntro::HandleMouseMotion(const InputEventMouseMotion* ev)
{
}

void GSIntro::Update(float deltaTime)
{
	m_time += deltaTime;
	if (m_time > 1.5)
	{
		SceneDirector::GetInstance()->ChangeState(StateType::STATE_MENU);
		m_time = 0;
	}
}

void GSIntro::Draw()
{
	m_logo->Draw();
}
