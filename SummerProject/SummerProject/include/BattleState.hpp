// BattleState.hpp

#ifndef BATTLESTATE_HPP_INCLUDED
#define BATTLESTATE_HPP_INCLUDED

#include "AbstractState.hpp"

namespace spaceshooter
{
	class DrawManager;
	class BS_Player;
	class BS_Enemy;
	class BS_Skills;
	class BattleState : public AbstractState
	{
	public:
		BattleState();
		~BattleState();

		virtual bool Enter();
		virtual void Exit();
		virtual bool Update(float deltatime);
		virtual void Draw();
		virtual std::string GetNextState();

	private:
		void OnAction(const std::string& action, bool state);
		//Overall and skills
		void InitSkillEnemy(std::string skillname, int skillNumber);
		void BattleManager(float deltatime);
		
		//player funtions
		void UpdatePlayer(float deltatime);
		void PlayersTurn(float deltatime);
		void InitPlayerStats();
		void FirstStrikeDecider();
		//enemy functions
		void EnemysTurn(float deltatime);
		void InitEnemyStats();
	private:
		DrawManager* m_draw_manager;

		float m_screen_width;
		float m_screen_height;
		//textures pointers etc 
		// player
		sf::Texture* m_player_texture;
		sf::Sprite m_player_sprite;
		sf::Vector2f m_player_position;
		sf::Vector2f m_player_velocity;
		sf::Vector2f m_player_direction;
		std::string player_saveFile;
		std::string enemy_encounter_name;
		bool playersTurn;
		BS_Player*m_player;
		//enemy
		bool enemysTurn;

		//battle stats
		BS_Skills* m_skillHolder;
		int currentSelectedOption;
		int AmountOfOptionsInMenu1;
		int AmountOfOptionsInMenu2;
		int AmountOfOptionsInSkillScreen;
		//player
		float m_player_health;
		float m_player_damage;
		float m_player_speed;
		std::string m_player_name;
		//enemy
		float m_enemy_health;
		float m_enemy_damage;
		float m_enemy_speed;
		int m_enemy_loot;
		std::string m_enemy_name;
		std::vector<std::string> m_enemySkills;
		BS_Enemy*m_enemy;
		void EnemyUseSkill();
		//temp solution to save ablitiy stats, cant come up with a better way 
		//skill 1
		int m_enemy_skill_1_Number;
		float m_enemy_skill_1_DMG;
		float m_enemy_skill_1_HitRate;
		int m_enemy_skill_1_AmountOfAttacks;
		std::string m_enemy_skill_1_Attribute;
		std::string m_enemy_skill_1_Name;
		//skill 2
		int m_enemy_skill_2_Number;
		float m_enemy_skill_2_DMG;
		float m_enemy_skill_2_HitRate;
		int m_enemy_skill_2_AmountOfAttacks;
		std::string m_enemy_skill_2_Attribute;
		std::string m_enemy_skill_2_Name;
		//skill 3
		int m_enemy_skill_3_Number;
		float m_enemy_skill_3_DMG;
		float m_enemy_skill_3_HitRate;
		int m_enemy_skill_3_AmountOfAttacks;
		std::string m_enemy_skill_3_Attribute;
		std::string m_enemy_skill_3_Name;
		//skill 4 
		int m_enemy_skill_4_Number;
		float m_enemy_skill_4_DMG;
		float m_enemy_skill_4_HitRate;
		int m_enemy_skill_4_AmountOfAttacks;
		std::string m_enemy_skill_4_Attribute;
		std::string m_enemy_skill_4_Name;
		// sound
		sf::Sound m_sound;
		// note(tommi): code for actions will be refactored
		// into a player controller class
		enum TurnManager
		{
			TURN_PLAYER,
			TURN_ENEMY,
		};
		TurnManager turnManager;

		enum BattleHUD
		{
			MENU_FIRST,
			MENU_SKILLS,
			MENU_ITEMS,
		};
		BattleHUD battleHUD;

		enum
		{
			ACTION_LEFT,
			ACTION_RIGHT,
			ACTION_UP,
			ACTION_DOWN,
			ACTION_FIRE,
			ACTION_ALT_FIRE,
			ACTION_SELECT1,
			ACTION_SELECT2,
			ACTION_SELECT3,
			ACTION_SELECT4,
			ACTION_COUNT
		};
		bool m_actions[ACTION_COUNT];
	};
} // namespace spaceshooter

#endif // BATTLESTATE_HPP_INCLUDED
