// BS_Skills.hpp

#ifndef BS_Skills_HPP_INCLUDED
#define BS_Skills_HPP_INCLUDED

namespace spaceshooter
{
	class BS_Skills
	{
	public:
		~BS_Skills();
		BS_Skills();
		std::string GetSkillAttribute();
		std::string GetSkillName();
		float GetSkillDMG();
		float GetSkillHitRate();
		float GetSkillAmountOfAttacks();
		float GetSkillAnimationTime();

		void LoadSkill(std::string p_filename, std::string skillname);
	private:
		enum SkillEffect
		{
			EFFECT_Poison,
			EFFECT_Stun,
		};
		SkillEffect skillEffectEnum; 
		//stats
		std::string m_skillProc;
		std::string m_skillAttribute;
		std::string m_character_name;
		std::string m_skillName;
		std::string m_skillEffect;
		float m_skillAnimationTime;
		float m_skillDMG;
		float m_skillHitRate;
		int m_skillTimesHit;
	};
} // namespace spaceshooter

#endif // BS_Skills_HPP_INCLUDED
