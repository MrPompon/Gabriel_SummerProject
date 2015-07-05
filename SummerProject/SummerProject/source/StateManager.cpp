// StateManager.cpp

#include "stdafx.h"
#include "AbstractState.hpp"
#include "StateManager.hpp"

#include "BattleState.hpp"
#include "TestState.hpp"
#include "CollisionTestState.hpp"

namespace spaceshooter
{
	StateManager::StateManager()
	{
		m_active_state = nullptr;
	}

	StateManager::~StateManager()
	{
	}

	bool StateManager::Initialize()
	{ 
		AttachState("Test", new TestState);
		AttachState("BattleState", new BattleState("DarkGround","LowKeyKnight","Dawn"));
		AttachState("ColTest", new CollisionTestState);
		SetActiveState("BattleState");

		return true;
	}

	void StateManager::Shutdown()
	{
		auto itr = m_states.begin();
		while (itr != m_states.end())
		{
			delete itr->second;
			++itr;
		}
		m_states.clear();
	}

	bool StateManager::Update(float deltatime)
	{
		if (!m_active_state)
			return false;

		if (!m_active_state->Update(deltatime))
		{
			if (!SetActiveState(m_active_state->GetNextState()))
			{
				return false;
			}
		}
		return true;
	}

	void StateManager::Draw()
	{
		if (!m_active_state)
			return;
		m_active_state->Draw();
	}

	void StateManager::AttachState(const std::string& name, AbstractState* state)
	{
		m_states.insert(std::pair<std::string, AbstractState*>(name, state));
	}

	void StateManager::DetachState(const std::string& name)
	{
		auto itr = m_states.find(name);
		if (itr != m_states.end())
		{
			delete itr->second;
			m_states.erase(itr);
		}
	}

	bool StateManager::SetActiveState(const std::string& name)
	{
		if (m_active_state)
			m_active_state->Exit();
		m_active_state = nullptr;

		auto itr = m_states.find(name);
		if (itr != m_states.end())
		{
			m_active_state = itr->second;
			if (!m_active_state->Enter())
			{
				return false;
			}
		}
		else
		{
			return false;
		}
		return true;
	}
} // namespace spaceshooter
