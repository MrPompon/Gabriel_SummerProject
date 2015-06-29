// BS_Enemy.hpp

#ifndef BS_ENEMY_HPP_INCLUDED
#define BS_ENEMY_HPP_INCLUDED

namespace spaceshooter
{
	class TextureManager;
	class BattleState;
	class BS_Enemy: public sf::Drawable
	{
	public:
		BS_Enemy(std::string enemyName, BattleState*p_BattleState);
		~BS_Enemy();
		std::vector<std::string> GetEnemySkills();
		void LoadEnemyStatus(std::string p_filename);
		float GetHealth();
		float GetDMG();
		float GetSpeed();
		float GetHitRate();
		float GetEvadeRate();
		void Update(float deltatime);
		bool WaitForDelay(float &delayTime);
		int Random(int min, int max);
		int GetLoot();
		std::string GetName();
		void InitEnemySprite(std::string p_enemy_spriteName);
		void LoadImageFile(std::string p_enemy_name);
		void DestroySpriteEffect(float deltatime);
		void AttackMoveSprite(float deltatime);
		void draw(sf::RenderTarget &target, sf::RenderStates states) const;
	private:
		void InitAudio();
		//stats
		float timeBeforeTurnBack;
		bool m_visible;
		float m_enemyAlpha;
		int m_beforeDestroyed;
		float m_delayTime;
		BattleState *m_battleState;
		float m_screen_width;
		float m_screen_height;
		float m_enemyPosX;
		float m_enemyPosY;
		sf::Sprite m_spr_enemy_creature;
		sf::Texture *m_tex_enemy_creature;
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
