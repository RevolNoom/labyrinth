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
{
	auto background = std::make_shared<SolidObject>(ResourceManagers::GetInstance()->GetTexture("BlackBackground.tga"));
	background->SetPosition(Vector2(Globals::screenWidth/2, Globals::screenHeight/2));
	background->SetSize(Vector2(Globals::screenWidth, Globals::screenHeight));
	_canvas.Insert(1, background);
	

	_bat = std::make_shared<SpriteAnimation>(
		ResourceManagers::GetInstance()->GetModel("Sprite2D.nfg"),
		ResourceManagers::GetInstance()->GetShader("Animation"),
		ResourceManagers::GetInstance()->GetTexture("bat.tga"), 2, 1, 0, 0.1);
	_bat->Set2DPosition(Globals::screenWidth / 2, Globals::screenHeight / 2);
	_bat->SetSize(60, 60);
	_canvas2[1].push_back(_bat);


	_rev = std::make_shared<Text>(
		ResourceManagers::GetInstance()->GetShader("TextShader"),
		ResourceManagers::GetInstance()->GetFont("Origicide.ttf"),
		"rev", TextColor::RED, 2); 
	_rev->Set2DPosition(Globals::screenWidth / 2 - 40, Globals::screenHeight / 2 + 60);
	_canvas2[2].push_back(_rev);
}

void SceneIntro::Update(float deltaTime)
{
	_bat->Update(deltaTime);

	m_time += deltaTime;
	if (m_time > 1.5)
	{
		m_time = 0;
		SceneDirector::GetInstance()->PushScene(SCENE_ID::SCENE_MENU);
	}
}

void SceneIntro::Draw()
{
	Scene::Draw();
	_bat->Draw();
	_rev->Draw();
}
