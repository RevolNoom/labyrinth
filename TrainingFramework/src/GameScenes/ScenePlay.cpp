#include "ScenePlay.h"
#include "GameButton.h"
#include "World/Player/Unit.hpp"
#include "World/Maze/Maze.hpp"
#include "GameScenes/ScenePlayLogicServer.h"

// Screen: 480 x 800
ScenePlay::ScenePlay() : Scene(), _gameWorld(b2Vec2(0, 0)), _trapSensor(nullptr)
{
	std::cout << "Scene Play Initializing\n";
	SetUpGameWorld();

	//auto maze = std::make_shared<Maze>(12, 20);
	auto maze = std::make_shared<Maze>(4, 8);
	maze->SetPosition(Vector2(Globals::screenWidth/2, Globals::screenHeight/2));
	maze->SetCellSize(Vector2(40, 40));
	maze->RegisterToWorld(&_gameWorld);
	GetCanvas().Insert(5, maze);
	

	auto unit = std::make_shared<Unit>();
	unit->SetPosition(Vector2(10, 10));
	unit->SetSize(Vector2(20, 20));
	unit->RegisterToWorld(&_gameWorld);
	GetCanvas().Insert(7, unit);
}

ScenePlay::~ScenePlay()
{
}

void ScenePlay::Update(float delta)
{
	// Although they said delta should not vary,
	// I don't have the luxury of rewriting more of the framework.
	_gameWorld.Step(delta, 12, 5);
	Scene::Update(delta);
}

void ScenePlay::WinGame()
{
	Pause();
	std::cout << "Yay";
}

void ScenePlay::SetUpGameWorld()
{
	_trapSensor = new SensorListener();
	_gameWorld.SetContactListener(_trapSensor);

	ScenePlayLogicServer::GetInstance()->SetUpScenePlay(this);
}
