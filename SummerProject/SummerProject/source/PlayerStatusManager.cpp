#include "stdafx.h"
#include <iostream>

#include "ServiceLocator.hpp"
#include "PlayerStatusManager.hpp"
namespace spaceshooter
{

	std::vector<std::string> explodestatus(const std::string& string, const std::string& delimeter)
	{
		std::vector<std::string> parts;
		std::size_t oldPos = 0;
		while (true){
			std::size_t newPos = string.find(delimeter, oldPos);
			if (newPos == std::string::npos){
				parts.push_back(string.substr(oldPos, newPos - oldPos));
				break;
			}
			parts.push_back(string.substr(oldPos, newPos - oldPos));
			oldPos = newPos + 1;
		}
		return parts;
	}
	PlayerStatusManager::PlayerStatusManager()
	{
		LoadPlayerStatus("save_file_1.txt");
		playerPosition.x = 16;
		playerPosition.y = 16;
		m_playerEXP = 0;
		m_playerGold = 0;
		CurrentLevel = 1;
	}
	PlayerStatusManager::~PlayerStatusManager()
	{

	}
	bool PlayerStatusManager::Initialize()
	{
		return false;
	}
	void PlayerStatusManager::Update(float deltatime)
	{
	
	}
	void PlayerStatusManager::LoadPlayerStatus(std::string fileName)
	{
			std::ifstream inputStream("../assets/save_files/" + fileName);
			if (!inputStream.is_open()){
				std::cout << "Failed to load playerStats: Could not open file '" << fileName << "'" << std::endl;
			}
			std::cout << "save file (../assets/save_files/ ) " + fileName + " opened" << std::endl;
			std::string line;
			std::vector<std::string> parts;
			int currentRow = 0;
			while (std::getline(inputStream, line)){
				//seperates a line to an array and makes everyword a seperate index
				parts = explodestatus(line, " ");
				//checks the first string index of the lines
				if (parts[0] == "[NAME]"){
					m_player_name = parts[1];
					std::cout << m_player_name << std::endl;
				}
				if (parts[0] == "[HP]"){
					m_playerMaxHealth = std::stof(parts[1]); //converts string to float
					std::cout << m_playerMaxHealth << std::endl;
				}
				if (parts[0] == "[DMG]"){
					m_playerDamage = std::stof(parts[1]);
					std::cout << m_playerDamage << std::endl;
				}
				if (parts[0] == "[SPEED]"){
					m_playerSpeed = std::stof(parts[1]);
					std::cout << m_playerSpeed << std::endl;
				}
				if (parts[0] == "[EVADERATE]"){
					m_playerEvadeRate = std::stof(parts[1]);
					std::cout << m_playerSpeed << std::endl;
				}
				if (parts[0] == "[HITRATE]"){
					m_playerHitRate = std::stof(parts[1]);
				}
			
			}
			m_playerCurrentHealth = m_playerMaxHealth;
			areaName = "OverWorld1_1";
		}
	void PlayerStatusManager::LevelUp()
	{	
			m_playerMaxHealth *= 1.15;
			AddStat("DMG", 50);
			AddStat("HitRate", 5);
			m_playerCurrentHealth = m_playerMaxHealth; //gives the player max hp
			CurrentLevel++;
			
	}
	void PlayerStatusManager::CheckEXP()
	{
		EXPNeeded = (CurrentLevel * 100);

		std::cout << EXPNeeded << " " << m_playerEXP;
		if (m_playerEXP >= EXPNeeded){
			LevelUp();
			m_playerEXP = 0;
		}
	}
	float PlayerStatusManager::GetStat(std::string statName)
	{
		if (statName == "Gold"){
			return m_playerGold;
		}else if(statName=="HP"){
			return m_playerCurrentHealth;
		}else if (statName == "EXP"){
			return m_playerEXP;
		}else if (statName == "MaxHealth"){
			return m_playerMaxHealth;
		}else if (statName == "DMG"){
			return m_playerDamage;
		}else if (statName == "HitRate"){
			return m_playerHitRate;
		}else if (statName == "EvadeRate"){
			return m_playerEvadeRate;
		}else if (statName == "Speed"){
			return m_playerSpeed;
		}
	}
	void  PlayerStatusManager::SetStat(std::string statName,int amount)
	{
		if (statName == "Gold"){
			m_playerGold = amount;
		}else if (statName == "HP"){
			m_playerCurrentHealth = amount;
		}else if (statName == "EXP"){
			m_playerEXP = amount;
		}else if (statName == "MaxHealth"){
			m_playerMaxHealth = amount;
		}
	}
	void PlayerStatusManager::AddStat(std::string statName, float amount)
	{
		if (statName == "Gold"){
			m_playerGold += amount;
		}else if (statName == "HP"){
			m_playerCurrentHealth += amount;
		}else if (statName == "EXP"){
			m_playerEXP += amount;
		}else if (statName == "MaxHealth"){
			m_playerMaxHealth += amount;
		}else if (statName == "DMG"){
			m_playerDamage += amount;
		}else if (statName == "HitRate"){
			m_playerHitRate += amount;
		}else if (statName == "EvadeRate"){
			m_playerEvadeRate += amount;
		}else if (statName == "Speed"){
			m_playerSpeed += amount;
		}
	}
	sf::Vector2f PlayerStatusManager::GetPlayerPosition()
	{
		return playerPosition;
	}
	void PlayerStatusManager::SetPlayerPosition(sf::Vector2f position)
	{
		playerPosition = position;
	}
	std::string PlayerStatusManager::GetAreaName()
	{
		return areaName;
	}
	void PlayerStatusManager::SetAreaName(std::string p_areaName)
	{
		areaName = p_areaName;
	}
}