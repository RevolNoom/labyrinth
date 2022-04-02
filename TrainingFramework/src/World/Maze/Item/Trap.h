#ifndef TRAP_H
#define TRAP_H

#include "World/SolidObject.h"

class Trap :
	public SolidObject
{
public:
	Trap(std::shared_ptr<Texture> txtr);

	virtual void RegisterToWorld(b2World* world) override;

	// Called in b2ContactListener
	virtual void Trigger() = 0;
};

#endif // TRAP_H