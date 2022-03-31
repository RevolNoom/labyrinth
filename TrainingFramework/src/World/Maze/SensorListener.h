#ifndef SENSOR_LISTENER_H
#define SENSOR_LISTENER_H

#include "box2d/b2_world_callbacks.h"
#include <box2d/b2_contact.h>
#include "World/Maze/Item/TransPlatform.h"

class SensorListener :
    public b2ContactListener
{
public:

    // Swap layout of the maze 
    // when a TransPlatform is stepped on
    virtual void BeginContact(b2Contact* contact) override
    {
        b2Fixture* fixtures[]{contact->GetFixtureA(),
                            contact->GetFixtureB() };
        
        for (auto& f : fixtures)
        {
            Trap *tp;
            if (tp = ItsATrap(f))
                tp->Trigger();
        }
    }

    // Three functions below are copied and marked overridden
    // I don't know why, but they seem to avoid me errors
    // of b2Contact* destruction


	virtual void EndContact(b2Contact* contact) override
    { 
        B2_NOT_USED(contact); 
    }

	virtual void PreSolve(b2Contact* contact, const b2Manifold* oldManifold) override
	{
		B2_NOT_USED(contact);
		B2_NOT_USED(oldManifold);
	}

	virtual void PostSolve(b2Contact* contact, const b2ContactImpulse* impulse) override
	{
		B2_NOT_USED(contact);
		B2_NOT_USED(impulse);
	}

private:
    
    Trap* ItsATrap(const b2Fixture* f)
    {
        return reinterpret_cast<Trap*>(f->GetUserData().pointer);
    }
};

#endif
