#pragma once
#include "Scene.h"
#include "SpriteAnimation.h"
#include "GameObject/Timer.h"

class SceneIntro : public Scene
{
public:
	SceneIntro();
	~SceneIntro();
	virtual void Init() override;
	virtual void Update(float deltaTime) override;
	virtual void Draw() override;

private:
	// A bit awkward because I forget to do a 
	// PhysicObject - SpriteAnimation adapter
	std::shared_ptr<SpriteAnimation> _bat;
	std::shared_ptr<Text> _rev;
	Timer _timer;
};

