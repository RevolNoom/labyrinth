#ifndef SP_LOGIC_SERVER_H
#define SP_LOGIC_SERVER_H

#include "GameManager/Singleton.h"
#include "World/Maze/Item/Prize.h"
#include "World/Maze/Item/ExitStair.h"
#include "GameScenes/ScenePlay.h"

class Unit;

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


	// TODO: Die() and EscapeMaze() seems identical
	// Refactor them?


	// The Escape object will register to logic server through here 
	// when it's constructed 
	void SetUpExitStair(ExitStair* escape);

	// Called by ExitStair::Trigger() when the player touch it
	void EscapeMaze();


	// Called by whatever dangerous carnivorous creatures/traps
	// That touch the the player
	void Die();

	void SetUpScenePlay(ScenePlay* sp);


	// Setup Player to be chased by the Wraith
	void SetupPlayer(Unit* player);

	// Wraith uses this to chase the player
	Unit* GetPlayer();

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
	Unit* _player;
	Result _result;
};

#endif