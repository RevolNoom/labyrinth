#ifndef SENSOR_LISTENER_H
#define SENSOR_LISTENER_H

#include "box2d/b2_world_callbacks.h"
#include <box2d/b2_contact.h>
#include "World/Maze/Item/TransPlatform.h"

class Unit;

class SensorListener :
    public b2ContactListener
{
private:
    template <typename T>
    T* ConvertTo(const b2Body* f)
    {
        if (f == nullptr)
            return nullptr;
        return dynamic_cast<T*>(reinterpret_cast<PhysicObject*>(f->GetUserData().pointer));
    }

    // This one provides better contact listening
    // But b2Contact::Destroy() has to destroy all the fun.
    virtual void BeginContact(b2Contact* contact) override
    {
        if (contact)
        {
            b2Fixture* fixture[2];
            fixture[0] = contact->GetFixtureA();
            fixture[1] = contact->GetFixtureB();
           
            for (int iii=0; iii<2; ++iii)
            {
                Trap* body;
                body = ConvertTo<Trap>(fixture[iii]->GetBody());
                if (body)
                {
                    //std::cout << "Doin nothin\n";
                    body->Trigger();
                }
            }
           
        }
    }


    // Swap layout of the maze 
    // when a TransPlatform is stepped on
    // TODO: Buggy contact reporting, but much more stable than BeginContact()
        /*
	void PostSolve(b2Contact* contact, const b2ContactImpulse* impulse) override
	{
        B2_NOT_USED(impulse);
        //try
        {
            for (b2Contact* it = contact; it != nullptr; it = it->GetNext())
            {
                Trap* tp;
                if (tp = IsATrap(it->GetFixtureA()))
                    tp->Trigger();
                else if (tp = IsATrap(it->GetFixtureB()))
                    tp->Trigger();
            }
        }
        //catch (std::exception& e)
        //{
         //   std::cout << "I have no fkin idea why it throws: "<<e.what()<<". And I don't care.\n";
        //}
}*/

//private:
    

};

#endif
