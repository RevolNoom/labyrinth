#include "InputEvent.hpp"
#include "BaseObject.h"
#include "Scene.h"

bool InputEventMouseMotion::HandledBy(std::shared_ptr<BaseObject> obj) const
{
	return obj->HandleMouseMotion(this);
}

bool InputEventMouseClick::HandledBy(std::shared_ptr<BaseObject> obj) const
{
	return obj->HandleMouseClick(this);
}

bool InputEventKeyPress::HandledBy(std::shared_ptr<BaseObject> obj) const
{
	return obj->HandleKeyPress(this);
}