#include <algorithm>
#include <random>

template<class T>
MazeLayout<T>::MazeLayout(int width, int height)
{
	if (width < 1 || height < 1)
	{
		std::string msg = std::string("Invalid matrix dimension: ") + std::to_string(width) + "x" + std::to_string(height);
		std::cout << msg << "\n";
		throw std::exception(msg.c_str());
	}
	_size = { width, height };
	
	_layout.resize(width * height);
}

template<class T>
MazeLayout<T>::MazeLayout(Coordinate size) : MazeLayout(size.first, size.second)
{
}


template<class T>
T& MazeLayout<T>::GetCell(Coordinate c)
{
	return _layout[_size.first * c.second + c.first];
}

template<class T>
const T& MazeLayout<T>::GetCell(Coordinate c) const
{
	return _layout[_size.first * c.second + c.first];
}

template<class T>
Coordinate MazeLayout<T>::GetSize() const
{
	return _size;
}

template<class T>
int MazeLayout<T>::GetCellAmount() const
{
	return _size.first * _size.second;
}

template<class T>
void MazeLayout<T>::Shuffle()
{
	std::shuffle(_layout.begin(), _layout.end(), std::mt19937_64{static_cast<unsigned int>(std::rand())});
}

template<class T>
typename MazeLayout<T>::Iterator MazeLayout<T>::GetIterator()
{
	return Iterator(this);
}

template<class T>
MazeLayout<T>::Iterator::Iterator(MazeLayout<T>* source) : 
	_source(source),
	_nextPos(Coordinate{ 0, 0 }),
	_dims(source->GetSize())
{
}

template<class T>
inline T& MazeLayout<T>::Iterator::Next()
{
	auto result = _source->GetCell(_nextPos);
	_nextPos = NextPosition();
	return result;
}

template<class T>
inline bool MazeLayout<T>::Iterator::HasNext()
{
	auto next = NextPosition();
	return next.first < _dims.first && next.second < _dims.second;
}

template<class T>
Coordinate MazeLayout<T>::Iterator::NextPosition()
{
	Coordinate next(_nextPos);
	++next.first;
	if (next.first >= _dims.first)
	{
		next.first = 0;
		++next.second;
	}
	return next;
}
