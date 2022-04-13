#pragma once
#include "Singleton.h"
#include "World/PhysicObject.h"
#include "GameButton.h"

// Shares UI components between scenes
// Kills a bit of code. 
// The good point is I can reuse them across scenes
// Downside is that moving one thing cascades to another.
// I don't move them, anyway
class GUI :
    public CSingleton<GUI>
{
public:
    GUI();

    struct Backgrounds
    {
        std::shared_ptr<PhysicObject>
            _black,
            _tile;
    };

    struct Buttons
    {
        std::shared_ptr<GameButton> 
            _setting,
            _credit,
            _return,
            _music,
            _exit,
            _sfx;
    };

    struct Miscs
    {
        std::shared_ptr<PhysicObject>
            _bat;
        std::shared_ptr<Text>
            _music, _sfx;
    };

    Backgrounds GetBackground();
    Buttons GetButton();
    Miscs GetMisc();

private:
     Backgrounds _backgrounds;
     Buttons _buttons;
     Miscs _miscs;
};

