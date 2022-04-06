#ifndef SERVICE_LOCATOR_H
#define SERVICE_LOCATOR_H

#include "Singleton.h"
#include "GameManager/AudioPlayer.h"

// Service Locator Pattern
// 
// Provide a global access point for services 
// such as sound, ambiance, scene tree,... ?
// 
// Well, it's a singleton, so it might be bad. 
// But I'm pretty sure a global access point
// for sound is ok.
class ServiceLocator : public CSingleton<ServiceLocator>
{
public:
	// Putting ServiceLocator() here cringes me so much
	// But something in Microsoft's xutility file
	// don't allow me to lock this into private
	ServiceLocator();

	void SetBackgroundMusicPlayer(std::shared_ptr<AudioPlayer> bgm);
	std::shared_ptr<AudioPlayer> GetBackgroundMusicPlayer();
	
	void SetSoundEffectAudioPlayer(std::shared_ptr<AudioPlayer> se);
	std::shared_ptr<AudioPlayer> GetSoundEffectAudioPlayer();

private:

	std::shared_ptr<AudioPlayer> _backgroundMusic;
	std::shared_ptr<AudioPlayer> _soundEffect;
};

#endif