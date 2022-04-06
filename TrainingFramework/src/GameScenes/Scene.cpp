#include "Scene.h"
#include "GameManager/ServiceLocator.h"

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

	for (auto& layer : _canvas2)
		for (auto& obj : layer.second)
			if (ev->HandledBy(obj))
				break;
}

void Scene::Enter() { ServiceLocator::GetInstance()->GetBackgroundMusicPlayer()->Play(_backgroundMusic); }

void Scene::Pause() { ServiceLocator::GetInstance()->GetBackgroundMusicPlayer()->Stop(_backgroundMusic); }

void Scene::Resume() { ServiceLocator::GetInstance()->GetBackgroundMusicPlayer()->Play(_backgroundMusic); }

void Scene::Exit() { ServiceLocator::GetInstance()->GetBackgroundMusicPlayer()->Stop(_backgroundMusic); }


void Scene::Update(float delta)
{
	for (auto &obj : _canvas.GetAll())
		obj->Update(delta); 
	
	for (auto& layer : _canvas2)
		for (auto& obj : layer.second)
			obj->Update(delta);
}

void Scene::Draw()
{
	_canvas.Draw();
	for (auto& layer : _canvas2)
		for (auto& obj : layer.second)
			obj->Draw();
	
}

void Scene::SetBackgroundMusic(const Music& m) { _backgroundMusic = m; }
Music Scene::GetBackgroundMusic() { return _backgroundMusic; }
