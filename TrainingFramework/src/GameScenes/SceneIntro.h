#pragma once
#include "Scene.h"

class SceneIntro : public Scene
{
public:
	SceneIntro();
	~SceneIntro();
	virtual void Init() override;
	virtual void Update(float deltaTime) override;

private:
	float	m_time;
};

