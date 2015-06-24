// BS_Enemy.cpp

#include "stdafx.h"
#include "BS_Enemy.hpp"
#include <iostream>
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
	BS_Enemy::BS_Enemy(std::string enemyName)
	{
		std::string enemy_stat_file = "../assets/enemy_table/" + enemyName+".txt";
		LoadEnemyStatus(enemy_stat_file);
	}
	float BS_Enemy::GetDMG()
	{
		return m_damage;
	}
	float BS_Enemy::GetHealth()
	{
		return m_health;
	}
	int BS_Enemy::GetLoot()
	{
		return m_loot;
	}
	
	std::string BS_Enemy::GetName()
	{
		return m_enemy_name;
	}
	float BS_Enemy::GetSpeed()
	{
		return m_speed;
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
		}
	}
} // namespace spaceshooter
