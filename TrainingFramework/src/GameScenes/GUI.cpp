#include "GUI.h"
#include "World/Maze/Item/Bat.h"
#include "ServiceLocator.h"
#include "Scene.h"
#include "SceneDirector.h"

GUI::GUI()
{
	// BACKGROUNDS

    _backgrounds._tile = std::make_shared<SolidObject>(ResourceManagers::GetInstance()->GetTexture("TileBig.tga"));
    _backgrounds._tile->SetPosition(Vector2(Globals::screenWidth / 2, Globals::screenHeight / 2));
    _backgrounds._tile->SetSize(Vector2(Globals::screenWidth, Globals::screenHeight));

	_backgrounds._black = std::make_shared<SolidObject>(ResourceManagers::GetInstance()->GetTexture("BlackBackground.tga"));
	_backgrounds._black->SetPosition(Vector2(Globals::screenWidth / 2, Globals::screenHeight / 2));
	_backgrounds._black->SetSize(Vector2(Globals::screenWidth, Globals::screenHeight));


	// BUTTONS

	
	_buttons._setting = std::make_shared<GameButton>(ResourceManagers::GetInstance()->GetTexture("btn_settings.tga"));
	_buttons._setting->Set2DPosition(Globals::screenWidth - 125, 50);
	_buttons._setting->SetSize(50, 50);
	_buttons._setting->SetOnClick([]() {
		SceneDirector::GetInstance()->PushScene(SCENE_ID::SCENE_SETTING);
		});

	_buttons._credit = std::make_shared<GameButton>(ResourceManagers::GetInstance()->GetTexture("Sign.tga"));
	_buttons._credit->SetTexture(ResourceManagers::GetInstance()->GetTexture("SignGlow.tga"), GameButton::Hover::H_ON);
	_buttons._credit->Set2DPosition(Globals::screenWidth / 2 - 130, Globals::screenHeight / 2 + 50);
	_buttons._credit->SetSize(50, 70);
	_buttons._credit->SetOnClick([]() {
		SceneDirector::GetInstance()->PushScene(SCENE_ID::SCENE_CREDIT);
		});

	_buttons._return = std::make_shared<GameButton>(ResourceManagers::GetInstance()->GetTexture("btn_close.tga"));
	_buttons._return->Set2DPosition(Globals::screenWidth - 50, 50);
	_buttons._return->SetSize(50, 50);
	_buttons._return->SetOnClick([]() {
		SceneDirector::GetInstance()->PopScene();
		});


	_buttons._music = std::make_shared<GameButton>(ResourceManagers::GetInstance()->GetTexture("btn_music.tga"));
	_buttons._music->SetTexture(ResourceManagers::GetInstance()->GetTexture("btn_music.tga"), GameButton::Hover::H_ON, GameButton::Toggle::T_ON);
	_buttons._music->SetTexture(ResourceManagers::GetInstance()->GetTexture("btn_music.tga"), GameButton::Hover::H_OFF, GameButton::Toggle::T_ON);
	_buttons._music->SetTexture(ResourceManagers::GetInstance()->GetTexture("btn_music_off.tga"), GameButton::Hover::H_ON, GameButton::Toggle::T_OFF);
	_buttons._music->SetTexture(ResourceManagers::GetInstance()->GetTexture("btn_music_off.tga"), GameButton::Hover::H_OFF, GameButton::Toggle::T_OFF);
	_buttons._music->EnableToggle(true);
	_buttons._music->Set2DPosition(Globals::screenWidth / 3, Globals::screenHeight / 2);
	_buttons._music->SetSize(50, 50);
	_buttons._music->SetOnClick([&]() {

		auto playingMusic = SceneDirector::GetInstance()->CurrentScene()->GetBackgroundMusic();

		if (_buttons._music->IsToggledOn())
		{
			ServiceLocator::GetInstance()->GetBackgroundMusicPlayer()->Stop(playingMusic);
			ServiceLocator::GetInstance()->SetBackgroundMusicPlayer(AudioPlayerMuted::GetInstance());
		}
		else
		{
			ServiceLocator::GetInstance()->SetBackgroundMusicPlayer(AudioPlayerOn::GetInstance());
			ServiceLocator::GetInstance()->GetBackgroundMusicPlayer()->Play(playingMusic);
		}
		//std::cout << "BGM changed: " << ServiceLocator::GetInstance()->GetBackgroundMusicPlayer()->Name();
	}
	);


	_buttons._exit = std::make_shared<GameButton>(ResourceManagers::GetInstance()->GetTexture("btn_close.tga"));
	_buttons._exit->Set2DPosition(Globals::screenWidth - 50, 50);
	_buttons._exit->SetSize(50, 50);
	_buttons._exit->SetOnClick([]() {
		exit(0);
		});


	_buttons._sfx = std::make_shared<GameButton>(ResourceManagers::GetInstance()->GetTexture("btn_sfx.tga"));
	_buttons._sfx->SetTexture(ResourceManagers::GetInstance()->GetTexture("btn_sfx.tga"), GameButton::Hover::H_ON, GameButton::Toggle::T_ON);
	_buttons._sfx->SetTexture(ResourceManagers::GetInstance()->GetTexture("btn_sfx.tga"), GameButton::Hover::H_OFF, GameButton::Toggle::T_ON);
	_buttons._sfx->SetTexture(ResourceManagers::GetInstance()->GetTexture("btn_sfx_off.tga"), GameButton::Hover::H_ON, GameButton::Toggle::T_OFF);
	_buttons._sfx->SetTexture(ResourceManagers::GetInstance()->GetTexture("btn_sfx_off.tga"), GameButton::Hover::H_OFF, GameButton::Toggle::T_OFF);
	_buttons._sfx->EnableToggle(true);
	_buttons._sfx->Set2DPosition(Globals::screenWidth * 2 / 3, Globals::screenHeight / 2);
	_buttons._sfx->SetSize(50, 50);
	_buttons._sfx->SetOnClick([&]() {
		if (_buttons._sfx->IsToggledOn())
			ServiceLocator::GetInstance()->SetSoundEffectAudioPlayer(AudioPlayerMuted::GetInstance());
		else
			ServiceLocator::GetInstance()->SetSoundEffectAudioPlayer(AudioPlayerOn::GetInstance());
		});


	// MISCS

	_miscs._bat = std::make_shared<Bat>();
	_miscs._bat->SetSize(Vector2(60, 60));


}

GUI::Backgrounds GUI::GetBackground()
{
    return _backgrounds;
}


GUI::Buttons GUI::GetButton()
{
	return _buttons;
}


GUI::Miscs GUI::GetMisc()
{
    return _miscs;
}