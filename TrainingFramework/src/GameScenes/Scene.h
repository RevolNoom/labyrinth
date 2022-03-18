#pragma once
#include "SceneDirector.h"
#include "GameManager/ResourceManagers.h"
#include "Canvas.hpp"
#include "Music.hpp"


// PATTERN: PROTOTYPE
// Controlled by SceneDirector
// You create a scene, add some objects to its Canvas
// And then fire it up with Enter()
class Scene
{
public:
	Scene();

	virtual ~Scene();


	Canvas& GetCanvas();


// Rev's Modification:

	// OVERRIDE ME
	// Default behaviors:
	// It's in the Framework. I have no idea what it does
	// Best leave it be
	virtual void Init();


	// OVERRIDE ME
	// Default behaviors:
	// Propagate event to canvas child objects
	// until an object mark this event as handled
	virtual void HandleEvent(std::shared_ptr<InputEvent> ev);


	// OVERRIDE ME
	// Default behaviors:
	// Start Background music
	virtual void Enter();


	// OVERRIDE ME
	// Default behaviors: None
	virtual void Pause();


	// OVERRIDE ME
	// Default behaviors: None
	virtual void Resume();


	// OVERRIDE ME
	// Default behaviors:
	// Stop Background music
	virtual void Exit();


	// OVERRIDE ME
	// Default behaviors:
	// Update all objects on Canvas
	virtual void Update(float delta);


	// OVERRIDE ME
	// Default behaviors: 
	// Draw all objects on Canvas
	virtual void Draw();

	void SetBackgroundMusic(const Music& m);
	Music GetBackgroundMusic();

protected:
	// Rev's Mod:
	// Godot Engine's tree-based structure
	// TODO: What if I want to delete a childObject?
	Canvas _canvas;

	Music _backgroundMusic;
};

