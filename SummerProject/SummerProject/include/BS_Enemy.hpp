// BS_Enemy.hpp

#ifndef BS_ENEMY_HPP_INCLUDED
#define BS_ENEMY_HPP_INCLUDED

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
		float GetHitRate();
		float GetEvadeRate();
		int GetLoot();
		std::string GetName();
	private:
		
		//stats
		std::string m_enemy_name;
		float m_health;
		float m_speed;
		float m_hitrate;
		float m_damage;
		float m_evadeRate;
		int m_loot;
		std::vector<std::string> m_enemySkills;
	};
} // namespace spaceshooter

#endif // BS_Enemy_HPP_INCLUDED
