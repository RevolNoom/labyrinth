#ifndef SP_LOGIC_SERVER_H
#define SP_LOGIC_SERVER_H

#include "GameManager/Singleton.h"
#include "World/Maze/Item/Prize.h"
#include "World/Maze/Item/ExitStair.h"
#include "GameScenes/ScenePlay.h"

// Putting Logic server out into the open might not be the best idea
// But I'm so tired with bugs. I just want to get the job done already
class ScenePlayLogicServer: public CSingleton<ScenePlayLogicServer>
{
public:
	// The Prize object will register to logic server through here 
	// when it's constructed 
	void SetUpPrize(Prize *prize);
	// Called by Prize::Trigger() when the player touch it
	void PickUpPrize();

	// The Escape object will register to logic server through here 
	// when it's constructed 
	void SetUpExitStair(ExitStair* escape);

	// TODO: Die() and EscapeMaze() seems identical
	// Refactor them?

	// Called by ExitStair::Trigger() when the player touch it
	void EscapeMaze();

	// Called by whatever dangerous carnivorous creatures/traps
	// That touch the the player
	void Die();

	void SetUpScenePlay(ScenePlay* sp);

	void StartPlaying();


	enum class Result
	{
		WIN,
		LOSE
	};
	Result GetGameResult();

private:
	Prize * _prize; 
	ExitStair* _escape;
	ScenePlay* _scenePlay;
	Result _result;
};

#endif