#pragma once
#include "GameManager/Singleton.h"
#include "GameConfig.h"
#include <list>
#include <map>
#include "InputEvent.hpp"

class Scene;

using SCENE__ID = int;
enum SCENE_ID
{
	SCENE_INVALID = 0,
	SCENE_INTRO,
	SCENE_MENU,
	SCENE_PLAY
};

class SceneDirector : public CSingleton<SceneDirector>
{
public:

	SceneDirector();
	~SceneDirector();

	void	Cleanup();

	void	PushScene(SCENE__ID id);
	void	PopScene();

	bool	isRunning() { return m_running; }
	void	Quit() { m_running = false; }
	void	Update(float delta);

	void	HandleEvent(std::shared_ptr<InputEvent> ev);

	inline std::shared_ptr<Scene> CurrentScene() const
	{
		return _sceneStack.back();
	}


private:
	void SetupScenes();
	void SetupSceneIntro();
	void SetupSceneMenu();
	void SetupScenePlay();


private:
	std::map <SCENE__ID, std::shared_ptr<Scene>>	_scene;
	std::list < std::shared_ptr<Scene>>	_sceneStack;

	bool	m_running;
	bool	m_fullscreen;
};

