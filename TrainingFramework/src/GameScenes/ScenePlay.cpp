#include "ScenePlay.h"
#include "GameButton.h"
#include "World/Player/Unit.hpp"
#include "World/Maze/Maze.hpp"
#include "GameScenes/ScenePlayLogicServer.h"
#include "GUI.h"

// Screen: 480 x 800
ScenePlay::ScenePlay() : Scene(), _gameWorld(nullptr), _trapSensor(), _state(State::PAUSE)
{
	SetBackgroundMusic(Music("game.mp3"));
}

ScenePlay::~ScenePlay()
{
}



void ScenePlay::Update(float delta)
{
	if (_state == State::WAIT_FOR_CLEANUP)
	{
		ScenePlay::Exit();
		SceneDirector::GetInstance()->PushScene(SCENE_ID::SCENE_RESULT);
	}
	else if (_state == State::RUNNING)
	{
		// Although they said delta should not vary,
		// I don't have the luxury of rewriting more of the framework.
		_gameWorld->Step(delta, 8, 3);
		Scene::Update(delta);
	}
}

void ScenePlay::DonePlaying()
{
	// Cut off the stack, so that I don't delete the world
	// while b2Contacts are still in use on stack
	_state = State::WAIT_FOR_CLEANUP;
}


void ScenePlay::Enter()
{
	_state = State::RUNNING;
	Scene::Enter();
	SetUpGameWorld();

	GetCanvas().Insert(1, GUI::GetInstance()->GetBackground()._black);

	//auto maze = std::make_shared<Maze>(12, 20);
	auto maze = std::make_shared<Maze>(10, 6);
	maze->SetPosition(Vector2(Globals::screenWidth / 2, Globals::screenHeight / 2));
	maze->SetCellSize(Vector2(Globals::screenHeight / 6, Globals::screenHeight / 6));
	maze->RegisterToWorld(_gameWorld);
	GetCanvas().Insert(5, maze);


	auto unit = std::make_shared<Unit>();
	unit->SetPosition(maze->GetCellSize()/2);
	unit->SetSize(maze->GetCellSize()/3);
	unit->SetMaxVelocity(maze->GetCellSize() * 3 / 2);
	unit->RegisterToWorld(_gameWorld);
	GetCanvas().Insert(7, unit);
	ScenePlayLogicServer::GetInstance()->SetupPlayer(unit.get());


	ScenePlayLogicServer::GetInstance()->StartPlaying();
}


void ScenePlay::Pause()
{
	_state = State::PAUSE;
	Scene::Pause();
}


void ScenePlay::Resume()
{
	if (_state == State::STOP)
		ScenePlay::Enter();
	else // This line is surplus, but it decouples 
		// Resume() from the logic of Enter()
		_state = State::RUNNING; 
}


void ScenePlay::Exit()
{
	GetCanvas().Clear();

	delete _gameWorld;
	
	Scene::Exit();
}


void ScenePlay::HandleEvent(std::shared_ptr<InputEvent> ev)
{
	if (_state == State::RUNNING)
		Scene::HandleEvent(ev);
}

void ScenePlay::SetUpGameWorld()
{
	_trapSensor = SensorListener();
	_gameWorld = new b2World(b2Vec2(0, 0));
	_gameWorld->SetContactListener(&_trapSensor);

	ScenePlayLogicServer::GetInstance()->SetUpScenePlay(this);
}
