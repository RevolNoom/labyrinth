#pragma once
#include "SceneDirector.h"
#include "GameManager/ResourceManagers.h"
#include "Canvas.hpp"


class Scene
{
public:
	Scene() : m_stateType(StateType::STATE_INVALID){}
	Scene(StateType stateType);
	virtual ~Scene() {}

	virtual void Init() = 0;
	virtual void Exit() = 0;

	virtual void Pause() = 0;
	virtual void Resume() = 0;

	virtual void HandleEvents() = 0;


// Rev's Modification:
// OVERRIDE MEEEEEEEE
// Provide default behaviours to objects that are 
// user-added

	// OVERRIDE ME
	virtual void HandleKeyPress(const InputEventKeyPress* ev) {}

	// OVERRIDE ME
	virtual void HandleMouseClick(const InputEventMouseClick* ev) {}

	// OVERRIDE ME
	virtual void HandleMouseMotion(const InputEventMouseMotion* ev) {}


	virtual void Update(float deltaTime) = 0;

	virtual void Draw()
	{
		// Call the overridden behaviours
		this->Draw();

		// Default:
		_canvas.Draw();
	}

	static std::shared_ptr<Scene> CreateState(StateType stt);
	StateType GetGameStateType();

protected:
	StateType m_stateType;

	// Rev's Mod:
	// Godot Engine's tree-based structure
	// TODO: What if I want to delete a childObject?
	Canvas _canvas;

};

