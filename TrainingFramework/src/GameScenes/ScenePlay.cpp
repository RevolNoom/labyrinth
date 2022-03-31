#include "ScenePlay.h"
#include "GameButton.h"
#include "World/Player/Unit.hpp"
#include "World/Maze/Maze.hpp"
#include "World/Maze/Item/TransPlatform.h"

ScenePlay::ScenePlay(): Scene(), _gameWorld(b2Vec2(0, 0))
{
	std::cout << "Scene Play Initializing\n";
	SetUpGameWorld();

	auto maze = std::make_shared<Maze>(5, 5);
	maze->SetPosition(Vector2(200, 200));
	maze->SetSize(Vector2(400, 400));
	maze->RegisterToWorld(&_gameWorld);
	GetCanvas().Insert(5, maze);


	auto unit = std::make_shared<Unit>();
	unit->SetPosition(Vector2(10, 10));
	unit->SetSize(Vector2(25, 25));
	unit->RegisterToWorld(&_gameWorld);
	GetCanvas().Insert(7, unit);
	

	auto trap = std::make_shared<TransPlatform>(maze, 3);
	trap->SetPosition(Vector2(50, 0));
	trap->SetSize(Vector2(25, 25));
	trap->RegisterToWorld(&_gameWorld);
	GetCanvas().Insert(6, trap);
}

void ScenePlay::Update(float delta)
{
	// Although they said delta should not vary,
	// I don't have the luxury of rewriting more of the framework.
	_gameWorld.Step(delta, 8, 3);

	Scene::Update(delta);
}

void ScenePlay::SetUpGameWorld()
{
	_dontTouchThis_ItIsFor_gameWorld = SensorListener();
	_gameWorld.SetContactListener(&_dontTouchThis_ItIsFor_gameWorld);
}
