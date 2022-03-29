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
    virtual void HandleEvent(std::shared_ptr<InputEvent> ev) override;

    std::shared_ptr<Maze> _mz;
    std::shared_ptr<Unit> _u;
};

