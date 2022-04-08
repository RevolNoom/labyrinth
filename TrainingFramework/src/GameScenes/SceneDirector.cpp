#include "SceneDirector.h"
#include "Scene.h"
#include "SceneIntro.h"
#include "ScenePlay.h"
#include "SceneResult.h"
#include "ServiceLocator.h"

#include "World/PhysicObject.h"
#include "SpriteAnimation.h"
#include "World/Maze/Maze.hpp"
#include "World/Player/Unit.hpp"
#include "GUI.h"

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
	SetupSceneIntro();
	SetupSceneMenu();
	SetupSceneCredit();
	SetupScenePlay();
	SetupSceneResult();
	SetupSceneSetting();
}



void SceneDirector::SetupSceneIntro()
{
	_scene[SCENE_ID::SCENE_INTRO] = std::make_shared<SceneIntro>();
}



void SceneDirector::SetupSceneMenu()
{
	auto menu = std::make_shared<Scene>();
	_scene[SCENE_ID::SCENE_MENU] = menu;

	menu->SetBackgroundMusic(Music("theme.mp3"));
	menu->GetCanvas().Insert(1, GUI::GetInstance()->GetBackground()._tile);


	auto button = std::make_shared<GameButton>(ResourceManagers::GetInstance()->GetTexture("DoorClose.tga"));
	button->SetTexture(ResourceManagers::GetInstance()->GetTexture("DoorOpen.tga"), GameButton::Hover::H_ON);
	button->Set2DPosition(Globals::screenWidth / 2, Globals::screenHeight / 2);
	button->SetSize(200, 200);
	button->SetOnClick([]() {
		SceneDirector::GetInstance()->PushScene(SCENE_ID::SCENE_PLAY);
		});
	menu->GetCanvas2()[3].push_back(button);


	menu->GetCanvas2()[3].push_back(GUI::GetInstance()->GetButton()._exit);
	menu->GetCanvas2()[3].push_back(GUI::GetInstance()->GetButton()._setting);


	// Credit button
	auto texture = ResourceManagers::GetInstance()->GetTexture("Sign.tga");
	auto creditbutton = std::make_shared<GameButton>(texture);
	creditbutton->SetTexture(ResourceManagers::GetInstance()->GetTexture("SignGlow.tga"), GameButton::Hover::H_ON);
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
	
	
	credit->SetBackgroundMusic(Music("theme.mp3"));


	credit->GetCanvas().Insert(1, GUI::GetInstance()->GetBackground()._tile);
	credit->GetCanvas2()[3].push_back(GUI::GetInstance()->GetButton()._return);


	// Credit text
	auto shader = ResourceManagers::GetInstance()->GetShader("TextShader");
	std::shared_ptr<Font> origicide = ResourceManagers::GetInstance()->GetFont("Origicide.ttf");

	auto textCredit = std::make_shared<Text>(shader, origicide, "credits", TextColor::RED, 1);
	textCredit->Set2DPosition(Vector2(Globals::screenWidth / 2 - 50, Globals::screenHeight / 5));
	credit->GetCanvas2()[3].push_back(textCredit);


	// Some bats to adorn the banner
	auto bat = GUI::GetInstance()->GetMisc()._bat->Clone();
	bat->SetPosition(Vector2(Globals::screenWidth / 2 - 85, Globals::screenHeight / 5));
	credit->GetCanvas().Insert(2, bat);

	bat = bat->Clone();
	bat->SetPosition(Vector2(Globals::screenWidth / 2 + 75, Globals::screenHeight / 5));
	credit->GetCanvas().Insert(2, bat);

	// CREDIT CONTENT

	std::shared_ptr<Font> arialbd = ResourceManagers::GetInstance()->GetFont("arialbd.ttf");
	std::string credits[]{ "Treasure Hunter made by Revol Noom.",
							"Game assets from Pixel Dungeon by Watabou.",
							"Box2D physic engine by Erin Catto",
							"Font Origicide by Cpr.Sparhelt.",
							"\"Bats In Cave Sound\" by Mike Koenig."
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


void SceneDirector::SetupSceneSetting()
{
	auto setting = std::make_shared<Scene>();
	_scene[SCENE_ID::SCENE_SETTING] = setting;


	setting->GetCanvas().Insert(1, GUI::GetInstance()->GetBackground()._tile);


	// BANNER
	auto shader = ResourceManagers::GetInstance()->GetShader("TextShader");
	std::shared_ptr<Font> origicide = ResourceManagers::GetInstance()->GetFont("Origicide.ttf");


	auto textCredit = std::make_shared<Text>(shader, origicide, "Settings", TextColor::RED, 1);
	textCredit->Set2DPosition(Vector2(Globals::screenWidth / 2 - 50, Globals::screenHeight / 5));
	setting->GetCanvas2()[3].push_back(textCredit);


	// Some bats to adorn the banner
	auto bat = GUI::GetInstance()->GetMisc()._bat->Clone();
	bat->SetPosition(Vector2(Globals::screenWidth / 2 - 85, Globals::screenHeight / 5));
	setting->GetCanvas().Insert(2, bat);


	bat = bat->Clone();
	bat->SetPosition(Vector2(Globals::screenWidth / 2 + 75, Globals::screenHeight / 5));
	setting->GetCanvas().Insert(2, bat);


	setting->GetCanvas2()[3].push_back(GUI::GetInstance()->GetButton()._return);
	setting->GetCanvas2()[3].push_back(GUI::GetInstance()->GetButton()._music);
	setting->GetCanvas2()[3].push_back(GUI::GetInstance()->GetButton()._sfx);
}
