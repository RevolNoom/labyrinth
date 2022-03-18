#include "SceneDirector.h"
#include "Scene.h"
#include "SceneIntro.h"
#include "World/WorldObject.hpp"
#include "SpriteAnimation.h"
#include "GameButton.h"

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
		std::cerr << "Are you kidding me? SceneID: " << id << "\n";
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
	auto menu = std::make_shared<Scene>();

	auto model = ResourceManagers::GetInstance()->GetModel("Sprite2D.nfg");
	auto shader = ResourceManagers::GetInstance()->GetShader("TextureShader");
	auto texture = ResourceManagers::GetInstance()->GetTexture("bg_main_menu.tga");


	auto background = std::make_shared<Sprite2D>(model, shader, texture);
	background->Set2DPosition(Globals::screenWidth / 2, Globals::screenHeight / 2);
	background->SetSize(Globals::screenWidth, Globals::screenHeight);
	menu->GetCanvas().Insert(1, background);


	texture = ResourceManagers::GetInstance()->GetTexture("btn_play.tga");
	std::shared_ptr<GameButton> button = std::make_shared<GameButton>(model, shader, texture);
	button->Set2DPosition(Globals::screenWidth / 2, Globals::screenHeight / 2);
	button->SetSize(200, 200);
	button->SetOnClick([]() {
		SceneDirector::GetInstance()->PushScene(SCENE_ID::SCENE_PLAY);
		});
	menu->GetCanvas().Insert(3, button);


	// exit button
	texture = ResourceManagers::GetInstance()->GetTexture("btn_close.tga");
	button = std::make_shared<GameButton>(model, shader, texture);
	button->Set2DPosition(Globals::screenWidth - 50, 50);
	button->SetSize(50, 50);
	button->SetOnClick([]() {
		exit(0);
		});
	menu->GetCanvas().Insert(3, button);


	// game title
	shader = ResourceManagers::GetInstance()->GetShader("TextShader");
	std::shared_ptr<Font> font = ResourceManagers::GetInstance()->GetFont("Brightly Crush Shine.otf");
	auto textGameName = std::make_shared< Text>(shader, font, "Epic Game", Vector4(1.0f, 0.5f, 0.0f, 1.0f), 3.0f);
	textGameName->Set2DPosition(Vector2(60, 200));
	menu->GetCanvas().Insert(3, textGameName);


	// Some cheery music
	menu->SetBackgroundMusic(Music("Alarm01.wav"));


	_scene[SCENE_ID::SCENE_MENU] = menu;
}



void SceneDirector::SetupScenePlay()
{
	auto play = std::make_shared<Scene>();

	auto model = ResourceManagers::GetInstance()->GetModel("Sprite2D.nfg");
	auto texture = ResourceManagers::GetInstance()->GetTexture("bg_play1.tga");
	auto shader = ResourceManagers::GetInstance()->GetShader("TextureShader");


	// background
	auto background = std::make_shared<Sprite2D>(model, shader, texture);
	background->Set2DPosition((float)Globals::screenWidth / 2, (float)Globals::screenHeight / 2);
	background->SetSize(Globals::screenWidth, Globals::screenHeight);
	play->GetCanvas().Insert(1, background);


	// button close
	texture = ResourceManagers::GetInstance()->GetTexture("btn_close.tga");
	auto button = std::make_shared<GameButton>(model, shader, texture);
	button->Set2DPosition(Globals::screenWidth - 50, 50);
	button->SetSize(50, 50);
	button->SetOnClick([this]() {
		SceneDirector::GetInstance()->PopScene();
		});
	play->GetCanvas().Insert(4, button);


	// score
	shader = ResourceManagers::GetInstance()->GetShader("TextShader");
	std::shared_ptr<Font> font = ResourceManagers::GetInstance()->GetFont("Brightly Crush Shine.otf");
	auto score = std::make_shared< Text>(shader, font, "score: 10", TextColor::RED, 1.0);
	score->Set2DPosition(Vector2(5, 25));
	play->GetCanvas().Insert(3, score);


	shader = ResourceManagers::GetInstance()->GetShader("Animation");
	texture = ResourceManagers::GetInstance()->GetTexture("Actor1_2.tga");
	auto obj = std::make_shared<SpriteAnimation>(model, shader, texture, 9, 6, 5, 0.1f);
	obj->Set2DPosition(240, 400);
	obj->SetSize(334, 223);
	//obj->SetRotation(Vector3(0.0f, 3.14f, 0.0f));
	play->GetCanvas().Insert(2, obj);


	_scene[SCENE_ID::SCENE_PLAY] = play;
}