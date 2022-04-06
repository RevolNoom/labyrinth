#pragma once 
#include "Sprite2D.h"
#include <functional>

class GameButton : public Sprite2D
{
public:
	enum Hover
	{
		H_OFF,
		H_ON,
		MAX_HOVER
	};

	enum Toggle
	{
		T_OFF,
		T_ON,
		MAX_TOGGLE
	};

	GameButton();
	GameButton(std::shared_ptr<Texture> texture);

	void	EnableToggle(bool enable);
	bool	IsToggledOn();

	void	SetTexture(std::shared_ptr<Texture> texture, bool isHovered = Hover::H_OFF, bool toggleState = Toggle::T_ON);

	void	SetOnClick(std::function<void(void)>pBtClick);
	bool	IsHolding();

	virtual bool HandleMouseClick(const InputEventMouseClick* ev) override;
	virtual bool HandleMouseMotion(const InputEventMouseMotion* ev) override;

	void UpdateTexture(const InputEventMouse* ev);

protected:
	bool	MouseIsHoveringOnButton(const InputEventMouse* ev);

private:

	std::function<void(void)>m_pBtClick;

	bool	m_isHolding;
	
	// Rev's Mod
	std::shared_ptr<Texture> _texture[MAX_TOGGLE][MAX_HOVER];
	bool	_isToggledOn;
	bool	_allowToggle;
};
