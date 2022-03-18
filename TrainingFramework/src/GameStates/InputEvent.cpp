#include "InputEvent.hpp"
#include "BaseObject.h"
#include "Scene.h"

void InputEventMouseMotion::HandledBy(std::shared_ptr<BaseObject> obj) const
{
	obj->HandleMouseMotion(this);
}

void InputEventMouseMotion::HandledBy(std::shared_ptr<Scene> sc) const
{
	sc->HandleMouseMotion(this);
}


void InputEventMouseClick::HandledBy(std::shared_ptr<BaseObject> obj) const
{
	obj->HandleMouseClick(this);
}

void InputEventMouseClick::HandledBy(std::shared_ptr<Scene> sc) const
{
	sc->HandleMouseClick(this);
}


void InputEventKeyPress::HandledBy(std::shared_ptr<BaseObject> obj) const
{
	obj->HandleKeyPress(this);
}

void InputEventKeyPress::HandledBy(std::shared_ptr<Scene> sc) const
{
	sc->HandleKeyPress(this);
}
