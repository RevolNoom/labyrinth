#include "SceneDirector.h"
#include "Scene.h"
#include "SceneIntro.h"
#include "ScenePlay.h"
#include "SceneResult.h"

#include "World/PhysicObject.h"
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

	if (_sceneStack.size())
		CurrentScene()->Resume();
	else
		exit(0);
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
	SetupSceneCredit();
	SetupSceneIntro();
	SetupSceneMenu(); 
	SetupScenePlay();
	SetupSceneResult();
}



void SceneDirector::SetupSceneIntro()
{
	_scene[SCENE_ID::SCENE_INTRO] = std::make_shared<SceneIntro>();
}



void SceneDirector::SetupSceneMenu()
{
	auto menu = std::make_shared<Scene>();
	_scene[SCENE_ID::SCENE_MENU] = menu;


	auto texture = ResourceManagers::GetInstance()->GetTexture("TileBig.tga");

	auto background = std::make_shared<Sprite2D>(texture);
	background->Set2DPosition(Globals::screenWidth / 2, Globals::screenHeight / 2);
	background->SetSize(Globals::screenWidth, Globals::screenHeight);
	menu->GetCanvas2()[1].push_back(background);


	auto button = std::make_shared<GameButton>(ResourceManagers::GetInstance()->GetTexture("DoorClose.tga"));
	button->SetHoveringTexture(ResourceManagers::GetInstance()->GetTexture("DoorOpen.tga"));
	button->Set2DPosition(Globals::screenWidth / 2, Globals::screenHeight / 2);
	button->SetSize(200, 200);
	button->SetOnClick([]() {
		SceneDirector::GetInstance()->PushScene(SCENE_ID::SCENE_PLAY);
		});
	menu->GetCanvas2()[3].push_back(button);


	// exit button
	texture = ResourceManagers::GetInstance()->GetTexture("btn_close.tga");
	button = std::make_shared<GameButton>(texture);
	button->Set2DPosition(Globals::screenWidth - 50, 50);
	button->SetSize(50, 50);
	button->SetOnClick([]() {
		SceneDirector::GetInstance()->PopScene();
		});
	menu->GetCanvas2()[3].push_back(button);


	// Credit button
	texture = ResourceManagers::GetInstance()->GetTexture("Sign.tga");
	auto creditbutton = std::make_shared<GameButton>(texture);
	creditbutton->SetHoveringTexture(ResourceManagers::GetInstance()->GetTexture("SignGlow.tga"));
	creditbutton->Set2DPosition(Globals::screenWidth/2 - 130, Globals::screenHeight / 2 + 50);
	creditbutton->SetSize(50, 70);
	creditbutton->SetOnClick([]() {
		SceneDirector::GetInstance()->PushScene(SCENE_ID::SCENE_CREDIT);
		});
	menu->GetCanvas2()[4].push_back(creditbutton);
	

	// game title
	auto shader = ResourceManagers::GetInstance()->GetShader("TextShader");
	std::shared_ptr<Font> font = ResourceManagers::GetInstance()->GetFont("Origicide.ttf");
	auto textGameName = std::make_shared<Text>(shader, font, "Treasure hunter", TextColor::RED, 2);
	textGameName->Set2DPosition(Vector2(30, 200));
	menu->GetCanvas2()[3].push_back(textGameName);

	// Some cheery music
	menu->SetBackgroundMusic(Music("Alarm01.wav"));
}


void SceneDirector::SetupSceneCredit()
{
	auto credit = std::make_shared<Scene>();
	_scene[SCENE_ID::SCENE_CREDIT] = credit;


	auto texture = ResourceManagers::GetInstance()->GetTexture("TileBig.tga");
	auto background = std::make_shared<Sprite2D>(texture);
	background->Set2DPosition(Globals::screenWidth / 2, Globals::screenHeight / 2);
	background->SetSize(Globals::screenWidth, Globals::screenHeight);
	credit->GetCanvas2()[1].push_back(background);

	// return button
	auto button = std::make_shared<GameButton>(ResourceManagers::GetInstance()->GetTexture("btn_close.tga"));
	button->Set2DPosition(Globals::screenWidth - 50, 50);
	button->SetSize(50, 50);
	button->SetOnClick([]() {
		SceneDirector::GetInstance()->PopScene();
		});
	credit->GetCanvas2()[3].push_back(button);

	// Credit text
	auto shader = ResourceManagers::GetInstance()->GetShader("TextShader");
	std::shared_ptr<Font> origicide = ResourceManagers::GetInstance()->GetFont("Origicide.ttf");

	auto textCredit = std::make_shared<Text>(shader, origicide, "credits", TextColor::RED, 1);
	textCredit->Set2DPosition(Vector2(Globals::screenWidth / 2 - 50, Globals::screenHeight / 5));
	credit->GetCanvas2()[3].push_back(textCredit);

	// Some bats to adorn the credit scene
	auto _bat = std::make_shared<SpriteAnimation>(
		ResourceManagers::GetInstance()->GetModel("Sprite2D.nfg"),
		ResourceManagers::GetInstance()->GetShader("Animation"),
		ResourceManagers::GetInstance()->GetTexture("bat.tga"), 2, 1, 0, 0.1);
	_bat->Set2DPosition(Globals::screenWidth / 2 - 85, Globals::screenHeight / 5);
	_bat->SetSize(60, 60);
	credit->GetCanvas2()[2].push_back(_bat);


	_bat = std::make_shared<SpriteAnimation>(
		ResourceManagers::GetInstance()->GetModel("Sprite2D.nfg"),
		ResourceManagers::GetInstance()->GetShader("Animation"),
		ResourceManagers::GetInstance()->GetTexture("bat.tga"), 2, 1, 0, 0.1);
	_bat->Set2DPosition(Globals::screenWidth / 2 + 75, Globals::screenHeight / 5);
	_bat->SetSize(60, 60);
	credit->GetCanvas2()[2].push_back(_bat);




	// CREDIT CONTENT

	std::shared_ptr<Font> arialbd = ResourceManagers::GetInstance()->GetFont("arialbd.ttf");
	std::string credits[]{ "Treasure Hunter made by Revol Noom.",
							"Game assets from Pixel Dungeon by Watabou.",
							"Box2D physic engine by Erin Catto",
							"Font Origicide by Cpr.Sparhelt.",
							"Game engine made by awesome Gameloft team." };

	for (int iii = 0; iii < sizeof(credits)/sizeof(credits[0]); ++iii)
	{
		auto whiteCreditTxt = std::make_shared<Text>(shader, arialbd, credits[iii], TextColor::WHITE, 0.7, TextAlign::CENTER);
		whiteCreditTxt->Set2DPosition(Vector2(Globals::screenWidth / 10, Globals::screenHeight / 3 + iii*30));
		credit->GetCanvas2()[3].push_back(whiteCreditTxt);
	}

}



void SceneDirector::SetupScenePlay()
{
	_scene[SCENE_ID::SCENE_PLAY] = std::make_shared<ScenePlay>();
}


void SceneDirector::SetupSceneResult()
{
	_scene[SCENE_ID::SCENE_RESULT] = std::make_shared<SceneResult>();
}
