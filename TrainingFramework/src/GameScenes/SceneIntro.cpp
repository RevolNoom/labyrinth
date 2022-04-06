#include "SceneIntro.h"
#include "World/Maze/Cell.h"
#include "World/Maze/Item/Bat.h"
#include "GUI.h"

SceneIntro::SceneIntro() : _timer(1.5)
{
	_canvas.Insert(1, GUI::GetInstance()->GetBackground()._black);

	auto bat = GUI::GetInstance()->GetMisc()._bat->Clone();
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


SceneIntro::~SceneIntro()
{
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
