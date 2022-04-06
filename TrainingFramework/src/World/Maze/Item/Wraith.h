#ifndef GHOST_H
#define GHOST_H

#include "Bat.h"

class Wraith :
    public Bat
{
public:
	Wraith();

	virtual std::shared_ptr<PhysicObject> Clone() override;

	virtual void Update(float delta) override;

private:
	void ChasePlayer();
};

#endif // GHOST_H