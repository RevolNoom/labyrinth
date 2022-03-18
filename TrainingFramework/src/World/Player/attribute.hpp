#ifndef ATTRIBUTE_HPP
#define ATTRIBUTE_HPP

using Int = int;

class Attribute
{
public:
	Attribute() : _value(0), _max(0)
	{}

	Attribute(int value, int max) : _value(value), _max(max)
	{}


	Int Max();
	Int Value();


	// Increase current value by @amount
	void Increase(Int amount);
	// Reduce current value by @amount
	void Decrease(Int amount);


	// Increase maximum capacity by @amount
	// Can't go below 0
	void Grow(Int amount);
	// Decrease maximum capacity by @amount
	// Can't go below 0
	void Shrink(Int amount);

private:
	Int _value;
	Int _max;
};


// Dumb data holder, store the attributes
// of an Unit
class SetAttribute
{
public:
	Attribute health;
	Attribute speed;
	// more attributes down here
};

#endif /* ATTRIBUTE_HPP */