#include "stdafx.h"
#include <iostream>
#include "ServiceLocator.hpp"
#include "TextureManager.hpp"
#include "InputManager.hpp"
#include "AudioManager.hpp"
#include "DrawManager.hpp"
#include "OverWorldState.hpp"
#include "StateManager.hpp"
#include "BattleState.hpp"
#include "OVArea.hpp"
#include "OVPlayer.hpp"
namespace spaceshooter
{
	bool OverWorldState::Enter()
	{
		
		m_OVPlayer = new OVPlayer();
		m_OVArea = new OVArea("OverWorld1_1.txt",this,m_OVPlayer);
		m_draw_manager = ServiceLocator<DrawManager>::GetService();
		m_input_manager = ServiceLocator<InputManager>::GetService();
		//m_stateManager = ServiceLocator<StateManager>::GetService();
		InitAudio();
		m_mouse = m_input_manager->GetMouse();
	
		m_exitState = false;
		return true;
	}
	bool OverWorldState::Update(float deltatime)
	{
		UpdateMouse(deltatime);
		if (m_OVArea != NULL)
		{
			m_OVArea->Update(deltatime);
		}
		
		m_OVPlayer->Update(deltatime);
		if (m_exitState == true)
		{
			return false;
		}
		return true;
	}
	void OverWorldState::InitAudio()
	{
		AudioManager* audio_manager = ServiceLocator<AudioManager>::GetService();
		sf::Music* BS_Music = audio_manager->CreateMusicFromFile("../assets/audio/Music/OV/OV_1.ogg");
		//BS_Music->play();
	}
	void OverWorldState::Exit()
	{

	}
	void OverWorldState::Draw()
	{
		m_draw_manager->Draw(*m_OVArea);
		m_draw_manager->Draw(*m_OVPlayer);
	}
	std::string OverWorldState::GetNextState()
	{
		return std::string("BattleState"+m_encounterName);
	}
	void OverWorldState::UpdateMouse(float deltatime)
	{
		/*mousePosition = m_draw_manager->getWindow()->mapPixelToCoords(m_mouse.getPosition(*m_draw_manager->getWindow()));
		if (m_mouse.isButtonPressed(m_mouse.Right))
		{
			m_OVArea = new OVArea("OverWorld1_1Spooky.txt", this, m_OVPlayer);
		}*/
	}
	void OverWorldState::ChangeArea(std::string p_fileareaName)
	{
		m_OVArea = new OVArea(p_fileareaName+".txt", this, m_OVPlayer);
	}
	void OverWorldState::SetExitState(std::string encounterName)
	{
		//m_stateManager->AttachState("BattleState", new BattleState("Boss_1", encounterName, "Night"));
		m_encounterName = encounterName;
		m_exitState = true;
	}
}