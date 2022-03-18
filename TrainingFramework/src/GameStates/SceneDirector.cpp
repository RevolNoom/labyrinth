
#include "SceneDirector.h"
#include "Scene.h"

SceneDirector::SceneDirector() : m_running(true), m_pActiveState(nullptr), m_pNextState(nullptr), m_fullscreen(false)
{
}


SceneDirector::~SceneDirector()
{
}


void SceneDirector::Cleanup()
{
	// cleanup the all states
	while (!m_StateStack.empty()) {
		m_StateStack.back()->Exit();
		m_StateStack.pop_back();
	}
}

void SceneDirector::ChangeState(StateType state)
{
	std::shared_ptr<Scene> nextState = Scene::CreateState(state);
	ChangeState(nextState);
}

void SceneDirector::ChangeState(std::shared_ptr<Scene> state)
{
	m_pNextState = state;
}

void SceneDirector::PushState(StateType state)
{
	std::shared_ptr<Scene> nextState = Scene::CreateState(state);
	// pause current state
	if (!m_StateStack.empty()) {
		m_StateStack.back()->Pause();
	}

	m_pNextState = nextState;
}

void SceneDirector::PopState()
{
	// cleanup the current state
	if (!m_StateStack.empty()) {
		m_StateStack.back()->Exit();
		m_StateStack.pop_back();
	}

	// resume previous state
	if (!m_StateStack.empty()) {
		m_StateStack.back()->Resume();
		m_pActiveState = m_StateStack.back();
	}
}

void  SceneDirector::PerformStateChange()
{
	if (m_pNextState != 0)
	{
		if (m_StateStack.empty() == false) {
			if(m_pActiveState->GetGameStateType() == StateType::STATE_INTRO)
			{
				// Cleanup Intro state
				m_pActiveState->Exit();
				m_StateStack.pop_back();
			}
			else
			{
				// Pause other states
				m_pActiveState->Pause();
			}
		}

		// store and init the new state
		m_StateStack.push_back(m_pNextState);
		m_StateStack.back()->Init();
		m_pActiveState = m_pNextState;
	}

	m_pNextState = 0;
}

void SceneDirector::HandleEvent(std::shared_ptr<InputEvent> ev)
{
	ev->HandledBy(CurrentState());
}
