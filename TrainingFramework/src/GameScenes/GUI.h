#pragma once
#include "Singleton.h"
#include "World/PhysicObject.h"
#include "GameButton.h"

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
    };

    Backgrounds GetBackground();
    Buttons GetButton();
    Miscs GetMisc();

private:
     Backgrounds _backgrounds;
     Buttons _buttons;
     Miscs _miscs;
};

