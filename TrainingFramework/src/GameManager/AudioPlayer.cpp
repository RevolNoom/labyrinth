#include "AudioPlayer.h"
#include "GameScenes/Music.hpp"
#include "ResourceManagers.h"

void AudioPlayer::Play(Music song)
{
	if (song.GetSongName() != "")
		ResourceManagers::GetInstance()->PlaySound(song.GetSongName());
}

void AudioPlayer::Stop(Music song)
{
	if (song.GetSongName() != "")
		ResourceManagers::GetInstance()->StopSound(song.GetSongName());
}

void AudioPlayerMuted::Play(Music song)
{
}

void AudioPlayerMuted::Stop(Music song)
{
}
