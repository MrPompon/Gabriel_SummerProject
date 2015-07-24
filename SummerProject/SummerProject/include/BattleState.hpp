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
	class GUIWindow;
	class BS_LifeBar;
	class SkillEffect;
	class ScreenEffects;
	class PlayerStatusManager;

	class BattleState : public AbstractState
	{
		friend class GUIWindow;
		friend class BS_LifeBar;
		friend class BS_Enemy;
	public:
		BattleState(std::string p_areaTheme, std::string p_encounterName, std::string p_timeOfDay);
		~BattleState();

		virtual bool Enter();
		virtual void Exit();
		virtual bool Update(float deltatime);
		virtual void Draw();
		virtual std::string GetNextState();
		void SetBattleText();
		void AddBattleText(std::string p_battleText);
		void EmptyBattleText();
		void AddBattleSentence(std::string p_user, std::string p_skillName, float p_amoutOfHits, float p_totallDMG);
	private: //battle background stuff
		sf::Texture m_tex_battleBackground;
		sf::Sprite m_spr_battleBackground;
		std::stringstream ssBT;
		void InitBackground(std::string p_areaTheme);
	private:
		//All Combat font
		bool menu_is_up;
		sf::RenderWindow *m_window;
		sf::View m_view;
		bool optionsKeyIsPressed;
		//player
		sf::Text text_player_health, text_player_damage;
		//enemy
		sf::Text text_enemy_health, text_enemy_damage; 
		sf::Text text_enemy_name;
		sf::Text text_battle_text;
	private:
		void OnAction(const std::string& action, bool state);
		//audio stuff
		std::string m_battleTheme;
		void InitAudio(std::string p_battleTheme);
		sf::Music *m_music;
		sf::Music *m_music_victory;
		bool m_music_victoryPlaying;
		sf::Music* BS_Music;
		sf::Music* BS_Music_Victory;
		//Overall and skills
		void ManageWindow(std::string windowName, bool trueOrFalse);
		void InitSkillEnemy(std::string skillname, int skillNumber);
		void InitSkillPlayer(std::string skillname, int skillNumber);
		void BattleManager(float deltatime);
		void BattleStatusChecker();
		void UpdateBattleHUD(float deltatime);
		void InitBattleHUD();
		void InitLifeBars();
		bool CalculateSkillHit(float enemyHitRate, float skillHitRate, float playerEvadeRate);
		float CalculateSkillDamage(float DMG, float SkillDMG, std::string p_skillName);
		void ChangeTurn(float p_turnDelayTime);
		//player funtions
		void SetCombatEndStats(float hp, float exp, float gold);
		void PlayersTurn(float deltatime);
		void InitPlayerStats();
		void FirstStrikeDecider();
		void CheckMousePosition(float deltatime);
		void PlayerUseSkill(int p_skillNumber);
		//enemy functions
		sf::Vector2f enemyPos;
		void EnemysTurn(float deltatime);
		void InitEnemyStats();
		std::string m_areaTheme;
		std::string m_encounterName;
	private:
		bool m_battleOver;
		sf::Mouse m_mouse;
		std::vector<GUIWindow> AllGUIWindows;
		std::vector<BS_LifeBar> AllLifeBars;
		std::vector<SkillEffect> AllSkillEffects;
		ScreenEffects* m_screenEffect;
		std::vector<ScreenEffects> AllScreenEffects;
		SkillEffect* aSkillEffect;
		DrawManager* m_draw_manager;
		float m_turnDelayTime;
		int Random(int min, int max);
		float m_screen_width;
		float m_screen_height;
		sf::Font hudBattleFont;
		bool m_enemyWon;
		bool m_playerWon;
		sf::Sound lootSound;
		//textures pointers etc 
		// player
		sf::Texture* m_player_texture;
		sf::Sprite m_player_sprite;
		sf::Vector2f m_player_position;
		std::string player_saveFile;
		std::string enemy_encounter_name;
		bool playersTurn;
		BS_Player*m_player;
		//enemy
		bool enemysTurn;
		bool enemyAttacks;
		//all enemy HUD
		sf::Text m_text_combat;
		//battle stats
		sf::Vector2f mousePosition;
		BS_Skills* m_skillHolder;
		int AmountOfOptionsInMenu1;
		int AmountOfOptionsInMenu2;
		int AmountOfOptionsInSkillScreen;
		//player
		PlayerStatusManager* m_player_status_manager;
		float m_player_health;
		float m_player_damage;
		float m_player_speed;
		float m_player_evadeRate;
		float m_player_hitrate;
		std::string m_player_name;
		//playerSkills
		int m_player_skill_1_Number;
		float m_player_skill_1_DMG;
		float m_player_skill_1_HitRate;
		int m_player_skill_1_AmountOfAttacks;
		std::string m_player_skill_1_Attribute;
		std::string m_player_skill_1_Name;
		float m_player_skill_1_animTime;
		sf::Sound m_player_skill_1_sound;
		//skill 2
		int m_player_skill_2_Number;
		float m_player_skill_2_DMG;
		float m_player_skill_2_HitRate;
		int m_player_skill_2_AmountOfAttacks;
		std::string m_player_skill_2_Attribute;
		std::string m_player_skill_2_Name;
		float m_player_skill_2_animTime;
		sf::Sound m_player_skill_2_sound;
		//skill 3
		int m_player_skill_3_Number;
		float m_player_skill_3_DMG;
		float m_player_skill_3_HitRate;
		int m_player_skill_3_AmountOfAttacks;
		std::string m_player_skill_3_Attribute;
		std::string m_player_skill_3_Name;
		float m_player_skill_3_animTime;
		sf::Sound m_player_skill_3_sound;
		//skill 4 
		int m_player_skill_4_Number;
		float m_player_skill_4_DMG;
		float m_player_skill_4_HitRate;
		int m_player_skill_4_AmountOfAttacks;
		std::string m_player_skill_4_Attribute;
		std::string m_player_skill_4_Name;
		std::vector<BS_Player> m_playerVector;
		std::vector<std::string> m_playerSkills;
		float m_player_skill_4_animTime;
		sf::Sound m_player_skill_4_sound;
		//enemy

		float m_enemy_health;
		float m_enemy_damage;
		float m_enemy_speed;
		float m_enemy_hitrate;
		float m_enemy_evadeRate;
		int m_enemy_loot;
		void EnemyUseSkill_1();
		void EnemyUseSkill_2();
		void EnemyUseSkill_3();
		void EnemyUseSkill_4();
		std::string m_enemy_name;
		std::vector<BS_Enemy> m_enemyVector;
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
		float m_enemy_skill_1_animTime;
		sf::Sound m_enemy_skill_1_sound;
		//skill 2
		int m_enemy_skill_2_Number;
		float m_enemy_skill_2_DMG;
		float m_enemy_skill_2_HitRate;
		int m_enemy_skill_2_AmountOfAttacks;
		std::string m_enemy_skill_2_Attribute;
		std::string m_enemy_skill_2_Name;
		float m_enemy_skill_2_animTime;
		sf::Sound m_enemy_skill_2_sound;
		//skill 3
		int m_enemy_skill_3_Number;
		float m_enemy_skill_3_DMG;
		float m_enemy_skill_3_HitRate;
		int m_enemy_skill_3_AmountOfAttacks;
		std::string m_enemy_skill_3_Attribute;
		std::string m_enemy_skill_3_Name;
		float m_enemy_skill_3_animTime;
		sf::Sound m_enemy_skill_3_sound;
		//skill 4 
		int m_enemy_skill_4_Number;
		float m_enemy_skill_4_DMG;
		float m_enemy_skill_4_HitRate;
		int m_enemy_skill_4_AmountOfAttacks;
		std::string m_enemy_skill_4_Attribute;
		std::string m_enemy_skill_4_Name;
		float m_enemy_skill_4_animTime;
		sf::Sound m_enemy_skill_4_sound;
		enum TurnManager
		{
			TURN_PLAYER,
			TURN_ENEMY,
			TURN_OVER,
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
