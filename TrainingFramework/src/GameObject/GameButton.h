#pragma once 
#include "Sprite2D.h"
#include <functional>

class GameButton : public Sprite2D
{
public:
	GameButton() : Sprite2D(), m_pBtClick(nullptr), m_isHolding(false) {}
	GameButton(std::shared_ptr<Model> model, std::shared_ptr<Shader> shader, std::shared_ptr<Texture> texture);
	~GameButton();
	void	SetOnClick(std::function<void(void)>pBtClick);
	bool	HandleMouseClick(const InputEventMouseClick* ev);
	bool	IsHolding();

private:
	bool	MouseIsHoveringOnButton(const InputEventMouseClick* ev);

	std::function<void(void)>m_pBtClick;
	bool	m_isHolding;
};
