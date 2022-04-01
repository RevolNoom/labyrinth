#pragma once

#ifndef CELL_PROFILE_H
#define CELL_PROFILE_H

class CellProfile
{
public:
	enum Bit
	{
		// BITS
		W = 0x1,
		N = 0x2,
		E = 0x4,
		S = 0x8,

		NO_WALL = 0x0,
		ALLWALL = 0xF,

		ENABLED = 0x10
	};

	CellProfile();

	CellProfile(int directions);

	// TODO: This is Debugging value
	// Destroy after done
	int Value() { return _wallBit; }

	bool HasWalls(Bit w) const;
	void SetWalls(Bit w);
	void AddWalls(Bit w);
	void RemoveWalls(Bit w);

protected:
	friend class Cell;
	bool IsEnabled() const;
	void SetEnabled(bool enabled);

private:
	int _wallBit;
};

#endif // CELL_PROFILE_H