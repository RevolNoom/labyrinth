#pragma once
#include "Scene.h"

class Sprite2D;
class Sprite3D;
class Text;
class GameButton;
class SpriteAnimation;

class GSPlay :
	public Scene
{
public:
	GSPlay();
	~GSPlay();

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
    int m_Test;

private:
	std::shared_ptr<Sprite2D>	m_background;
	std::shared_ptr<Text>		m_score;
	std::list<std::shared_ptr<GameButton>>	m_listButton;
	std::list<std::shared_ptr<SpriteAnimation>>	m_listAnimation;

};

