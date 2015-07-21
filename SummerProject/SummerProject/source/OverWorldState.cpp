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
		OV_Music = audio_manager->CreateMusicFromFile("../assets/audio/Music/OV/OV_1.ogg");
		OV_Music->play();
	}
	void OverWorldState::Exit()
	{
		OV_Music->stop();
	
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
	void OverWorldState::ChangeArea(std::string p_fileareaName)
	{
		m_OVArea = new OVArea(p_fileareaName+".txt", this, m_OVPlayer);
	}
	void OverWorldState::SetExitState(std::string encounterName)
	{
		//m_stateManager->AttachState("BattleState"+m_encounterName, new BattleState("Boss_1", encounterName, "Night"));
		m_encounterName = encounterName;
		m_exitState = true;
	}
}