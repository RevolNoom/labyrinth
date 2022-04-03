#include "GameButton.h"

GameButton::GameButton(std::shared_ptr<Model> model, std::shared_ptr<Shader> shader, std::shared_ptr<Texture> texture)
	: Sprite2D(-1, model, shader, texture), m_pBtClick(nullptr), m_isHolding(false)
{
	_texture[HOVERED] = texture;
	_texture[NOT_HOVERED] = texture;
}

GameButton::GameButton(std::shared_ptr<Texture> texture): Sprite2D(texture)
{
	_texture[HOVERED] = texture;
	_texture[NOT_HOVERED] = texture;
}

GameButton::~GameButton()
{
}

void GameButton::SetHoveringTexture(std::shared_ptr<Texture> texture)
{
	_texture[HOVERED] = texture;
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
		}
		m_isHolding = false;
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
	if (MouseIsHoveringOnButton(ev))
	{
		SetTexture(_texture[HOVERED]);
	}
	else
		SetTexture(_texture[NOT_HOVERED]);
	return false;
}


bool GameButton::IsHolding()
{
	return m_isHolding;
}
