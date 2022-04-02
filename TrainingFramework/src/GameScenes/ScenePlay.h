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

    // Called by LogicServer to flag that we win
    virtual void WinGame();

private:
    // Deal with b2 sensors
    void SetUpGameWorld();

    b2World _gameWorld;
    SensorListener *_trapSensor;
};

