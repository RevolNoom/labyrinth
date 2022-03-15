using Int = signed int32_t;

class Attribute
{
public:
	Int max();
	Int value();

	// Increase current value by @amount
	Int Increase(Int amount);
	// Reduce current value by @amount
	Int Decrease(Int amount);


	// Increase maximum capacity by @amount
	// Can't go below 0
	Int Grow(Int amount);
	// Decrease maximum capacity by @amount
	// Can't go below 0
	Int Shrink(Int amount);

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
