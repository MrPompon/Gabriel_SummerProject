// BS_Enemy.cpp

#include "stdafx.h"
#include "BS_Enemy.hpp"
#include "BattleState.hpp"
#include <iostream>
#include "TextureManager.hpp"
#include "ServiceLocator.hpp"
#include "AudioManager.hpp"
namespace spaceshooter
{
	std::vector<std::string> explode1(const std::string& string, const std::string& delimeter)
	{
		std::vector<std::string> parts;
		std::size_t oldPos = 0;
		while (true)
		{
			std::size_t newPos = string.find(delimeter, oldPos);
			if (newPos == std::string::npos)
			{
				parts.push_back(string.substr(oldPos, newPos - oldPos));
				break;
			}
			parts.push_back(string.substr(oldPos, newPos - oldPos));
			oldPos = newPos + 1;
		}
		return parts;
	}
	BS_Enemy::BS_Enemy(std::string enemyName, BattleState*p_BattleState)
	{
		m_battleState = p_BattleState;
		m_screen_width = 1024.0f;
		m_screen_height = 600.0f;
		m_enemyPosX = m_screen_width*0.5;
		m_enemyPosY = m_screen_height*0.1;
		std::string enemy_stat_file = "../assets/enemy_table/" + enemyName+".txt";
		LoadEnemyStatus(enemy_stat_file);
		LoadImageFile(enemyName);
	}
	float BS_Enemy::GetDMG()
	{
		return m_damage;
	}
	void BS_Enemy::DestroySpriteEffect(float deltatime)
	{
		m_delayTime -= deltatime;
		if (WaitForDelay(m_delayTime))
		{
			m_enemyAlpha -= 5;
			m_beforeDestroyed++;
			sf::Vector2f vibrationPosition;
			vibrationPosition.x = m_enemyPosX - Random(-10, 10);
			vibrationPosition.y = m_enemyPosY;
			vibrationPosition.y++;
			m_spr_enemy_creature.setColor(sf::Color(255,255,255,m_enemyAlpha));
			m_spr_enemy_creature.setPosition(vibrationPosition.x, vibrationPosition.y);
			m_delayTime = 0.05;
			if (m_beforeDestroyed >= 45)
			{
				m_visible = false;
			}
		}
	}
	int BS_Enemy::Random(int min, int max)
	{
		return min + (rand() % (max - min + 1));
	}
	bool BS_Enemy::WaitForDelay(float &delayTime)
	{
		if (delayTime < 0)
		{
			return true;
		}
		else
		{
			return false;
		}
	}
	float BS_Enemy::GetHealth()
	{
		return m_health;
	}
	int BS_Enemy::GetLoot()
	{
		return m_loot;
	}
	void BS_Enemy::InitEnemySprite(std::string p_enemy_spriteName)
	{
		LoadImageFile(p_enemy_spriteName);
	}
	void BS_Enemy::LoadImageFile(std::string p_enemy_name)
	{
		TextureManager* texture_manager = ServiceLocator<TextureManager>::GetService();
		m_tex_enemy_creature = texture_manager->CreateTextureFromFile("../assets/Sprites/Enemy_BS/" + m_enemy_name + "_BS_SPR.png");
		m_spr_enemy_creature.setTexture(*m_tex_enemy_creature);
		m_spr_enemy_creature.setPosition(m_enemyPosX,m_enemyPosY);
	}
	void BS_Enemy::Update(float deltatime)
	{
		if (m_battleState->m_enemy_health<=0)
		{
			DestroySpriteEffect(deltatime);
		}
		if (m_battleState->enemyAttacks == true)
		{
			AttackMoveSprite(deltatime);
		}
		else
		{
			timeBeforeTurnBack = 1.0f;
			if (!m_battleState->m_enemy_health <= 0)
			{
				m_spr_enemy_creature.setPosition(m_enemyPosX, m_enemyPosY);
			}
		
		}
	}
	void BS_Enemy::draw(sf::RenderTarget &target, sf::RenderStates states) const
	{
		if (m_visible)
		{
			states.texture = m_tex_enemy_creature;
			target.draw(m_spr_enemy_creature, states);
		}
	}
	float BS_Enemy::GetHitRate()
	{
		return m_hitrate;
	}
	std::string BS_Enemy::GetName()
	{
		return m_enemy_name;
	}
	float BS_Enemy::GetSpeed()
	{
		return m_speed;
	}
	float BS_Enemy::GetEvadeRate()
	{
		return m_evadeRate;
	}
	BS_Enemy::~BS_Enemy()
	{
	}
	std::vector<std::string>BS_Enemy::GetEnemySkills()
	{
		return m_enemySkills;
	}
	void BS_Enemy::LoadEnemyStatus(std::string p_filename)
	{
		timeBeforeTurnBack = 1.0f;
		m_enemyAlpha = 255;
		m_beforeDestroyed = 0;
		m_visible = true;
		std::ifstream inputStream(p_filename);
		if (!inputStream.is_open())
		{
			std::cout << "Failed to load enemy stats: Could not open file '" << p_filename << "'" << std::endl;
		}
		std::cout << "enemy stat (../assets/enemy_table/ ) " + p_filename + " opened" << std::endl;
		std::string line;
		std::vector<std::string> parts;
		int currentRow = 0;
		while (std::getline(inputStream, line))
		{
			//seperates a line to an array and makes everyword a seperate index
			parts = explode1(line, " ");
			//checks the first string index of the lines
			if (parts[0] == "[NAME]")
			{
				m_enemy_name = parts[1];
			}
			if (parts[0] == "[LOOT]")
			{
				m_loot =std::stoi(parts[1]);
				std::cout <<m_enemy_name<<" has "<< m_loot<< " amount of gold" << std::endl;
			}
			if (parts[0] == "[HP]")
			{
				m_health = std::stof(parts[1]); //converts string to float
				std::cout <<"has "<< m_health<<" health" << std::endl;
			}
			if (parts[0] == "[DMG]")
			{
				m_damage = std::stof(parts[1]); //converts string to float
				std::cout <<" has "<< m_damage<<" DMG" << std::endl;
			}
			if (parts[0] == "[SPEED]")
			{
				m_speed = std::stof(parts[1]); //converts string to float
				std::cout <<"has "<< m_speed <<" speed"  << std::endl;
			}
			if (parts[0] == "[SKILLS]")
			{
				m_enemySkills.push_back(parts[1]);
				m_enemySkills.push_back(parts[2]);
				m_enemySkills.push_back(parts[3]);
				m_enemySkills.push_back(parts[4]);
			}
			if (parts[0] == "[HITRATE]")
			{
				m_hitrate = std::stof(parts[1]);
				std::cout << "has " << m_hitrate << " HitRate" << std::endl;
			}
			if (parts[0] == "[EVADERATE]")
			{
				m_evadeRate = std::stof(parts[1]);
			}
		}
	}
	void BS_Enemy::AttackMoveSprite(float deltatime)
	{
		timeBeforeTurnBack-=deltatime;
		if (timeBeforeTurnBack <= -1 &&! m_battleState->m_enemy_health <= 0)
		{
			m_spr_enemy_creature.setPosition(m_enemyPosX, m_enemyPosY);
		}
		if (timeBeforeTurnBack > 0)
		{
			m_spr_enemy_creature.move(-4, 3);
		}
		else if (timeBeforeTurnBack < 0)
		{
			m_spr_enemy_creature.move(4, -3);
		}
	}
	void BS_Enemy::InitAudio()
	{
		AudioManager* audio_manager = ServiceLocator<AudioManager>::GetService();
		//audio_manager->CreateSoundFromFile("../assets/Audio/Enemy/")
	}
} // namespace spaceshooter
