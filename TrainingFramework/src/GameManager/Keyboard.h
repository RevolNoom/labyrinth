#ifndef KEYBOARD_H
#define KEYBOARD_H

#include "Singleton.h"
#include "GameScenes/InputEvent.hpp"
#include <vector>

class Keyboard :
    public CSingleton<Keyboard>
{
public:
    Keyboard();
    void HandleKeyPress(const InputEventKeyPress* ev);
    bool IsPressing(int key);

private:
    std::vector<int> _isPressingKey;
};

#endif // KEYBOARD_H