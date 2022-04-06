#include "Keyboard.h"

Keyboard::Keyboard(): _isPressingKey(256, 0)
{
    /*
    std::cout << "Keyboard comes alive: ";
    for (auto i : _isPressingKey)
        std::cout << i << " ";
    std::cout << "\n";*/
}

void Keyboard::HandleKeyPress(const InputEventKeyPress* ev)
{
    //std::cout << ev->Key() << (ev->IsPressed() ? " Press" : "Unpress") << "\n";
    _isPressingKey[char(ev->Key())] = ev->IsPressed();
}

bool Keyboard::IsPressing(int key)
{
    //std::cout << (_isPressingKey[key] ? std::string("") : std::string("Not ")) << "Pressed: " << char(key) << "\n";
    return _isPressingKey[key];
}
