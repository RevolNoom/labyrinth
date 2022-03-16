#pragma once

#ifndef PHYSIC_WORLD_HPP
#define PHYSIC_WORLD_HPP

#include "b2_world.h"
#include <memory>

// A wrapper, global access point
// for Top Down world
class PhysicWorldTD
{
public:
	static std::shared_ptr<b2World> get_instance()
	{
		if (_singleton == nullptr)
			_singleton = std::make_shared<b2World>(0);
		return _singleton;
	}

private:
	static std::shared_ptr<b2World> _singleton;
};
#endif