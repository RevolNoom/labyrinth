#ifndef MUSIC_HPP
#define MUSIC_HPP

#include <string>
#include "GameManager/ResourceManagers.h"

class Music
{
public:
	Music(){}
	Music(std::string songName): _song(songName), _isPlaying(false)
	{}

	~Music()
	{
		// Should I?
		//Stop();
	}

	void Play()
	{
		if (_song != "" && !_isPlaying)
		{
			_isPlaying = true;
			ResourceManagers::GetInstance()->PlaySound(_song);
		}
	}

	void Stop()
	{
		if (_isPlaying && _song != "")
		{
			_isPlaying = false;
			ResourceManagers::GetInstance()->StopSound(_song);
		}
	}

private:
	std::string _song;
	bool _isPlaying;
};

#endif /* MUSIC_HPP */
