#include "SceneIntro.h"
#include "World/Maze/Cell.h"
#include "World/Maze/Item/Bat.h"

SceneIntro::SceneIntro() : _timer(1.5)
{
	Init();
}


SceneIntro::~SceneIntro()
{
}


void SceneIntro::Init()
{
	auto background = std::make_shared<SolidObject>(ResourceManagers::GetInstance()->GetTexture("BlackBackground.tga"));
	background->SetPosition(Vector2(Globals::screenWidth/2, Globals::screenHeight/2));
	background->SetSize(Vector2(Globals::screenWidth, Globals::screenHeight));
	_canvas.Insert(1, background);
	
	auto bat = std::make_shared<Bat>();
	bat->SetPosition(Vector2(Globals::screenWidth / 2, Globals::screenHeight / 2));
	bat->SetSize(Vector2(60, 60));
	GetCanvas().Insert(1, bat);

	_rev = std::make_shared<Text>(
		ResourceManagers::GetInstance()->GetShader("TextShader"),
		ResourceManagers::GetInstance()->GetFont("Origicide.ttf"),
		"rev", TextColor::RED, 2); 
	_rev->Set2DPosition(Globals::screenWidth / 2 - 40, Globals::screenHeight / 2 + 60);
	_canvas2[2].push_back(_rev);

	_timer.Start();
}

void SceneIntro::Update(float deltaTime)
{
	Scene::Update(deltaTime);
	_timer.Update(deltaTime);
	if (_timer.TimeOut())
		SceneDirector::GetInstance()->PushScene(SCENE_ID::SCENE_MENU);
}

void SceneIntro::Draw()
{
	Scene::Draw();
	_rev->Draw();
}
