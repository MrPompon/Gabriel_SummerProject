// BS_Player.hpp

#ifndef BS_Player_HPP_INCLUDED
#define BS_Player_HPP_INCLUDED

namespace spaceshooter
{
	class BS_Player
	{
	public:
		~BS_Player();
		BS_Player(std::string filename);
		float GetHealth();
		float GetDMG();
		float GetSpeed();
		float GetEvadeRate();
		float GetHitRate();
		std::vector<std::string> GetPlayerSkills();
		void LoadPlayerStatus(std::string p_filename);
	private:
		//stats
		std::vector<std::string> m_playerSkills;
		std::string m_character_name;
		float m_health;
		float m_speed;
		float m_damage;
		float m_evadeRate;
		float m_hitrate;
	};
} // namespace spaceshooter

#endif // BS_Player_HPP_INCLUDED
