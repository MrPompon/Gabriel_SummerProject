// BS_Skills.cpp

#include "stdafx.h"
#include "BS_Skills.hpp"
#include <iostream>
namespace spaceshooter
{
	std::vector<std::string> explodeSkill(const std::string& string, const std::string& delimeter)
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
	BS_Skills::~BS_Skills()
	{
	}

	BS_Skills::BS_Skills()
	{
		
	}
	void BS_Skills::LoadSkill(std::string filename,std::string skillname)
	{
		std::ifstream inputStream("../assets/skill_files/" + filename+".txt");
		if (!inputStream.is_open())
		{
			std::cout << "Failed to load playerStats: Could not open file '" << filename << "'" << std::endl;
		}
		std::cout << "save file (../assets/skill_files/ " + filename + " opened for the skill "+skillname << std::endl;
		std::string line;
		std::vector<std::string> parts;
		int currentRow = 0;
		while (std::getline(inputStream, line))
		{
			//seperates a line to an array and makes everyword a seperate index
			parts = explodeSkill(line, " ");
			//checks the first string index of the lines
			if (parts[0] == "["+skillname+"]")
			{
				m_skillName= parts[1];
				m_skillAttribute = parts[2];
				m_skillDMG = std::stof(parts[3]);
				m_skillHitRate =std::stof(parts[4]);
				m_skillTimesHit = std::stoi(parts[5]);
				m_skillProc = parts[6];
			}
			
		}
	}
	std::string BS_Skills::GetSkillAttribute()
	{
		return m_skillAttribute;
	}
	float BS_Skills::GetSkillDMG()
	{
		return m_skillDMG;
	}
	float BS_Skills::GetSkillHitRate()
	{
		return m_skillHitRate;
	}
	float BS_Skills::GetSkillAmountOfAttacks()
	{
		return m_skillTimesHit;
	}
	std::string BS_Skills::GetSkillName()
	{
		return m_skillName;
	}

} // namespace spaceshooter
