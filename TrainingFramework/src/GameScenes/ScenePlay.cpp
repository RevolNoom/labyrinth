#include "ScenePlay.h"
#include "GameButton.h"
#include "World/TopdownWorld.hpp"
#include "World/Player/Unit.hpp"
#include "World/Maze/Maze.hpp"

ScenePlay::ScenePlay(): Scene()
{

	auto maze = std::make_shared<Maze>(3, 3);
	maze->Set2DPosition(Vector2(200, 200));
	maze->RegisterToWorld(TopdownWorld::get_instance());
	GetCanvas().Insert(5, maze);
	_mz = maze;

	auto unit = std::make_shared<Unit>();
	unit->Set2DPosition(Vector2(10, 10));
	unit->RegisterToWorld(TopdownWorld::get_instance());
	
	_u = unit;
	GetCanvas().Insert(6, unit);

}

void ScenePlay::Update(float delta)
{
	// Although they said delta should not vary,
	// I don't have the luxury of rewriting more of the framework.
	TopdownWorld::get_instance()->Step(delta, 6, 2);
	_u->body()->GetPosition();

	// The doc recommends ClearForces(). Idk.
	TopdownWorld::get_instance()->ClearForces();

	Scene::Update(delta);

	//auto p = _mz->GetCell(0, 0).wall()->body()->GetPosition();
	//std::cout << "Corner cell wall: " << p.x << " " << p.y << "\n";
}

void ScenePlay::HandleEvent(std::shared_ptr<InputEvent> ev)
{
	for (auto& obj : _canvas.GetAll())
		if (ev->HandledBy(obj))
			break;
}
