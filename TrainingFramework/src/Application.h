#pragma once
#include "Singleton.h"
#include "GameConfig.h"
#include "Camera.h"
#include "InputEvent.hpp"

class Application : public CSingleton<Application>
{
public:
	Application();
	~Application();

	void	Init();
	void	Update(GLfloat deltaTime);
	void	Render();

	void	HandleKeyEvent(unsigned char key, bool bIsPresseded);
	void	HandleTouchEvent(GLint x, GLint y, bool bIsPresseded);
	void	HandleMouseMoveEvent(GLint x, GLint y);
	void	HandleEvent(std::shared_ptr<InputEvent> ev);

	void	Exit();

	std::shared_ptr<Camera> GetCamera() {
		return m_camera;
	}

private:
	std::shared_ptr<Camera> m_camera;
};

