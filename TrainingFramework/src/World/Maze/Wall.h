#pragma once
#include "World/PhysicObject.hpp"
#include "Sprite2D.h"

class Wall :
    public PhysicObject,
    public Sprite2D
{
public:
    Wall(std::shared_ptr<Texture> texture);

    virtual void RegisterToWorld(b2World* world) override;
    virtual void SetEnable(bool enable) override;
    // Debugg
    //b2Body* body() { return _body; }

private:
    b2Body* _body;
};

