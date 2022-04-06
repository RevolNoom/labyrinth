#include "Application.h"
#include "GameScenes/SceneDirector.h"
#include "GameScenes/Scene.h"
#include "Keyboard.h"

Application::Application()
{
}

Application::~Application()
{
}

void Application::Init()
{
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	// Create a 2D camera
	m_camera = std::make_shared<Camera>(0, 0, Globals::screenWidth, 0, Globals::screenHeight, -1.0f, 1.0f, 10.0f);
	
	// Initiallize SceneDirector
	SceneDirector::GetInstance();
}
void Application::Update(GLfloat deltaTime)
{
	SceneDirector::GetInstance()->Update(deltaTime);
}

void Application::Render()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	SceneDirector::GetInstance()->CurrentScene()->Draw();
}

void Application::HandleKeyEvent(unsigned char key, bool bIsPressed)
{
	auto ev = std::make_shared<InputEventKeyPress>(key, bIsPressed);
	Keyboard::GetInstance()->HandleKeyPress(ev.get());
	HandleEvent(ev);
}

void Application::HandleTouchEvent(GLint x, GLint y, bool bIsPressed)
{
	HandleEvent(std::make_shared<InputEventMouseClick>(Vector2(x, y), bIsPressed));
}

void Application::HandleMouseMoveEvent(GLint x, GLint y)
{
	HandleEvent(std::make_shared<InputEventMouseMotion>(Vector2(x, y)));
}

void Application::HandleEvent(std::shared_ptr<InputEvent> ev)
{
	SceneDirector::GetInstance()->HandleEvent(ev);
}

void Application::Exit()
{
	exit(0);
}
