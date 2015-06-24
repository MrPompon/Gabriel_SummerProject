// BS_Player.hpp

#ifndef DRAWABLE_HPP_INCLUDED
#define DRAWABLE_HPP_INCLUDED

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
		void LoadPlayerStatus(std::string p_filename);
	private:
		

		//stats
		std::string m_character_name;
		float m_health;
		float m_speed;
		float m_damage;
		float m_evadeRate;
	};
} // namespace spaceshooter

#endif // BS_Player_HPP_INCLUDED
