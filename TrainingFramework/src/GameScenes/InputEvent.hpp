#ifndef INPUT_EVENT_HPP
#define INPUT_EVENT_HPP

#include <utilities.h>
#include <memory>
class BaseObject;
class Scene;

// Simulation of Godot Engine InputEvent
// Rev's Modification: Visitor Pattern
// for GameScene (formerly GameScene), and BaseObject

class InputEvent
{
public:
	virtual ~InputEvent() {};
	virtual bool HandledBy(std::shared_ptr<BaseObject> obj) const = 0;

};


class InputEventKeyPress: public InputEvent
{
public:
	InputEventKeyPress(int key, bool isPressed):
		_key(key), _isPressed(isPressed)
	{}

	virtual bool HandledBy(std::shared_ptr<BaseObject> obj) const override;

	bool IsPressed() const {return _isPressed;}
	unsigned int Key() const {return _key;}
private:
	unsigned int _key;
	bool _isPressed;
};


class InputEventMouseClick: public InputEvent
{
public:
	InputEventMouseClick(Vector2 position, bool IsPressed):
		_isPressed(IsPressed), _pos(position)
	{}

	virtual bool HandledBy(std::shared_ptr<BaseObject> obj) const override;

	bool IsPressed() const {return _isPressed;}
	Vector2 GetPosition() const {return _pos;}

private:
	Vector2 _pos;
	bool _isPressed;
};


class InputEventMouseMotion: public InputEvent
{
public:
	InputEventMouseMotion(Vector2 position):
		_pos(position)
	{}

	virtual bool HandledBy(std::shared_ptr<BaseObject> obj) const override;

	Vector2 GetPosition() const {return _pos;}
private:
	Vector2 _pos;

};
#endif /* INPUT_EVENT_HPP */

