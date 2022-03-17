#pragma once
#include "GameStateMachine.h"
#include "GameManager/ResourceManagers.h"
#include "Canvas.hpp"


class GameStateBase
{
public:
	GameStateBase() : m_stateType(StateType::STATE_INVALID){}
	GameStateBase(StateType stateType);
	virtual ~GameStateBase() {}

	virtual void Init() = 0;
	virtual void Exit() = 0;

	virtual void Pause() = 0;
	virtual void Resume() = 0;

	virtual void HandleEvents() = 0;
	virtual void HandleKeyEvents(int key, bool bIsPressed) = 0;
	virtual void HandleTouchEvents(int x, int y, bool bIsPressed) = 0;
	virtual void HandleMouseMoveEvents(int x, int y) = 0;

// Rev's Modification:
// OVERRIDE MEEEEEEEE
// Provide default behaviours to objects that are 
// user-added

	virtual void Update(float deltaTime) = 0;

	virtual void Draw()
	{
		// Call the overridden behaviours
		this->Draw();

		// Default:
		_canvas.Draw();
	}

	static std::shared_ptr<GameStateBase> CreateState(StateType stt);
	StateType GetGameStateType();

protected:
	StateType m_stateType;

	// Rev's Mod:
	// Godot Engine's tree-based structure
	// TODO: What if I want to delete a childObject?
	Canvas _canvas;

};

