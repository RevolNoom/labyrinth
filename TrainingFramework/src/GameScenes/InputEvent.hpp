#ifndef INPUT_EVENT_HPP
#define INPUT_EVENT_HPP

#include <utilities.h>
#include <memory>
class BaseObject;
class PhysicObject;
class Scene;

// Simulation of Godot Engine InputEvent
// Rev's Modification: Visitor Pattern
// for GameScene (formerly GameScene), and BaseObject

class InputEvent
{
public:
	virtual ~InputEvent() {};
	virtual bool HandledBy(std::shared_ptr<BaseObject> obj) const = 0;
	virtual bool HandledBy(std::shared_ptr<PhysicObject> obj) const = 0;

};


class InputEventKeyPress: public InputEvent
{
public:
	InputEventKeyPress(int key, bool isPressed):
		_key(key), _isPressed(isPressed)
	{}

	virtual bool HandledBy(std::shared_ptr<BaseObject> obj) const override;
	virtual bool HandledBy(std::shared_ptr<PhysicObject> obj) const override;

	bool IsPressed() const {return _isPressed;}
	unsigned int Key() const {return _key;}
private:
	unsigned int _key;
	bool _isPressed;
};

class InputEventMouse : public InputEvent
{
public:
	InputEventMouse(Vector2 position) :
		_pos(position)
	{}

	virtual bool HandledBy(std::shared_ptr<BaseObject> obj) const = 0;
	virtual bool HandledBy(std::shared_ptr<PhysicObject> obj) const = 0;

	Vector2 GetPosition() const { return _pos; }
private:
	Vector2 _pos;

};

class InputEventMouseClick: public InputEventMouse
{
public:
	InputEventMouseClick(Vector2 position, bool IsPressed):
		InputEventMouse(position),
		_isPressed(IsPressed)
	{}

	virtual bool HandledBy(std::shared_ptr<BaseObject> obj) const override;
	virtual bool HandledBy(std::shared_ptr<PhysicObject> obj) const override;

	bool IsPressed() const {return _isPressed;}

private:
	bool _isPressed;
};


class InputEventMouseMotion: public InputEventMouse
{
public:
	InputEventMouseMotion(Vector2 position): InputEventMouse(position)
	{}

	virtual bool HandledBy(std::shared_ptr<BaseObject> obj) const override;
	virtual bool HandledBy(std::shared_ptr<PhysicObject> obj) const override;
};
#endif /* INPUT_EVENT_HPP */

