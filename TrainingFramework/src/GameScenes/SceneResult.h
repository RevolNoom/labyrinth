#ifndef SCENE_RESULT_H
#define SCENE_RESULT_H

#include "Scene.h"

class SceneResult :
    public Scene
{
public:
    SceneResult();

	virtual void Enter() override;
	virtual void Exit() override;

private:
	std::shared_ptr<Text> _textResult;
};

#endif // SCENE_RESULT_H