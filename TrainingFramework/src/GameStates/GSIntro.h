#pragma once
#include "Scene.h"

class GSIntro : public Scene
{
public:
	GSIntro();
	~GSIntro();

	void	Init() override;
	void	Exit() override;

	void	Pause() override;
	void	Resume() override;

	void	HandleEvents() override;
	void	HandleKeyPress(const InputEventKeyPress* ev) override;
	void	HandleMouseClick(const InputEventMouseClick* ev) override;
	void	HandleMouseMotion(const InputEventMouseMotion* ev) override;
	void	Update(float deltaTime) override;
	void	Draw() override;

private:
	std::shared_ptr<Sprite2D> m_logo;
	float	m_time;
};

