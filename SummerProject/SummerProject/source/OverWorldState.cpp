#include "stdafx.h"
#include <iostream>
#include "ServiceLocator.hpp"
#include "TextureManager.hpp"
#include "InputManager.hpp"
#include "AudioManager.hpp"
#include "DrawManager.hpp"
#include "OverWorldState.hpp"

#include "OVArea.hpp"
namespace spaceshooter
{
	bool OverWorldState::Enter()
	{
		m_OVArea = new OVArea("OverWorld1_1.txt");
		m_draw_manager = ServiceLocator<DrawManager>::GetService();
		m_input_manager = ServiceLocator<InputManager>::GetService();
		m_mouse = m_input_manager->GetMouse();
		return true;
	}
	bool OverWorldState::Update(float deltatime)
	{
		UpdateMouse(deltatime);
		m_OVArea->Update(deltatime);
		return true;
	}
	void OverWorldState::Exit()
	{

	}
	void OverWorldState::Draw()
	{
		m_draw_manager->Draw(*m_OVArea);
	}
	std::string OverWorldState::GetNextState()
	{
		return std::string("");
	}
	void OverWorldState::UpdateMouse(float deltatime)
	{
		mousePosition = m_draw_manager->getWindow()->mapPixelToCoords(m_mouse.getPosition(*m_draw_manager->getWindow()));
	}
}