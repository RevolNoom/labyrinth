#ifndef ESCAPE_H
#define ESCAPE_H

#include "World/Maze/Item/Trap.h"

class ExitStair :
    public Trap
{
public:
	ExitStair();

	virtual void Draw() override;

	// Called in b2ContactListener
	virtual void Trigger() override;

	// Called after LogicServer found out that 
	// the ring is picked up
	void EnableExit();

	// ...
	void Escaped();


	virtual std::shared_ptr<PhysicObject> Clone() override;

private:
	bool _enableExit;
};

#endif