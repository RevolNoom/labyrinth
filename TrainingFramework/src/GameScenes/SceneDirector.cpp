#include "SceneDirector.h"
#include "Scene.h"
#include "SceneIntro.h"
#include "ScenePlay.h"

#include "World/PhysicObject.hpp"
#include "SpriteAnimation.h"
#include "GameButton.h"
#include "World/Maze/Maze.hpp"
#include "World/Player/Unit.hpp"

SceneDirector::SceneDirector() : m_running(true), m_fullscreen(false)
{
	SetupScenes();
	PushScene(SCENE_ID::SCENE_INTRO);
}


SceneDirector::~SceneDirector()
{
}


void SceneDirector::Cleanup()
{
	// cleanup the all states
	while (!_sceneStack.empty()) {
		_sceneStack.back()->Exit();
		_sceneStack.pop_back();
	}
}


void SceneDirector::PushScene(SCENE__ID id)
{
	if (id < 0 || id > _scene.size())
	{
		std::cerr << "SceneID: " << id << ". Are you kidding me?\n";
		return;
	}

	if (_sceneStack.size() > 0)
		CurrentScene()->Pause();

	_sceneStack.push_back(_scene[id]);
	CurrentScene()->Enter();
}


void SceneDirector::PopScene()
{
	// cleanup the current state
	CurrentScene()->Exit();
	_sceneStack.pop_back();

	CurrentScene()->Resume();
}


void SceneDirector::Update(float delta)
{
	CurrentScene()->Update(delta);
}


void SceneDirector::HandleEvent(std::shared_ptr<InputEvent> ev)
{
	CurrentScene()->HandleEvent(ev);
}


void SceneDirector::SetupScenes()
{
	SetupSceneIntro();
	SetupSceneMenu(); 
	SetupScenePlay();
}



void SceneDirector::SetupSceneIntro()
{
	_scene[SCENE_ID::SCENE_INTRO] = std::make_shared<SceneIntro>();
}



void SceneDirector::SetupSceneMenu()
{
	// TODO: I'm putting ScenePlay here for debuggin
	_scene[SCENE_ID::SCENE_MENU] = std::make_shared<ScenePlay>();


	/*
	auto texture = ResourceManagers::GetInstance()->GetTexture("bg_main_menu.tga");

	auto background = std::make_shared<Sprite2D>(texture);
	background->Set2DPosition(Globals::screenWidth / 2, Globals::screenHeight / 2);
	background->SetSize(Globals::screenWidth, Globals::screenHeight);
	menu->GetCanvas().Insert(1, background);


	texture = ResourceManagers::GetInstance()->GetTexture("btn_play.tga");
	std::shared_ptr<GameButton> button = std::make_shared<GameButton>(texture);
	button->Set2DPosition(Globals::screenWidth / 2, Globals::screenHeight / 2);
	button->SetSize(200, 200);
	button->SetOnClick([]() {
		SceneDirector::GetInstance()->PushScene(SCENE_ID::SCENE_PLAY);
		});
	menu->GetCanvas().Insert(3, button);


	// exit button
	texture = ResourceManagers::GetInstance()->GetTexture("btn_close.tga");
	button = std::make_shared<GameButton>(texture);
	button->Set2DPosition(Globals::screenWidth - 50, 50);
	button->SetSize(50, 50);
	button->SetOnClick([]() {
		exit(0);
		});
	menu->GetCanvas().Insert(3, button);


	// game title
	auto shader = ResourceManagers::GetInstance()->GetShader("TextShader");
	std::shared_ptr<Font> font = ResourceManagers::GetInstance()->GetFont("Brightly Crush Shine.otf");
	auto textGameName = std::make_shared< Text>(shader, font, "Epic Game", Vector4(1.0f, 0.5f, 0.0f, 1.0f), 3.0f);
	textGameName->Set2DPosition(Vector2(60, 200));
	menu->GetCanvas().Insert(3, textGameName);

	// Some cheery music
	menu->SetBackgroundMusic(Music("Alarm01.wav"));

	*/


	
}



void SceneDirector::SetupScenePlay()
{
	//_scene[SCENE_ID::SCENE_PLAY] = std::make_shared<ScenePlay>();
}
