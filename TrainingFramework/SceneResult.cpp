#include "SceneResult.h"
#include "SpriteAnimation.h"
#include "GameButton.h"
#include "GameScenes/ScenePlayLogicServer.h"

SceneResult::SceneResult(): Scene()
{

}

void SceneResult::Enter()
{
	auto background = std::make_shared<Sprite2D>(ResourceManagers::GetInstance()->GetTexture("TileBig.tga"));
	background->Set2DPosition(Globals::screenWidth / 2, Globals::screenHeight / 2);
	background->SetSize(Globals::screenWidth, Globals::screenHeight);
	GetCanvas2()[1].push_back(background);



	auto shader = ResourceManagers::GetInstance()->GetShader("TextShader");
	std::shared_ptr<Font> origicide = ResourceManagers::GetInstance()->GetFont("Origicide.ttf");

	std::string result =
		ScenePlayLogicServer::GetInstance()->GetGameResult() == ScenePlayLogicServer::Result::WIN ?
		"You Win" : "You Lose";

	auto textResult = std::make_shared<Text>(shader, origicide, result, TextColor::RED, 1);
	textResult->Set2DPosition(Vector2(Globals::screenWidth / 2 - 50, Globals::screenHeight / 5));
	GetCanvas2()[3].push_back(textResult);


	// Some bats to adorn the credit scene
	auto _bat = std::make_shared<SpriteAnimation>(
		ResourceManagers::GetInstance()->GetModel("Sprite2D.nfg"),
		ResourceManagers::GetInstance()->GetShader("Animation"),
		ResourceManagers::GetInstance()->GetTexture("bat.tga"), 2, 1, 0, 0.1);
	_bat->Set2DPosition(Globals::screenWidth / 2 - 95, Globals::screenHeight / 5);
	_bat->SetSize(60, 60);
	GetCanvas2()[2].push_back(_bat);


	_bat = std::make_shared<SpriteAnimation>(
		ResourceManagers::GetInstance()->GetModel("Sprite2D.nfg"),
		ResourceManagers::GetInstance()->GetShader("Animation"),
		ResourceManagers::GetInstance()->GetTexture("bat.tga"), 2, 1, 0, 0.1);
	_bat->Set2DPosition(Globals::screenWidth / 2 + 85, Globals::screenHeight / 5);
	_bat->SetSize(60, 60);
	GetCanvas2()[2].push_back(_bat);


	std::shared_ptr<Font> arialbd = ResourceManagers::GetInstance()->GetFont("arialbd.ttf");
	auto retryTxt = std::make_shared<Text>(shader, arialbd, "Retry?", TextColor::WHITE, 0.7, TextAlign::CENTER);
	retryTxt->Set2DPosition(Vector2(Globals::screenWidth / 2 - 30, Globals::screenHeight / 3));
	GetCanvas2()[3].push_back(retryTxt);



	auto retryDoor = std::make_shared<GameButton>(ResourceManagers::GetInstance()->GetTexture("DoorClose.tga"));
	retryDoor->SetHoveringTexture(ResourceManagers::GetInstance()->GetTexture("DoorOpen.tga"));
	retryDoor->Set2DPosition(Globals::screenWidth / 2, Globals::screenHeight / 2);
	retryDoor->SetSize(200, 200);
	retryDoor->SetOnClick([]() {
		SceneDirector::GetInstance()->PushScene(SCENE_ID::SCENE_PLAY);
		});
	GetCanvas2()[3].push_back(retryDoor);



	// exit button
	auto button = std::make_shared<GameButton>(ResourceManagers::GetInstance()->GetTexture("btn_close.tga"));
	button->Set2DPosition(Globals::screenWidth - 50, 50);
	button->SetSize(50, 50);
	button->SetOnClick([]() {
		exit(0);
		});
	GetCanvas2()[3].push_back(button);
}