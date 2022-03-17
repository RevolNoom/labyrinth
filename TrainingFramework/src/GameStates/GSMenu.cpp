#include "GSMenu.h"
#include "Camera.h"
#include "../World/WorldObject.hpp"


GSMenu::GSMenu() : GameStateBase(StateType::STATE_MENU), 
	m_background(nullptr), m_listButton(std::list<std::shared_ptr<GameButton>>{}), m_textGameName(nullptr)
{
}


GSMenu::~GSMenu()
{
}



void GSMenu::Init()
{
	auto model = ResourceManagers::GetInstance()->GetModel("Sprite2D.nfg");
	auto texture = ResourceManagers::GetInstance()->GetTexture("bg_main_menu.tga");
	auto shader = ResourceManagers::GetInstance()->GetShader("TextureShader");

	// background
	
	m_background = std::make_shared<Sprite2D>(model, shader, texture);
	m_background->Set2DPosition(Globals::screenWidth / 2, Globals::screenHeight / 2);
	m_background->SetSize(Globals::screenWidth, Globals::screenHeight);

	_canvas.Insert(1, m_background);

	/* WORLD OBJECT TEST GROUND */
	// Sylas 
	auto sylas = ResourceManagers::GetInstance()->GetTexture("Sylas.tga");

	auto s = std::make_shared<Sprite2D>(model, shader, sylas);
	s->Set2DPosition(Globals::screenWidth / 3, Globals::screenHeight / 3);
	s->SetSize(300, 300);
	auto w = std::make_shared<WorldObject>(sylas);

	_canvas.Insert(2, w);
	/* END TEST GROUND*/



	// play button
	texture = ResourceManagers::GetInstance()->GetTexture("btn_play.tga");
	std::shared_ptr<GameButton> button = std::make_shared<GameButton>(model, shader, texture);
	button->Set2DPosition(Globals::screenWidth / 2, Globals::screenHeight / 2);
	button->SetSize(200, 200);
	button->SetOnClick([]() {
			GameStateMachine::GetInstance()->ChangeState(StateType::STATE_PLAY);
		});
	_canvas.Insert(1, button);

	// exit button
	texture = ResourceManagers::GetInstance()->GetTexture("btn_close.tga");
	button = std::make_shared<GameButton>(model, shader, texture);
	button->Set2DPosition(Globals::screenWidth - 50, 50);
	button->SetSize(50, 50);
	button->SetOnClick([]() {
		exit(0);
		});
	_canvas.Insert(1, button);

	// game title
	shader = ResourceManagers::GetInstance()->GetShader("TextShader");
	std::shared_ptr<Font> font = ResourceManagers::GetInstance()->GetFont("Brightly Crush Shine.otf");
	m_textGameName = std::make_shared< Text>(shader, font, "Epic Game", Vector4(1.0f, 0.5f, 0.0f, 1.0f), 3.0f);
	m_textGameName->Set2DPosition(Vector2(60, 200));
	_canvas.Insert(1, m_textGameName);

	std::string name = "Alarm01.wav";
	ResourceManagers::GetInstance()->PlaySound(name);
}

void GSMenu::Exit()
{
	ResourceManagers::FreeInstance();
}


void GSMenu::Pause()
{
}

void GSMenu::Resume()
{
}


void GSMenu::HandleEvents()
{
}

void GSMenu::HandleKeyEvents(int key, bool bIsPressed)
{
}

void GSMenu::HandleTouchEvents(int x, int y, bool bIsPressed)
{
	for (auto obj : _canvas.GetAll())
		obj->HandleTouchEvents(x, y, bIsPressed);
}

void GSMenu::HandleMouseMoveEvents(int x, int y)
{
}

void GSMenu::Update(float deltaTime)
{
	m_background->Update(deltaTime);
	for (auto it : m_listButton)
	{
		it->Update(deltaTime);
	}
}

void GSMenu::Draw()
{
	_canvas.Draw();
}
