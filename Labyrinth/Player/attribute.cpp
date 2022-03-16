#include "attribute.hpp"
#include <algorithm>

Int Attribute::max()
{
	return _max;
}


Int Attribute::value()
{
	return _value;
}


void Attribute::Increase(Int amount)
{
	_value = std::clamp(_value + amount, 0, _max);
}


void Attribute::Decrease(Int amount)
{
	Increase(-amount);
}


void Attribute::Grow(Int amount)
{
	_max += amount;
	if _max < 0
		_max = 0;
}


void Attribute::Shrink(Int amount)
{
	Grow(-amount);
}
