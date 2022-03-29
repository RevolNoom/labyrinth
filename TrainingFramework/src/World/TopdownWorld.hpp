#pragma once

#ifndef TOPDOWN_WORLD_HPP
#define TOPDOWN_WORLD_HPP

#include "box2d/b2_world.h"
#include <memory>

// A wrapper, global access point
// for Top Down world
class TopdownWorld
{
public:
	static b2World* get_instance()
	{
		if (_singleton == nullptr)
			_singleton = new b2World(b2Vec2(0, 0));
		return _singleton;
	}

	void Update(float delta)
	{
	}
private:
	static b2World* _singleton ;
};


#endif /* TOPDOWN_WORLD_HPP */