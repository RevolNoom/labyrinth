#include "AudioPlayer.h"
#include "GameScenes/Music.hpp"
#include "ResourceManagers.h"

void AudioPlayerOn::Play(Music song)
{
	if (song.GetSongName() != "")
		ResourceManagers::GetInstance()->PlaySound(song.GetSongName());
}

void AudioPlayerOn::Stop(Music song)
{
	if (song.GetSongName() != "")
		ResourceManagers::GetInstance()->StopSound(song.GetSongName());
}

void AudioPlayerMuted::Play(Music song)
{
	//std::cout << "Play muted\n";
}

void AudioPlayerMuted::Stop(Music song)
{
	//std::cout << "Stop muted\n";
}
