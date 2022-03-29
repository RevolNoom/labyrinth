#pragma once
#include "Scene.h"
#include "World/Maze/Maze.hpp"
#include "World/Player/Unit.hpp"

class ScenePlay :
    public Scene
{
public:
    ScenePlay();

    virtual void Update(float delta) override;

};

