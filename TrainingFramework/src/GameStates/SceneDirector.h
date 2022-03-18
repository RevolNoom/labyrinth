#pragma once
#include "GameManager/Singleton.h"
#include "GameConfig.h"
#include <list>
#include "InputEvent.hpp"

class Scene;

enum class StateType
{
	STATE_INVALID = 0,
	STATE_INTRO,
	STATE_MENU,
	STATE_PLAY
};

class SceneDirector : public CSingleton<SceneDirector>
{
public:
	SceneDirector();
	~SceneDirector();

	void	Cleanup();

	void	ChangeState(std::shared_ptr<Scene> state);
	void	ChangeState(StateType stt);
	void	PushState(StateType stt);
	void	PopState();

	bool	isRunning() { return m_running; }
	void	Quit() { m_running = false; }
	void	PerformStateChange();

	void	HandleEvent(std::shared_ptr<InputEvent> ev);

	inline std::shared_ptr<Scene> CurrentState()const
	{
		return m_pActiveState;
	}

	inline bool NeedsToChangeState()const
	{
		return (m_pNextState != 0);
	}

	inline bool HasState()const
	{
		return m_StateStack.size() > 0;
	}

private:
	std::list < std::shared_ptr<Scene>>	m_StateStack;
	std::shared_ptr<Scene>				m_pActiveState;
	std::shared_ptr<Scene>				m_pNextState;
	bool	m_running;
	bool	m_fullscreen;
};

