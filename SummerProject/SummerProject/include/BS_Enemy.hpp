// BS_Enemy.hpp

#ifndef BS_Enemy_HPP_INCLUDED
#define BS_Enemy_HPP_INCLUDED

namespace spaceshooter
{
	class BS_Enemy
	{
	public:
		BS_Enemy(std::string enemyName);
		~BS_Enemy();
		std::vector<std::string> GetEnemySkills();
		void LoadEnemyStatus(std::string p_filename);
		float GetHealth();
		float GetDMG();
		float GetSpeed();
		int GetLoot();
		std::string GetName();
	private:
		
		//stats
		std::string m_enemy_name;
		float m_health;
		float m_speed;
		float m_damage;
		int m_loot;
		std::vector<std::string> m_enemySkills;
	};
} // namespace spaceshooter

#endif // BS_Enemy_HPP_INCLUDED
