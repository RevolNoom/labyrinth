#pragma once
#include "Scene.h"
#include "GameButton.h"

class GSMenu :
	public Scene
{
public:
	GSMenu();
	~GSMenu();

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
	std::shared_ptr<Sprite2D>				m_background;
	std::list<std::shared_ptr<GameButton>>	m_listButton;
	std::shared_ptr<Text>					m_textGameName;

};

