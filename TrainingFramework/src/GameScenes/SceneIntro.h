#pragma once
#include "Scene.h"
#include "SpriteAnimation.h"
#include "GameObject/Timer.h"

class SceneIntro : public Scene
{
public:
	SceneIntro();
	~SceneIntro();
	virtual void Update(float deltaTime) override;
	virtual void Draw() override;

private:
	std::shared_ptr<Text> _rev;
	Timer _timer;
};

