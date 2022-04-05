#pragma once
#include "Scene.h"
#include "World/Maze/Maze.hpp"
#include "World/Player/Unit.hpp"
#include "World/Maze/SensorListener.h"
#include "box2d/b2_world.h"

class ScenePlay :
    public Scene
{
public:
    ScenePlay();
    virtual ~ScenePlay();

    virtual void Update(float delta) override;

    // Called by LogicServer to flag that
    // the game has had a result
    virtual void DonePlaying();
    
    virtual void Pause() override;

    virtual void Resume() override;

    virtual void Enter() override;

    virtual void Exit() override;

private:
    virtual void HandleEvent(std::shared_ptr<InputEvent> ev) override;
    // Deal with b2 sensors
    void SetUpGameWorld();

    b2World *_gameWorld;
    SensorListener _trapSensor;

    enum class State
    {
        RUNNING = 0,
        PAUSE,
        STOP,
        WAIT_FOR_CLEANUP,
    };
    State _state;
};

