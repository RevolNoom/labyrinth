#ifndef AUDIO_PLAYER_H
#define AUDIO_PLAYER_H

#include "Singleton.h"
class Music;

class AudioPlayer : public CSingleton<AudioPlayer>
{
public:
	virtual void Play(Music song);
	virtual void Stop(Music song);
};

class AudioPlayerMuted: public AudioPlayer
{
public:
	virtual void Play(Music song) override;
	virtual void Stop(Music song) override;
};

#endif // AUDIO_PLAYER_H