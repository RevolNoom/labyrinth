#pragma once
#include "Trap.h"

class Prize :
    public Trap
{
public:
	Prize();

	virtual void Draw() override;

	// Called in b2ContactListener
	virtual void Trigger() override;
	virtual std::shared_ptr<PhysicObject> Clone() override;
};

