#include "SceneResult.h"
#include "SpriteAnimation.h"
#include "GameButton.h"
#include "GameScenes/ScenePlayLogicServer.h"
#include "World/Maze/Item/Bat.h"
#include "GUI.h"

SceneResult::SceneResult(): Scene()
{
	GetCanvas().Insert(1, GUI::GetInstance()->GetBackground()._tile);



	auto shader = ResourceManagers::GetInstance()->GetShader("TextShader");
	std::shared_ptr<Font> origicide = ResourceManagers::GetInstance()->GetFont("Origicide.ttf");


	_textResult = std::make_shared<Text>(shader, origicide, "", TextColor::RED, 1);
	_textResult->Set2DPosition(Vector2(Globals::screenWidth / 2 - 50, Globals::screenHeight / 5));
	GetCanvas2()[3].push_back(_textResult);


	// Some bats to adorn the credit scene
	auto bat = GUI::GetInstance()->GetMisc()._bat;
	bat->SetPosition(Vector2(Globals::screenWidth / 2 - 95, Globals::screenHeight / 5));
	GetCanvas().Insert(2, bat->Clone());

	bat->SetPosition(Vector2(Globals::screenWidth / 2 + 85, Globals::screenHeight / 5));
	GetCanvas().Insert(2, bat->Clone());


	std::shared_ptr<Font> arialbd = ResourceManagers::GetInstance()->GetFont("arialbd.ttf");
	auto retryTxt = std::make_shared<Text>(shader, arialbd, "Retry?", TextColor::WHITE, 0.7, TextAlign::CENTER);
	retryTxt->Set2DPosition(Vector2(Globals::screenWidth / 2 - 30, Globals::screenHeight / 3));
	GetCanvas2()[3].push_back(retryTxt);



	auto retryDoor = std::make_shared<GameButton>(ResourceManagers::GetInstance()->GetTexture("DoorClose.tga"));
	retryDoor->SetTexture(ResourceManagers::GetInstance()->GetTexture("DoorOpen.tga"), GameButton::Hover::H_ON);
	retryDoor->Set2DPosition(Globals::screenWidth / 2, Globals::screenHeight / 2);
	retryDoor->SetSize(200, 200);
	retryDoor->SetOnClick([]() {
		SceneDirector::GetInstance()->PushScene(SCENE_ID::SCENE_PLAY);
		});
	GetCanvas2()[3].push_back(retryDoor);


	GetCanvas2()[3].push_back(GUI::GetInstance()->GetButton()._exit);
	GetCanvas2()[4].push_back(GUI::GetInstance()->GetButton()._credit);
}

void SceneResult::Enter()
{
	std::string result;
	if (ScenePlayLogicServer::GetInstance()->GetGameResult() == ScenePlayLogicServer::Result::WIN)
	{
		result = "You Win";
		SetBackgroundMusic(Music("surface.mp3"));
	}
	else
	{
		result = "You Lose";
		SetBackgroundMusic(Music("snd_challenge.mp"));
	}

	_textResult->SetText(result);

	Scene::Enter();
}

void SceneResult::Exit()
{
	Scene::Exit();
}
