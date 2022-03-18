#include "Application.h"
#include "GameStates/SceneDirector.h"
#include "GameStates/Scene.h"

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

	SceneDirector::GetInstance()->PushState(StateType::STATE_INTRO);
}
void Application::Update(GLfloat deltaTime)
{
	SceneDirector::GetInstance()->PerformStateChange();

	if (SceneDirector::GetInstance()->HasState())
		SceneDirector::GetInstance()->CurrentState()->Update(deltaTime);
}

void Application::Render()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	if (SceneDirector::GetInstance()->HasState())
		SceneDirector::GetInstance()->CurrentState()->Draw();
}

void Application::HandleKeyEvent(unsigned char key, bool bIsPressed)
{
	HandleEvent(std::make_shared<InputEventKeyPress>(key, bIsPressed));
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
	if (SceneDirector::GetInstance()->HasState())
		SceneDirector::GetInstance()->HandleEvent(ev);
}

void Application::Exit()
{
	exit(0);
}
