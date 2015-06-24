// BattleState.cpp

#include "stdafx.h"
#include <iostream>
#include "ServiceLocator.hpp"
#include "TextureManager.hpp"
#include "InputManager.hpp"
#include "AudioManager.hpp"
#include "DrawManager.hpp"
#include "BattleState.hpp"

#include "BS_Player.hpp"
#include "BS_Enemy.hpp"
#include "BS_Skills.hpp"

namespace spaceshooter
{
	BattleState::BattleState()
	{
		m_screen_width = 1024.0f;
		m_screen_height = 600.0f;
		player_saveFile = "save_file_1.txt";
		enemy_encounter_name = "Minotaur";
		for (unsigned int index = 0; index < ACTION_COUNT; index++)
		{
			m_actions[index] = false;
		}
		m_player = new BS_Player(player_saveFile);
		m_enemy = new BS_Enemy(enemy_encounter_name);
		m_skillHolder = new BS_Skills();

		InitEnemyStats();
		InitPlayerStats();
		//Init all 4 enemy skills
		m_enemySkills = m_enemy->GetEnemySkills();
		for (int i = 0; i < m_enemySkills.size(); i++)
		{
			InitSkillEnemy(m_enemySkills[i],i);
		}
		FirstStrikeDecider();
		currentSelectedOption= 0;
		AmountOfOptionsInMenu1;
		AmountOfOptionsInMenu2;
		AmountOfOptionsInSkillScreen;
	}

	BattleState::~BattleState()
	{
	}

	bool BattleState::Enter()
	{
		// register to listen for all input actions
		InputManager* input_manager = ServiceLocator<InputManager>::GetService();
		input_manager->RegisterKeyActionListener(Action::LEFT, this, &BattleState::OnAction);
		input_manager->RegisterKeyActionListener(Action::RIGHT, this, &BattleState::OnAction);
		input_manager->RegisterKeyActionListener(Action::UP, this, &BattleState::OnAction);
		input_manager->RegisterKeyActionListener(Action::DOWN, this, &BattleState::OnAction);
		input_manager->RegisterKeyActionListener(Action::FIRE, this, &BattleState::OnAction);
		input_manager->RegisterKeyActionListener(Action::ALTFIRE, this, &BattleState::OnAction);
		input_manager->RegisterKeyActionListener(Action::SELECT1, this, &BattleState::OnAction);
		input_manager->RegisterKeyActionListener(Action::SELECT2, this, &BattleState::OnAction);
		input_manager->RegisterKeyActionListener(Action::SELECT3, this, &BattleState::OnAction);
		input_manager->RegisterKeyActionListener(Action::SELECT4, this, &BattleState::OnAction);

		
		m_player_position = { 300.0f, m_screen_height * 0.5f };
		m_player_velocity = { 0.0f, 0.0f };

		TextureManager* texture_manager = ServiceLocator<TextureManager>::GetService();
		m_player_texture = texture_manager->CreateTextureFromFile("../assets/player.png");
		m_player_texture->setSmooth(false);
		m_player_sprite.setTexture(*m_player_texture);
		m_player_sprite.setPosition(m_player_position);
		m_player_sprite.setOrigin(
			static_cast<float>(m_player_sprite.getTextureRect().width) * 0.5f,
			static_cast<float>(m_player_sprite.getTextureRect().height) * 0.5f);


		AudioManager* audio_manager = ServiceLocator<AudioManager>::GetService();
		sf::SoundBuffer* sound_buffer = audio_manager->CreateSoundFromFile("../assets/audio/gunfire.ogg");
		m_sound.setBuffer(*sound_buffer);
		m_sound.setLoop(false);
		m_sound.setVolume(60.0f);


		// better to have a local pointer than to access it through the service locator
		m_draw_manager = ServiceLocator<DrawManager>::GetService();

		return true;
	}
	void BattleState::FirstStrikeDecider()
	{
		//determines whos turn it is first 
		if (m_enemy_speed < m_player_speed)
		{
			turnManager = TURN_PLAYER;
		}
		else
		{
			turnManager = TURN_ENEMY;
		}
	}
	void BattleState::Exit()
	{
		TextureManager* texture_manager = ServiceLocator<TextureManager>::GetService();


		//  we should destroy audio stuff here
		// add destroy music and soundbuffer methods to the audio manager
		AudioManager* audio_manager = ServiceLocator<AudioManager>::GetService();
		// ...

		//  unregister all actions listeners
		InputManager* input_manager = ServiceLocator<InputManager>::GetService();
		input_manager->UnregisterKeyActionListener(Action::LEFT, this);
		input_manager->UnregisterKeyActionListener(Action::RIGHT, this);
		input_manager->UnregisterKeyActionListener(Action::UP, this);
		input_manager->UnregisterKeyActionListener(Action::DOWN, this);
		input_manager->UnregisterKeyActionListener(Action::FIRE, this);
		input_manager->UnregisterKeyActionListener(Action::ALTFIRE, this);
		input_manager->UnregisterKeyActionListener(Action::SELECT1, this);
		input_manager->UnregisterKeyActionListener(Action::SELECT2, this);
		input_manager->UnregisterKeyActionListener(Action::SELECT3, this);
		input_manager->UnregisterKeyActionListener(Action::SELECT4, this);
	}

