#ifndef AUDIO_PLAYER_H
#define AUDIO_PLAYER_H

#include "Singleton.h"
#include <string>
class Music;


// Finally I understand why I couldn't stop the music from playing
// Interface for AudioPlayers to multi-inherit from 
class AudioPlayer
{
public:
	//virtual std::string Name() = 0;

	virtual void Play(Music song) = 0;
	virtual void Stop(Music song) = 0;
};


class AudioPlayerOn : 
	public AudioPlayer, 
	public CSingleton<AudioPlayerOn>
{
public:
	//virtual std::string Name() { return "AudioPlayer"; }

	virtual void Play(Music song) override;
	virtual void Stop(Music song) override;
};

class AudioPlayerMuted: 
	public AudioPlayer,
	public CSingleton<AudioPlayerMuted>
{
public:

	//virtual std::string Name() override { return "AudioPlayerMuted"; }

	virtual void Play(Music song) override;
	virtual void Stop(Music song) override;
};

#endif // AUDIO_PLAYER_H