#include "attribute.hpp"
#include <algorithm>

Int Attribute::Max()
{
	return _max;
}


Int Attribute::Value()
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
	if (_max < 0)
		_max = 0;
	if (_value > _max)
		_value = _max;
}


void Attribute::Shrink(Int amount)
{
	Grow(-amount);
}
