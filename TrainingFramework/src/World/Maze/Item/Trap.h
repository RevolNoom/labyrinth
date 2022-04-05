#ifndef TRAP_H
#define TRAP_H

#include "World/SolidObject.h"

// TODO: No, Trap should be a separate interface
// But I've almost finished my project to go back fixing it at this point
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