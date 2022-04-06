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

	std::string GetSongName() { return _song; }
private:
	std::string _song;
};

#endif /* MUSIC_HPP */
