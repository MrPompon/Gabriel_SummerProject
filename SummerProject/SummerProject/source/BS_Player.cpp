// BS_Player.cpp

#include "stdafx.h"
#include "BS_Player.hpp"
#include <iostream>
namespace spaceshooter
{
	std::vector<std::string> explode(const std::string& string, const std::string& delimeter)
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
	BS_Player::~BS_Player()
	{
	}
		
	BS_Player::BS_Player(std::string filename)
	{
		LoadPlayerStatus(filename);
	}
	void BS_Player::LoadPlayerStatus(std::string filename)
	{
		std::ifstream inputStream("../assets/save_files/" + filename);
		if (!inputStream.is_open())
		{
			std::cout << "Failed to load playerStats: Could not open file '" << filename << "'" << std::endl;
		}
		std::cout << "save file (../assets/save_files/ ) " + filename + " opened" << std::endl;
		std::string line;
		std::vector<std::string> parts;
		int currentRow = 0;
		while (std::getline(inputStream, line))
		{
			//seperates a line to an array and makes everyword a seperate index
			parts = explode(line, " ");
			//checks the first string index of the lines
			if (parts[0] == "[NAME]")
			{
				m_character_name = parts[1];
				std::cout << m_character_name << std::endl;
			}
			if (parts[0] == "[HP]")
			{
				m_health = std::stof(parts[1]); //converts string to float
				std::cout << m_health << std::endl;
			}
			if (parts[0] == "[DMG]")
			{
				m_damage = std::stof(parts[1]); 
				std::cout << m_damage << std::endl;
			}
			if (parts[0] == "[SPEED]")
			{
				m_speed = std::stof(parts[1]);
				std::cout << m_speed << std::endl;
			}
			if (parts[0] == "[EVADERATE]")
			{
				m_evadeRate = std::stof(parts[1]); 
				std::cout << m_speed << std::endl;
			}
			if (parts[0] == "[SKILLS]")
			{
				for (unsigned int i = 1; i < parts.size(); i++)
				{
					m_playerSkills.push_back(parts[i]);
				}
			}
		}
	}
	float BS_Player::GetDMG()
	{
		return m_damage;
	}
	float BS_Player::GetHealth()
	{
		return m_health;
	}
	float BS_Player::GetSpeed()
	{
		return m_speed;
	}
	float BS_Player::GetEvadeRate()
	{
		return m_evadeRate;
	}
	std::vector<std::string> BS_Player::GetPlayerSkills()
	{
		return m_playerSkills;
	}
} // namespace spaceshooter
