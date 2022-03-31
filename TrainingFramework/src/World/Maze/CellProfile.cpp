#include "CellProfile.h"

CellProfile::CellProfile() : CellProfile(ALLWALL | ENABLED)
{}

CellProfile::CellProfile(int directions) : _wallBit(directions)
{}

bool CellProfile::HasWalls(Bit w) const
{
	return (_wallBit & ALLWALL & w) == w;
}

void CellProfile::SetWalls(Bit w)
{
	RemoveWalls(ALLWALL);
	AddWalls(w);
}

void CellProfile::AddWalls(Bit w)
{
	_wallBit |= w;
}

void CellProfile::RemoveWalls(Bit w)
{
	_wallBit &= (~w);
}

bool CellProfile::IsEnabled() const
{
	return _wallBit & ENABLED;
}

void CellProfile::SetEnabled(bool enabled)
{
	if (enabled)
		_wallBit |= ENABLED;
	else
		_wallBit &= ~ENABLED;
}
