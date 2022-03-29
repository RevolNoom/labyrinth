#include "Scene.h"

Scene::Scene()
{
	// Two-step initiallization?
	// Meh
	Init();
}

Scene::~Scene() {}

Canvas& Scene::GetCanvas() { return _canvas; }

void Scene::Init() {}

void Scene::HandleEvent(std::shared_ptr<InputEvent> ev)
{
	for (auto &obj : _canvas.GetAll())
		if (ev->HandledBy(obj))
			break;
}

void Scene::Enter() { _backgroundMusic.Play(); }

void Scene::Pause() {}

void Scene::Resume() {}

void Scene::Exit() { _backgroundMusic.Stop(); }


void Scene::Update(float delta)
{
	for (auto obj : _canvas.GetAll())
		obj->Update(delta);
}

void Scene::Draw()
{
	_canvas.Draw();
}

void Scene::SetBackgroundMusic(const Music& m) { _backgroundMusic = m; }
Music Scene::GetBackgroundMusic() { return _backgroundMusic; }
