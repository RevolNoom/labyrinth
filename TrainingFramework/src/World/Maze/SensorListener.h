#ifndef SENSOR_LISTENER_H
#define SENSOR_LISTENER_H

#include "box2d/b2_world_callbacks.h"
#include <box2d/b2_contact.h>
#include "World/Maze/Item/TransPlatform.h"

class SensorListener :
    public b2ContactListener
{
public:
    
    SensorListener() {}

    virtual ~SensorListener() {}

    // Swap layout of the maze 
    // when a TransPlatform is stepped on
    // TODO: Buggy contact reporting, but much more stable than BeginContact()
	virtual void PostSolve(b2Contact* contact, const b2ContactImpulse* impulse) override
	{

        for (b2Contact* it = contact; it != nullptr; it = it->GetNext())
        {
            b2Fixture* fixtures[] = { it->GetFixtureA(),
                                    it->GetFixtureB() };
            for (auto f : fixtures)
            {
                Trap* tp;
                if (tp = IsATrap(f))
                    tp->Trigger();
            }
        }

        B2_NOT_USED(impulse);
	}

private:
    
    Trap* IsATrap(const b2Fixture* f)
    {
        return reinterpret_cast<Trap*>(f->GetUserData().pointer);
    }
};

#endif
