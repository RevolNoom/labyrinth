#ifndef MUSIC_HPP
#define MUSIC_HPP

#include <string>
#include "GameManager/ResourceManagers.h"

class Music
{
public:
	Music(){}
	Music(std::string songName): _song(songName)
	{}

	void Play()
	{
		if (_song != "")
			ResourceManagers::GetInstance()->PlaySound(_song);
	}

	// uhmmm....
	// I don't know how to though...
	void Stop()
	{
	}

private:
	std::string _song;
};

#endif /* MUSIC_HPP */
