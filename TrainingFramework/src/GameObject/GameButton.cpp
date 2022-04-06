#include "GameButton.h"

GameButton::GameButton():
	GameButton(nullptr) 
{
}

GameButton::GameButton(std::shared_ptr<Texture> texture) :
	Sprite2D(texture),
	_allowToggle(false),
	_isToggledOn(true)
{
	Init();
	_texture[T_ON][Hover::H_ON] =
	_texture[T_ON][Hover::H_OFF] = 
	_texture[T_OFF][Hover::H_ON] = 
	_texture[T_OFF][Hover::H_OFF] = texture;
}

void GameButton::EnableToggle(bool enable)
{
	_allowToggle = enable;
}

bool GameButton::IsToggledOn()
{
	return _isToggledOn;
}

void GameButton::SetTexture(std::shared_ptr<Texture> texture, bool isHovered, bool toggleState)
{
	_texture[isHovered][toggleState] = texture;
}

void GameButton::SetOnClick(std::function<void(void)> pBtClick)
{
	m_pBtClick = pBtClick;
}

bool GameButton::HandleMouseClick(const InputEventMouseClick* ev)
{
	bool isHandled = false;
	if (ev->IsPressed() && MouseIsHoveringOnButton(ev))
	{
		m_isHolding = true;
	}
	else
	{
		// Only perform click action when the same button was pressed down and released
		if (MouseIsHoveringOnButton(ev)	&& IsHolding())
		{
			m_pBtClick();
			isHandled = true;
			m_isHolding = false;
			if (_allowToggle)
			{
				_isToggledOn = !_isToggledOn;
				UpdateTexture(ev);
			}
		}
	}
	return isHandled;
}

bool GameButton::MouseIsHoveringOnButton(const InputEventMouse* ev)
{
	GLint x = ev->GetPosition().x, y = ev->GetPosition().y;
	return (x > m_position.x - m_iWidth / 2) && (x < m_position.x + m_iWidth / 2)
		&& (y > m_position.y - m_iHeight / 2) && (y < m_position.y + m_iHeight / 2);
}

bool GameButton::HandleMouseMotion(const InputEventMouseMotion* ev)
{
	UpdateTexture(ev);
	return false;
}

void GameButton::UpdateTexture(const InputEventMouse* ev)
{
	auto hovered = MouseIsHoveringOnButton(ev);
	Sprite2D::SetTexture(_texture[hovered][_isToggledOn]);
}


bool GameButton::IsHolding()
{
	return m_isHolding;
}
