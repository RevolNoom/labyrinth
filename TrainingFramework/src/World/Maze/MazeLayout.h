#ifndef MAZE_LAYOUT_HPP
#define MAZE_LAYOUT_HPP

#include "Cell.h"
#include <vector>

using Coordinate = std::pair<int, int>;

//Contains the layout of cells in a Maze
template<class T>
class MazeLayout
{
public:

	// Create a Maze of width x height
	// Width, height > 0
	MazeLayout(int width, int height);
	explicit MazeLayout(Coordinate size);

	//void Draw();

	// Return the wall organization of this cell
	// with O at the Top Left corner
	T& GetCell(Coordinate c);

	// Return the wall organization of this cell
	// with O at the Top Left corner
	const T& GetCell(Coordinate c) const;

	// Return <width, height>
	Coordinate GetSize() const;

	// Return width*height
	int GetCellAmount() const;

	// Shuffle the content of this layout
	void Shuffle();



	// An iterator to iterate the maze layout.
	// TODO: DO NOT USE THIS ITERATOR TO MODIFY MAZE LAYOUT
	// It has bugs
	class Iterator
	{
	public:
		// Return the next element, and increment the iterator
		T& Next();
		bool HasNext();
		
		// Return the coordinate of the next element
		// The coordinate is invalid if there's no HasNext()
		Coordinate NextPosition();

	private:
		friend class MazeLayout<T>;
		Iterator(MazeLayout<T>* source);

		Coordinate _nextPos;
		Coordinate _dims;
		MazeLayout<T>* _source;
	};


	Iterator GetIterator();

private:

	Vector2 _pos;
	Coordinate _size;
	std::vector<T> _layout;
}; 

#include "MazeLayout.hpp"

#endif /* MAZE_LAYOUT_HPP */