	void BattleState::InitEnemyStats()
	{
		m_enemy_name = m_enemy->GetName();
		m_enemy_health = m_enemy->GetHealth();
		m_enemy_damage = m_enemy->GetDMG();
		m_enemy_speed = m_enemy->GetSpeed();
		m_enemy_loot = m_enemy->GetLoot();
	}
	void BattleState::InitPlayerStats()
	{
		m_player_damage = m_player->GetDMG();
		m_player_health = m_player->GetHealth();
		m_player_speed = m_player->GetSpeed();
	}
	bool BattleState::Update(float deltatime)
	{
		UpdatePlayer(deltatime);
		BattleManager(deltatime);
		return true;
	}

	void BattleState::Draw()
	{

		m_draw_manager->Draw(m_player_sprite, sf::RenderStates::Default);
	}

	std::string BattleState::GetNextState()
	{
		return std::string("");
	}

	// private
	void BattleState::OnAction(const std::string& action, bool state)
	{
		// note(tommi): map actions to an internal structure 
		if (action.compare(Action::LEFT) == 0)
		{
			m_actions[ACTION_LEFT] = state;
		}
		else if (action.compare(Action::RIGHT) == 0)
		{
			m_actions[ACTION_RIGHT] = state;
		}
		else if (action.compare(Action::UP) == 0)
		{
			m_actions[ACTION_UP] = state;
		}
		else if (action.compare(Action::DOWN) == 0)
		{
			m_actions[ACTION_DOWN] = state;
		}
		else if (action.compare(Action::FIRE) == 0)
		{
			m_actions[ACTION_FIRE] = state;
		}
		else if (action.compare(Action::ALTFIRE) == 0)
		{
			m_actions[ACTION_ALT_FIRE] = state;
		}
		else if (action.compare(Action::SELECT1) == 0)
		{
			m_actions[ACTION_SELECT1] = state;
		}
		else if (action.compare(Action::SELECT2) == 0)
		{
			m_actions[ACTION_SELECT2] = state;
		}
		else if (action.compare(Action::SELECT3) == 0)
		{
			m_actions[ACTION_SELECT3] = state;
		}
		else if (action.compare(Action::SELECT4) == 0)
		{
			m_actions[ACTION_SELECT4] = state;
		}
	}

