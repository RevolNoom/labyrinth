#include "SceneResult.h"
#include "SpriteAnimation.h"
#include "GameButton.h"
#include "GameScenes/ScenePlayLogicServer.h"
#include "World/Maze/Item/Bat.h"

SceneResult::SceneResult(): Scene()
{

}

void SceneResult::Enter()
{
	auto background = std::make_shared<SolidObject>(ResourceManagers::GetInstance()->GetTexture("TileBig.tga"));
	background->SetPosition(Vector2(Globals::screenWidth / 2, Globals::screenHeight / 2));
	background->SetSize(Vector2(Globals::screenWidth, Globals::screenHeight));
	GetCanvas().Insert(1, background);



	auto shader = ResourceManagers::GetInstance()->GetShader("TextShader");
	std::shared_ptr<Font> origicide = ResourceManagers::GetInstance()->GetFont("Origicide.ttf");

	std::string result =
		ScenePlayLogicServer::GetInstance()->GetGameResult() == ScenePlayLogicServer::Result::WIN ?
		"You Win" : "You Lose";

	auto textResult = std::make_shared<Text>(shader, origicide, result, TextColor::RED, 1);
	textResult->Set2DPosition(Vector2(Globals::screenWidth / 2 - 50, Globals::screenHeight / 5));
	GetCanvas2()[3].push_back(textResult);


	// Some bats to adorn the credit scene
	auto bat = std::make_shared<Bat>();
	bat->SetPosition(Vector2(Globals::screenWidth / 2 - 95, Globals::screenHeight / 5));
	bat->SetSize(Vector2(60, 60));
	GetCanvas().Insert(2, bat->Clone());

	bat->SetPosition(Vector2(Globals::screenWidth / 2 + 85, Globals::screenHeight / 5));
	GetCanvas().Insert(2, bat->Clone());


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