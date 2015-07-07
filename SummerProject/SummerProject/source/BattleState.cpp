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
#include "GUIWindow.hpp"
#include "BS_LifeBar.hpp"
#include "SkillEffect.hpp"
#include "ScreenEffects.hpp"

namespace spaceshooter
{
	BattleState::BattleState(std::string p_areaTheme, std::string p_encounterName, std::string p_timeOfDay)
	{
		m_encounterName = p_encounterName;
		m_areaTheme = p_areaTheme;

		m_screen_width = 1024.0f;
		m_screen_height = 600.0f;
		player_saveFile = "save_file_1.txt";
		enemy_encounter_name = m_encounterName;
		for (unsigned int index = 0; index < ACTION_COUNT; index++)
		{
			m_actions[index] = false;
		}
		m_player = new BS_Player(player_saveFile);
		m_enemy = new BS_Enemy(enemy_encounter_name,this);
		m_skillHolder = new BS_Skills();
		m_playerVector.push_back(*m_player);
		m_enemyVector.push_back(*m_enemy);
		InitEnemyStats();
		InitPlayerStats();
		//Init all 4 enemy skills
		m_enemySkills = m_enemy->GetEnemySkills();
		for (int i = 0; i < m_enemySkills.size(); i++)
		{
			InitSkillEnemy(m_enemySkills[i],i);
		}
		for (int i = 0; i < m_playerSkills.size(); i++)
		{
			InitSkillPlayer(m_playerSkills[i], i);
		}
		FirstStrikeDecider();
		InitBattleHUD();
		InitLifeBars();
		InitBackground(m_areaTheme);
		AmountOfOptionsInMenu1;
		AmountOfOptionsInMenu2;
		AmountOfOptionsInSkillScreen;
		//check time of day in constructor, change accordlinly 

		//set to night
		if (p_timeOfDay == "Night")
		{
			ScreenEffects *nightScreen = new ScreenEffects(m_window, "SetNight", 9999, m_draw_manager);
			AllScreenEffects.push_back(*nightScreen);
		}
		else if (p_timeOfDay == "Dusk")
		{
			ScreenEffects *duskScreen = new ScreenEffects(m_window, "SetDusk", 9999, m_draw_manager);
			AllScreenEffects.push_back(*duskScreen);
		}
		else if (p_timeOfDay == "Dawn")
		{
			ScreenEffects *dawnScreen = new ScreenEffects(m_window, "SetDawn", 9999, m_draw_manager);
			AllScreenEffects.push_back(*dawnScreen);
		}
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

		m_mouse = input_manager->GetMouse();
		m_player_position = { m_screen_width*0.2f, m_screen_height * 0.8f };

		TextureManager* texture_manager = ServiceLocator<TextureManager>::GetService();
		m_player_texture = texture_manager->CreateTextureFromFile("../assets/Sprites/Player_BS/Character_1_BS.png");
		m_player_texture->setSmooth(false);
		m_player_sprite.setTexture(*m_player_texture);
		m_player_sprite.setPosition(m_player_position);
		m_player_sprite.setOrigin(
			static_cast<float>(m_player_sprite.getTextureRect().width) * 0.5f,
			static_cast<float>(m_player_sprite.getTextureRect().height) * 0.5f);

		InitAudio(m_areaTheme);

		// better to have a local pointer than to access it through the service locator
		m_draw_manager = ServiceLocator<DrawManager>::GetService();
		m_window = m_draw_manager->getWindow();
		return true;
	}
	void BattleState::InitAudio(std::string p_battleTheme)
	{
		m_music_victoryPlaying = false;
		AudioManager* audio_manager = ServiceLocator<AudioManager>::GetService();
		sf::Music* BS_Music = audio_manager->CreateMusicFromFile("../assets/audio/Music/BS/" + p_battleTheme + ".ogg");
		sf::Music* BS_Music_Victory = audio_manager->CreateMusicFromFile("../assets/audio/Music/BS/VictoryTheme.ogg");
		sf::SoundBuffer *m_soundBuffer;
		m_soundBuffer= audio_manager->CreateSoundFromFile("../assets/audio/SFX/" + m_player_skill_1_Name + ".ogg");
		m_player_skill_1_sound.setBuffer(*m_soundBuffer);

		m_soundBuffer = audio_manager->CreateSoundFromFile("../assets/audio/SFX/" + m_player_skill_2_Name + ".ogg");
		m_player_skill_2_sound.setBuffer(*m_soundBuffer);

		m_soundBuffer = audio_manager->CreateSoundFromFile("../assets/audio/SFX/" + m_player_skill_3_Name + ".ogg");
		m_player_skill_3_sound.setBuffer(*m_soundBuffer);

		m_soundBuffer = audio_manager->CreateSoundFromFile("../assets/audio/SFX/" + m_player_skill_4_Name + ".ogg");
		m_player_skill_4_sound.setBuffer(*m_soundBuffer);

		m_soundBuffer = audio_manager->CreateSoundFromFile("../assets/audio/SFX/" + m_enemy_skill_1_Name + ".ogg");
		m_enemy_skill_1_sound.setBuffer(*m_soundBuffer);

		m_soundBuffer = audio_manager->CreateSoundFromFile("../assets/audio/SFX/" + m_enemy_skill_2_Name + ".ogg");
		m_enemy_skill_2_sound.setBuffer(*m_soundBuffer);

		m_soundBuffer = audio_manager->CreateSoundFromFile("../assets/audio/SFX/" + m_enemy_skill_3_Name + ".ogg");
		m_enemy_skill_3_sound.setBuffer(*m_soundBuffer);

		m_soundBuffer = audio_manager->CreateSoundFromFile("../assets/audio/SFX/" + m_enemy_skill_4_Name + ".ogg");
		m_enemy_skill_4_sound.setBuffer(*m_soundBuffer);

		m_soundBuffer = audio_manager->CreateSoundFromFile("../assets/audio/SFX/LootGain1.ogg");
		lootSound.setBuffer(*m_soundBuffer);

		m_music = BS_Music;
		m_music_victory = BS_Music_Victory;
		m_music->play();
		
	}
	void BattleState::CheckMousePosition(float deltatime)
	{
		//checks each seperate word in the GUIWindowToSeeIfItIsHovered
		mousePosition = m_draw_manager->getWindow()->mapPixelToCoords(m_mouse.getPosition(*m_draw_manager->getWindow()));
	
	}
	void BattleState::ManageWindow(std::string windowName, bool trueOrFalse)
	{
		for (unsigned int i = 0; i < AllGUIWindows.size(); i++)
		{
			if (AllGUIWindows[i].GetWindowName() == windowName)
			{
				AllGUIWindows[i].SetWindowVisible(trueOrFalse);
			}
		}
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
		m_enemyWon = false;
		m_enemy_name = m_enemy->GetName();
		m_enemy_health = m_enemy->GetHealth();
		m_enemy_damage = m_enemy->GetDMG();
		m_enemy_speed = m_enemy->GetSpeed();
		m_enemy_loot = m_enemy->GetLoot();
		m_enemy_hitrate = m_enemy->GetHitRate();
		m_enemy_evadeRate = m_enemy->GetEvadeRate();

		enemyPos.x = m_screen_width*0.7;
		enemyPos.y = m_screen_height*0.4;
	}
	void BattleState::InitPlayerStats()
	{
		m_playerWon = false;
		m_player_damage = m_player->GetDMG();
		m_player_health = m_player->GetHealth();
		m_player_speed = m_player->GetSpeed();
		m_player_evadeRate = m_player->GetEvadeRate();
		m_playerSkills = m_player->GetPlayerSkills();
		m_player_hitrate = m_player->GetHitRate();
	}
	bool BattleState::Update(float deltatime)
	{
		BattleManager(deltatime);
		UpdateBattleHUD(deltatime);
		m_turnDelayTime -= deltatime;
		CheckMousePosition(deltatime);
		m_enemyVector[0].Update(deltatime);
		for (unsigned int i = 0; i < AllSkillEffects.size(); i++)
		{
			AllSkillEffects[i].Update(deltatime);
		}
		for(unsigned int i = 0; i < AllScreenEffects.size(); i++)
		{
			AllScreenEffects[i].Update(deltatime);
		}
		return true;
	}