	void BattleState::BattleManager(float deltatime)
	{
		
		if (turnManager == TURN_ENEMY)
		{
			EnemysTurn(deltatime);
		}
		if (turnManager == TURN_PLAYER)
		{
			PlayersTurn(deltatime);
		}
	}
	void BattleState::InitSkillEnemy(std::string p_skillname,int skillNumber)
	{
		m_skillHolder->LoadSkill("skill_file",p_skillname);
		//loads the specific skill, need to store the values somewhere. 
		switch (skillNumber)
		{
		case 0:
			m_enemy_skill_1_Number = skillNumber;
			m_enemy_skill_1_DMG = m_skillHolder->GetSkillDMG();
			m_enemy_skill_1_HitRate = m_skillHolder->GetSkillHitRate();
			m_enemy_skill_1_AmountOfAttacks = m_skillHolder->GetSkillAmountOfAttacks();
			m_enemy_skill_1_Attribute = m_skillHolder->GetSkillAttribute();
			m_enemy_skill_1_Name = m_skillHolder->GetSkillName();
			break;
		case 1:
			m_enemy_skill_2_Number = skillNumber;
			m_enemy_skill_2_DMG = m_skillHolder->GetSkillDMG();
			m_enemy_skill_2_HitRate = m_skillHolder->GetSkillHitRate();
			m_enemy_skill_2_AmountOfAttacks = m_skillHolder->GetSkillAmountOfAttacks();
			m_enemy_skill_2_Attribute = m_skillHolder->GetSkillAttribute();
			m_enemy_skill_2_Name = m_skillHolder->GetSkillName();
			break;
		case 2:
			m_enemy_skill_3_Number = skillNumber;
			m_enemy_skill_3_DMG = m_skillHolder->GetSkillDMG();
			m_enemy_skill_3_HitRate = m_skillHolder->GetSkillHitRate();
			m_enemy_skill_3_AmountOfAttacks = m_skillHolder->GetSkillAmountOfAttacks();
			m_enemy_skill_3_Attribute = m_skillHolder->GetSkillAttribute();
			m_enemy_skill_3_Name = m_skillHolder->GetSkillName();
			break;
		case 3:
			m_enemy_skill_4_Number = skillNumber;
			m_enemy_skill_4_DMG = m_skillHolder->GetSkillDMG();
			m_enemy_skill_4_HitRate = m_skillHolder->GetSkillHitRate();
			m_enemy_skill_4_AmountOfAttacks = m_skillHolder->GetSkillAmountOfAttacks();
			m_enemy_skill_4_Attribute = m_skillHolder->GetSkillAttribute();
			m_enemy_skill_4_Name = m_skillHolder->GetSkillName();
			break;
		}
		
		
		
		
		
	}
	void BattleState::PlayersTurn(float deltatime)
	{
		playersTurn = true;
		//std::cout << "Players Turn" << std::endl;
		//change these for correct input, add delay between turns.
		//std::cout << "Playeeerrr";
			if (m_actions[ACTION_RIGHT])
			{
				turnManager = TURN_ENEMY;
			}
			if (m_actions[ACTION_FIRE])
			{
				currentSelectedOption++;
				std::cout << "MenuOptionIsAt " << currentSelectedOption << std::endl;
			}
		
	}
	void BattleState::EnemysTurn(float deltatime)
	{
		enemysTurn = true;
		//std::cout << "Enemyyyy";
		//std::cout << "Enemies Turn" << std::endl;
		//change these for correct input(AI), add delay between turns.
		if (m_actions[ACTION_LEFT])
		{
			turnManager = TURN_PLAYER;
		}
		if (m_actions[ACTION_FIRE])
		{
			currentSelectedOption++;
			std::cout<<m_enemy_skill_1_Name<<"has "<< m_enemy_skill_1_DMG<<" DMG "<<std::endl;
			std::cout << m_enemy_skill_2_Name << "has " << m_enemy_skill_2_DMG << " DMG " << std::endl;
			std::cout << m_enemy_skill_3_Name << "has " << m_enemy_skill_3_DMG << " DMG " << std::endl;
			std::cout << m_enemy_skill_4_Name << "has " << m_enemy_skill_4_DMG << " DMG " << std::endl;
		}
	}
	void BattleState::EnemyUseSkill()
	{

	}
	void BattleState::UpdatePlayer(float deltatime)
	{
		// note(tommi): these will not be hardcoded
		const float playerHalfWidth = m_player_texture->getSize().x * 0.5f;
		const float playerHalfHeight = m_player_texture->getSize().y * 0.5f;
		const float screenWidth = m_screen_width - playerHalfWidth;
		const float screenHeight = m_screen_height - playerHalfHeight;
		const float playerSpeed = 400.0f;

		bool playerMove = false;
		sf::Vector2f playerAcceleration = { 0.0f, 0.0f };

		if (m_actions[ACTION_UP])
		{
			playerMove = true;
			if (m_player_position.y > playerHalfHeight)
			{
				playerAcceleration.y = -1.0f;
			}
		}
		if (m_actions[ACTION_DOWN])
		{
			playerMove = true;
			if (m_player_position.y < screenHeight)
			{
				playerAcceleration.y = 1.0f;
			}
		}
		if (m_actions[ACTION_LEFT])
		{
			playerMove = true;
			if (m_player_position.x > playerHalfWidth)
			{
				playerAcceleration.x = -1.0f;
			}
		}
		if (m_actions[ACTION_RIGHT])
		{
			playerMove = true;
			if (m_player_position.x < screenWidth)
			{
				playerAcceleration.x = 1.0f;
			}
		}
		m_player_sprite.setPosition(m_player_position);
	}

} // namespace spaceshooter
