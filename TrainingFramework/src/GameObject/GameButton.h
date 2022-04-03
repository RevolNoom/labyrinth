#pragma once 
#include "Sprite2D.h"
#include <functional>

class GameButton : public Sprite2D
{
public:
	GameButton() : Sprite2D(), m_pBtClick(nullptr), m_isHolding(false) {}
	GameButton(std::shared_ptr<Model> model, std::shared_ptr<Shader> shader, std::shared_ptr<Texture> texture);
	GameButton(std::shared_ptr<Texture> texture);
	~GameButton();
	virtual bool HandleMouseClick(const InputEventMouseClick* ev) override;
	virtual bool HandleMouseMotion(const InputEventMouseMotion* ev) override;
	bool	IsHolding();

	void	SetHoveringTexture(std::shared_ptr<Texture> texture);
	void	SetOnClick(std::function<void(void)>pBtClick);

protected:
	bool	MouseIsHoveringOnButton(const InputEventMouse* ev);

private:

	std::function<void(void)>m_pBtClick;

	enum State
	{
		NOT_HOVERED,
		HOVERED,
	};
	std::shared_ptr<Texture> _texture[2];

	bool	m_isHolding;
};
