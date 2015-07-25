//PlayerStatusManager.hpp

#ifndef PlayerStatusManager_HPP_INCLUDED
#define PlayerStatusManager_HPP_INCLUDED


namespace spaceshooter
{
	

	class PlayerStatusManager
	{
		PlayerStatusManager(const PlayerStatusManager&);
		PlayerStatusManager& operator=(const PlayerStatusManager&);
	public:
		
		PlayerStatusManager();
		~PlayerStatusManager();
		void Update(float deltatime);
		void LoadPlayerStatus(std::string fileName);
		bool Initialize();
		float GetStat(std::string statName);
		void SetStat(std::string statName, int amount);
		void AddStat(std::string statName, float stat);
		sf::Vector2f GetPlayerPosition();
		void SetPlayerPosition(sf::Vector2f);
		void SetAreaName(std::string areaName);
		std::string GetAreaName();
		void CheckEXP();
	private:
		void LevelUp();
		int CurrentLevel;
		int EXPNeeded;

		sf::Vector2f playerPosition;
		std::string areaName;
		float m_playerMaxHealth;
		float m_playerCurrentHealth;
		float m_playerEXP;
		float m_playerGold;
		float m_playerDamage;
		float m_playerSpeed;
		float m_playerEvadeRate;
		float m_playerHitRate;
		std::string m_player_name;
	};
}// namespace spaceshooter

#endif // PlayerStatusManager_HPP_INCLUDED