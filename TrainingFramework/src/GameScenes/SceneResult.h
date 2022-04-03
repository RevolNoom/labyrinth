#ifndef SCENE_RESULT_H
#define SCENE_RESULT_H

#include "Scene.h"

class SceneResult :
    public Scene
{
public:
    SceneResult();

	// OVERRIDE ME
	// Default behaviors:
	// Start Background music
	virtual void Enter() override;
};

#endif // SCENE_RESULT_H