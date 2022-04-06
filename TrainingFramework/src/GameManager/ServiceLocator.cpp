#include "ServiceLocator.h"

ServiceLocator::ServiceLocator(): 
	_backgroundMusic(AudioPlayer::GetInstance()),
	_soundEffect(AudioPlayer::GetInstance())
{
}

void ServiceLocator::SetBackgroundMusicPlayer(std::shared_ptr<AudioPlayer> bgm)
{
	_backgroundMusic = bgm;
}
std::shared_ptr<AudioPlayer> ServiceLocator::GetBackgroundMusicPlayer()
{ 
	return _backgroundMusic;
}

void ServiceLocator::SetSoundEffectAudioPlayer(std::shared_ptr<AudioPlayer> se)
{ 
	_soundEffect = se; 
}

std::shared_ptr<AudioPlayer> ServiceLocator::GetSoundEffectAudioPlayer()
{
	return _soundEffect; 
}