	void BattleState::Draw()
	{
		m_draw_manager->Draw(m_spr_battleBackground);
	
		m_draw_manager->Draw(m_player_sprite);
		m_draw_manager->Draw(m_enemyVector[0]);
		//m_draw_manager->Draw(m_playerVector[0]);
		for (unsigned int i = 0; i < AllSkillEffects.size(); i++)
		{
			m_draw_manager->Draw(AllSkillEffects[i]);
		}
		for (unsigned int i = 0; i < AllScreenEffects.size(); i++)
		{
			m_draw_manager->Draw(AllScreenEffects[i]);
		}
		for (unsigned int i = 0; i < AllLifeBars.size(); i++)
		{
			m_draw_manager->Draw(AllLifeBars[i]);
		}
		//draw player - enemy health
		m_draw_manager->Draw(text_player_health);
		m_draw_manager->Draw(text_enemy_health);
		m_draw_manager->Draw(text_battle_text);
		m_draw_manager->Draw(text_enemy_name);
		for (unsigned int i = 0; i<AllGUIWindows.size(); i++)
		{
			m_draw_manager->Draw(AllGUIWindows[i]);
		}
	}

	std::string BattleState::GetNextState()
	{
		return std::string("BattleState");
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
		if (turnManager == TURN_OVER)
		{
			if (!m_music_victoryPlaying)
			{	
				m_music->stop();
				m_music_victory->play();
				m_music_victoryPlaying = true;
				lootSound.play();
			}
			if (m_playerWon)
			{
				ManageWindow("BattleLootWindow", true);
				
			}
			else
			{
				
			}
		}
	}
	void BattleState::InitSkillPlayer(std::string p_skillname, int skillNumber)
	{
		m_skillHolder->LoadSkill("skill_file", p_skillname);
		//loads the specific skill, need to store the values somewhere. 
		switch (skillNumber)
		{
		case 0:
			m_player_skill_1_Number = skillNumber;
			m_player_skill_1_DMG = m_skillHolder->GetSkillDMG();
			m_player_skill_1_HitRate = m_skillHolder->GetSkillHitRate();
			m_player_skill_1_AmountOfAttacks = m_skillHolder->GetSkillAmountOfAttacks();
			m_player_skill_1_Attribute = m_skillHolder->GetSkillAttribute();
			m_player_skill_1_Name = m_skillHolder->GetSkillName();
			m_player_skill_1_animTime = m_skillHolder->GetSkillAnimationTime();
			break;
		case 1:
			m_player_skill_2_Number = skillNumber;
			m_player_skill_2_DMG = m_skillHolder->GetSkillDMG();
			m_player_skill_2_HitRate = m_skillHolder->GetSkillHitRate();
			m_player_skill_2_AmountOfAttacks = m_skillHolder->GetSkillAmountOfAttacks();
			m_player_skill_2_Attribute = m_skillHolder->GetSkillAttribute();
			m_player_skill_2_Name = m_skillHolder->GetSkillName();
			m_player_skill_2_animTime = m_skillHolder->GetSkillAnimationTime();
			break;
		case 2:
			m_player_skill_3_Number = skillNumber;
			m_player_skill_3_DMG = m_skillHolder->GetSkillDMG();
			m_player_skill_3_HitRate = m_skillHolder->GetSkillHitRate();
			m_player_skill_3_AmountOfAttacks = m_skillHolder->GetSkillAmountOfAttacks();
			m_player_skill_3_Attribute = m_skillHolder->GetSkillAttribute();
			m_player_skill_3_Name = m_skillHolder->GetSkillName();
			m_player_skill_3_animTime = m_skillHolder->GetSkillAnimationTime();
			break;
		case 3:
			m_player_skill_4_Number = skillNumber;
			m_player_skill_4_DMG = m_skillHolder->GetSkillDMG();
			m_player_skill_4_HitRate = m_skillHolder->GetSkillHitRate();
			m_player_skill_4_AmountOfAttacks = m_skillHolder->GetSkillAmountOfAttacks();
			m_player_skill_4_Attribute = m_skillHolder->GetSkillAttribute();
			m_player_skill_4_Name = m_skillHolder->GetSkillName();
			m_player_skill_4_animTime = m_skillHolder->GetSkillAnimationTime();
			break;
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
			m_enemy_skill_1_animTime = m_skillHolder->GetSkillAnimationTime();
			break;
		case 1:
			m_enemy_skill_2_Number = skillNumber;
			m_enemy_skill_2_DMG = m_skillHolder->GetSkillDMG();
			m_enemy_skill_2_HitRate = m_skillHolder->GetSkillHitRate();
			m_enemy_skill_2_AmountOfAttacks = m_skillHolder->GetSkillAmountOfAttacks();
			m_enemy_skill_2_Attribute = m_skillHolder->GetSkillAttribute();
			m_enemy_skill_2_Name = m_skillHolder->GetSkillName();
			m_enemy_skill_2_animTime = m_skillHolder->GetSkillAnimationTime();
			break;
		case 2:
			m_enemy_skill_3_Number = skillNumber;
			m_enemy_skill_3_DMG = m_skillHolder->GetSkillDMG();
			m_enemy_skill_3_HitRate = m_skillHolder->GetSkillHitRate();
			m_enemy_skill_3_AmountOfAttacks = m_skillHolder->GetSkillAmountOfAttacks();
			m_enemy_skill_3_Attribute = m_skillHolder->GetSkillAttribute();
			m_enemy_skill_3_Name = m_skillHolder->GetSkillName();
			m_enemy_skill_3_animTime = m_skillHolder->GetSkillAnimationTime();
			break;
		case 3:
			m_enemy_skill_4_Number = skillNumber;
			m_enemy_skill_4_DMG = m_skillHolder->GetSkillDMG();
			m_enemy_skill_4_HitRate = m_skillHolder->GetSkillHitRate();
			m_enemy_skill_4_AmountOfAttacks = m_skillHolder->GetSkillAmountOfAttacks();
			m_enemy_skill_4_Attribute = m_skillHolder->GetSkillAttribute();
			m_enemy_skill_4_Name = m_skillHolder->GetSkillName();
			m_enemy_skill_4_animTime = m_skillHolder->GetSkillAnimationTime();
			break;
		}
	}
	void BattleState::PlayersTurn(float deltatime)
	{
		if (m_turnDelayTime <= 0)
		{
			if (enemysTurn == true)
			{
				//activate windows for players turn here
				ManageWindow("SkillMenu", true);
			}
			enemysTurn = false;
			enemyAttacks = false;
			//escape key/open menu
			if (m_actions[ACTION_SELECT4] && optionsKeyIsPressed==false)
			{
					if (menu_is_up == false)
					{
						ManageWindow("OptionsMenu", true);
						ManageWindow("SkillMenu", false);
						menu_is_up = true;
					}
					else if (menu_is_up)
					{
						ManageWindow("OptionsMenu", false);
						ManageWindow("SkillMenu", true);
						menu_is_up = false;
					}

					optionsKeyIsPressed = true;
			}
			if (!m_actions[ACTION_SELECT4])
			{
				optionsKeyIsPressed=false; 
			}
		}
	}
	void BattleState::EnemysTurn(float deltatime)
	{
		//deactivate GUIWhen its players turn
		ManageWindow("OptionsMenu", false);
		ManageWindow("SkillMenu", false);
		enemysTurn = true;
		if (m_turnDelayTime <= 0)
		{
			enemyAttacks=true;
			EnemyUseSkill();
			std::cout << "Player has " << m_player_health << " health remaining " << std::endl;
			BattleStatusChecker();
		}
		
	}
	int BattleState::Random(int min, int max)
	{
		return min + (rand() % (max - min + 1));
	}
	void BattleState::EnemyUseSkill()
	{
		//randomize behavior for now
		int rnd = Random(0, 3);
		switch (rnd)
		{
		case 0:
			EnemyUseSkill_1();
			m_enemy_skill_1_sound.play();
			ChangeTurn(m_enemy_skill_1_animTime);
			aSkillEffect = new SkillEffect(m_enemy_skill_1_Name, m_enemy_skill_1_animTime, m_player_position,m_draw_manager);
			AllSkillEffects.push_back(*aSkillEffect);
			break;
		case 1:
			EnemyUseSkill_2();
			m_enemy_skill_2_sound.play();
			ChangeTurn(m_enemy_skill_2_animTime);
			aSkillEffect = new SkillEffect(m_enemy_skill_2_Name, m_enemy_skill_2_animTime, m_player_position,m_draw_manager);
			AllSkillEffects.push_back(*aSkillEffect);
			break;
		case 2:
			EnemyUseSkill_3();
			m_enemy_skill_3_sound.play();
			ChangeTurn(m_enemy_skill_3_animTime);
			aSkillEffect = new SkillEffect(m_enemy_skill_3_Name, m_enemy_skill_3_animTime, m_player_position, m_draw_manager);
			AllSkillEffects.push_back(*aSkillEffect);
			break;
		case 3:
			EnemyUseSkill_4();
			m_enemy_skill_4_sound.play();
			ChangeTurn(m_enemy_skill_4_animTime);
			aSkillEffect = new SkillEffect(m_enemy_skill_4_Name, m_enemy_skill_4_animTime, m_player_position, m_draw_manager);
			AllSkillEffects.push_back(*aSkillEffect);
			break;
		}
	}
	bool BattleState::CalculateSkillHit(float p_HitRate, float p_skillHitRate, float p_targetEvadeRate)
	{
		float totallHitRate = p_HitRate + p_skillHitRate;
		float calculatedHitRate = totallHitRate - p_targetEvadeRate;
		int rnd = Random(0, 100);
		if (rnd < calculatedHitRate)
		{
			std::cout << "HIT";
			return true;
		}
		else
		{
			std::cout << "MISS"<<std::endl;
			return false;
		}
	}
	float BattleState::CalculateSkillDamage(float p_DMG, float p_SkillDMG,std::string p_skillName)
	{
		float finalSkillDmg=0;
		
		finalSkillDmg=p_DMG+p_SkillDMG;
		std::cout <<p_skillName << " DEALS " << finalSkillDmg << " DMG" << std::endl;
		return finalSkillDmg;
	}
	void BattleState::EnemyUseSkill_1()
	{
		int amountOfHits = 0;
		float totallDMG=0;
		for (int i = 0; i < m_enemy_skill_1_AmountOfAttacks; i++)
		{
			if (CalculateSkillHit(m_enemy_hitrate, m_enemy_skill_1_HitRate, m_player_evadeRate))
			{
				amountOfHits++;
				if (m_enemy_skill_1_Attribute == "Offensive")
				{
					totallDMG= CalculateSkillDamage(m_enemy_damage, m_enemy_skill_1_DMG, m_enemy_skill_1_Name);
					m_player_health -= totallDMG;
				}
				else if (m_enemy_skill_1_Attribute == "Defensive")
				{
					std::cout << "Defensive moves does not work yet AI :(";
				}
			}
		}
		AddBattleSentence("Foe", m_enemy_skill_1_Name, amountOfHits, totallDMG);
	}
	void BattleState::EnemyUseSkill_2()
	{
		int amountOfHits = 0;
		float totallDMG=0;
		for (int i = 0; i < m_enemy_skill_2_AmountOfAttacks; i++)
		{
			if (CalculateSkillHit(m_enemy_hitrate, m_enemy_skill_2_HitRate, m_player_evadeRate))
			{
				amountOfHits++;
				if (m_enemy_skill_2_Attribute == "Offensive")
				{
					totallDMG = CalculateSkillDamage(m_enemy_damage, m_enemy_skill_2_DMG, m_enemy_skill_2_Name);
					m_player_health -= totallDMG;
				}
				else if (m_enemy_skill_2_Attribute == "Defensive")
				{
					std::cout << "Defensive moves does not work yet AI :(";
				}
			}
		}
		AddBattleSentence("Foe", m_enemy_skill_2_Name, amountOfHits, totallDMG);
		
	}
	void BattleState::EnemyUseSkill_3()
	{
		int amountOfHits = 0;
		float totallDMG=0;
		for (int i = 0; i < m_enemy_skill_3_AmountOfAttacks; i++)
		{
			if (CalculateSkillHit(m_enemy_hitrate, m_enemy_skill_3_HitRate, m_player_evadeRate))
			{
				amountOfHits++;
				if (m_enemy_skill_3_Attribute == "Offensive")
				{
					totallDMG = CalculateSkillDamage(m_enemy_damage, m_enemy_skill_3_DMG, m_enemy_skill_3_Name);
					m_player_health -= totallDMG;
				}
				else if (m_enemy_skill_3_Attribute == "Defensive")
				{
					std::cout << "Defensive moves does not work yet AI :(";
				}
			}
		}
		AddBattleSentence("Foe", m_enemy_skill_3_Name, amountOfHits, totallDMG);
	}
	void BattleState::EnemyUseSkill_4()
	{
		int amountOfHits = 0;
		float totallDMG=0;
		for (int i = 0; i < m_enemy_skill_4_AmountOfAttacks; i++)
		{
			if (CalculateSkillHit(m_enemy_hitrate, m_enemy_skill_4_HitRate, m_player_evadeRate))
			{
				amountOfHits++;
				if (m_enemy_skill_4_Attribute == "Offensive")
				{
					totallDMG = CalculateSkillDamage(m_enemy_damage, m_enemy_skill_4_DMG, m_enemy_skill_4_Name);
					m_player_health -= totallDMG;
				}
				else if (m_enemy_skill_4_Attribute == "Defensive")
				{
					std::cout << "Defensive moves does not work yet AI :(";
				}
			}
		}
		AddBattleSentence("Foe", m_enemy_skill_4_Name, amountOfHits, totallDMG);
	}
	void BattleState::PlayerUseSkill(int p_skillNumber)
	{
		int amountOfHits;
		float totallDMG=0;
		
		switch (p_skillNumber)
		{
			
		case 0:
			amountOfHits = 0;
			m_player_skill_1_sound.play();
			aSkillEffect = new SkillEffect(m_player_skill_1_Name, m_player_skill_1_animTime, enemyPos, m_draw_manager);
			AllSkillEffects.push_back(*aSkillEffect);
			for (int i = 0; i < m_player_skill_1_AmountOfAttacks; i++)
			{
				if (CalculateSkillHit(m_player_hitrate, m_player_skill_1_HitRate, m_enemy_evadeRate))
				{
					amountOfHits++;
					if (m_player_skill_1_Attribute == "Offensive")
					{
						totallDMG= CalculateSkillDamage(m_player_damage, m_player_skill_1_DMG, m_player_skill_1_Name);
						m_enemy_health -= totallDMG;
					}
					else if (m_player_skill_1_Attribute == "Defensive")
					{
						std::cout << "Defensive moves does not work yet AI :(";
					}
				}
			}
			std::cout << m_player_skill_1_Name << " Hit " << amountOfHits << " Times" << std::endl;
			
			AddBattleSentence("You",m_player_skill_1_Name, amountOfHits, totallDMG);
			
			break;
		case 1: 
			m_player_skill_2_sound.play();
			aSkillEffect = new SkillEffect(m_player_skill_2_Name, m_player_skill_2_animTime, enemyPos, m_draw_manager);
			AllSkillEffects.push_back(*aSkillEffect);
			amountOfHits = 0;
			for (int i = 0; i < m_player_skill_2_AmountOfAttacks; i++)
			{
				if (CalculateSkillHit(m_player_hitrate, m_player_skill_2_HitRate, m_enemy_evadeRate))
				{
					amountOfHits++;
					if (m_player_skill_2_Attribute == "Offensive")
					{
						totallDMG = CalculateSkillDamage(m_player_damage, m_player_skill_2_DMG, m_player_skill_2_Name);
						m_enemy_health -= totallDMG;
					}
					else if (m_player_skill_2_Attribute == "Defensive")
					{
						std::cout << "Defensive moves does not work yet AI :(";
					}
				}
			}
			AddBattleSentence("You", m_player_skill_2_Name, amountOfHits, totallDMG);
			break;
		case 2:
			amountOfHits = 0;
			aSkillEffect = new SkillEffect(m_player_skill_3_Name, m_player_skill_3_animTime, enemyPos, m_draw_manager);
			AllSkillEffects.push_back(*aSkillEffect);
			m_player_skill_3_sound.play();
			for (int i = 0; i < m_player_skill_3_AmountOfAttacks; i++)
			{
				if (CalculateSkillHit(m_player_hitrate, m_player_skill_3_HitRate, m_enemy_evadeRate))
				{
					amountOfHits++;
					if (m_player_skill_3_Attribute == "Offensive")
					{
						totallDMG = CalculateSkillDamage(m_player_damage, m_player_skill_3_DMG, m_player_skill_3_Name);
						m_enemy_health -= totallDMG;
					}
					else if (m_player_skill_3_Attribute == "Defensive")
					{
						std::cout << "Defensive moves does not work yet AI :(";
					}
				}
			}
			AddBattleSentence("You", m_player_skill_3_Name, amountOfHits, totallDMG);
			break;
		case 3:
			amountOfHits = 0;
			aSkillEffect = new SkillEffect(m_player_skill_4_Name, m_player_skill_4_animTime, enemyPos, m_draw_manager);
			AllSkillEffects.push_back(*aSkillEffect);
			m_player_skill_4_sound.play();
			for (int i = 0; i < m_player_skill_4_AmountOfAttacks; i++)
			{
				if (CalculateSkillHit(m_player_hitrate, m_player_skill_4_HitRate, m_enemy_evadeRate))
				{
					amountOfHits++;
					if (m_player_skill_4_Attribute == "Offensive")
					{
						totallDMG = CalculateSkillDamage(m_player_damage, m_player_skill_4_DMG, m_player_skill_4_Name);
						m_enemy_health -= totallDMG;
					}
					else if (m_player_skill_4_Attribute == "Defensive")
					{
						std::cout << "Defensive moves does not work yet AI :(";
					}
				}
			}
			AddBattleSentence("You", m_player_skill_4_Name, amountOfHits, totallDMG);
			break;
		}
	}
	void BattleState::BattleStatusChecker()
	{
		if (m_enemy_health <= 0)
		{
			//change state or screen 
			std::cout << "PLAYER WON FIGHT" << std::endl;
			m_playerWon = true;
			turnManager = TURN_OVER;
		}
		else if(m_player_health <= 0)
		{
			//change state to game over
			std::cout << "ENEMY WON FIGHT" << std::endl;
			m_enemyWon = true;
			turnManager = TURN_OVER;
		} 
	}
	void BattleState::InitBackground(std::string p_areaTheme)
	{
			if (!m_tex_battleBackground.loadFromFile("../assets/Sprites/Backgrounds/"+p_areaTheme+".png"))
			{
				std::cout << "failed to load the battlebackground";
			}
			m_spr_battleBackground.setTexture(m_tex_battleBackground);
	}
	void BattleState::InitLifeBars()
	{
		BS_LifeBar *m_playerLifeBar = new BS_LifeBar(this,m_player,sf::Vector2f(m_screen_width*0.7,m_screen_height*0.8));
		BS_LifeBar *m_enemyLifeBar = new BS_LifeBar(this,m_enemy,sf::Vector2f(m_screen_width*0.05,m_screen_height*0.05));
		AllLifeBars.push_back(*m_playerLifeBar);
		AllLifeBars.push_back(*m_enemyLifeBar);
	}
	void BattleState::AddBattleText(std::string p_battleText)
	{
		ssBT << p_battleText;
	}
	void BattleState::EmptyBattleText()
	{
		ssBT.str("");
	}
	void BattleState::AddBattleSentence(std::string p_user, std::string p_skillName, float p_amountOfHits, float p_totallDMG)
	{
		EmptyBattleText();
		std::stringstream ss;
		AddBattleText(p_user);
		AddBattleText(" Used ");
		AddBattleText(p_skillName);
		if (p_amountOfHits > 0)
		{


			AddBattleText(" Hit ");
			AddBattleText("\n");
			ss << p_amountOfHits;
			AddBattleText(ss.str());
			AddBattleText(" Times for ");
			ss.str("");
			ss << p_totallDMG*p_amountOfHits;
			AddBattleText(ss.str());
			AddBattleText(" DMG!");
		}
		else
		{
			AddBattleText("\n");
			AddBattleText(p_skillName);
			AddBattleText(" Was Evaded!");
		}
		SetBattleText();
	}
	void BattleState::SetBattleText()
	{
		text_battle_text.setString(ssBT.str());
	}
	void BattleState::InitBattleHUD()
	{
		GUIWindow *gUIWindow = new GUIWindow(this,m_player,m_enemy,"OptionsMenu",m_screen_width*0.3, m_screen_height*0.01, 120.0f, 50.0f, 130.0f,80.0f, 40, 1, 7);
		AllGUIWindows.push_back(*gUIWindow);

		gUIWindow = new GUIWindow(this, m_player, m_enemy, "SkillMenu", m_screen_width*0.3, m_screen_height*0.7, -100.0f, 10.0f, 135.0f, 45.0f, 30, 2, 2);
		AllGUIWindows.push_back(*gUIWindow);

		gUIWindow = new GUIWindow(this, m_player, m_enemy, "InventoryMenu", m_screen_width*0.3, m_screen_height*0.7, -100.0f, 10.0f, 135.0f, 45.0f, 16, 4, 4);
		AllGUIWindows.push_back(*gUIWindow);

		gUIWindow = new GUIWindow(this, m_player, m_enemy, "BattleLootWindow", m_screen_width*0.3, m_screen_height*0.1, 30, 30, 130, 50, 25, 1, 5);
		AllGUIWindows.push_back(*gUIWindow);

		

		if (!hudBattleFont.loadFromFile("../assets/Fonts/SuperMario256.ttf"))
		{
			std::cout << "Failed to load font" << std::endl;
		}
		//players health displayed
		text_player_health.setFont(hudBattleFont);
		text_player_health.setPosition(m_screen_width*0.7, m_screen_height * 0.84f);
		text_player_health.setColor(sf::Color::Red);
		text_player_health.setCharacterSize(39);
		text_player_health.setStyle(sf::Text::Bold | sf::Text::Italic);
		//enemies health displayed
		text_enemy_health.setFont(hudBattleFont);
		text_enemy_health.setPosition(m_screen_width*0.2, m_screen_height * 0.1f);
		text_enemy_health.setColor(sf::Color::Red);
		text_enemy_health.setCharacterSize(39);
		text_enemy_health.setStyle(sf::Text::Bold | sf::Text::Italic);
		ManageWindow("BattleLootWindow", false);
		//Enemys Name 
		text_enemy_name.setFont(hudBattleFont);
		text_enemy_name.setPosition(m_screen_width*0.01, m_screen_height * 0.01f);
		text_enemy_name.setColor(sf::Color::Red);
		text_enemy_name.setCharacterSize(39);
		text_enemy_name.setStyle(sf::Text::Bold | sf::Text::Italic);
		//battle text
		text_battle_text.setFont(hudBattleFont);
		text_battle_text.setPosition(m_screen_width*0.65, m_screen_height * 0.7f);
		text_battle_text.setColor(sf::Color::Black);
		text_battle_text.setCharacterSize(25);
		text_battle_text.setStyle(sf::Text::Bold | sf::Text::Italic);
	}
	void BattleState::UpdateBattleHUD(float deltatime)
	{
		for (unsigned int i = 0; i<AllGUIWindows.size(); i++)
		{
			AllGUIWindows[i].Update(deltatime);
		}
		for (unsigned int i = 0; i < AllLifeBars.size(); i++)
		{
			AllLifeBars[i].Update(deltatime);
		}
		std::stringstream ss;
		ss << m_player_health;
		text_player_health.setString(ss.str());
		ss.str("");
		ss << m_enemy_health;
		text_enemy_health.setString(ss.str());
		ss.str("");
		ss << m_enemy_name;
		text_enemy_name.setString(ss.str());
	}
	void BattleState::ChangeTurn(float p_turnDelayTime)
	{
		m_turnDelayTime = p_turnDelayTime;
		
			if (turnManager == TURN_PLAYER)
			{
				turnManager = TURN_ENEMY;
			}
			else if (turnManager == TURN_ENEMY)
			{
				turnManager = TURN_PLAYER;
			}
	}
}
 // namespace spaceshooter
