// TestState.hpp

#ifndef TESTSTATE_HPP_INCLUDED
#define TESTSTATE_HPP_INCLUDED

#include "AbstractState.hpp"

namespace spaceshooter
{
	class DrawManager;

	// note(tommi): to clarify, this whole class is just for testing
	// we will refactor and break out code into classes eventually
	// when we know how to do the things we need to do
	class TestState : public AbstractState
	{
	public:
		TestState();
		~TestState();

		virtual bool Enter();
		virtual void Exit();
		virtual bool Update(float deltatime);
		virtual void Draw();
		virtual std::string GetNextState();

	private:
		void OnAction(const std::string& action, bool state);
		void UpdateBackground(float deltatime);
		void UpdateEnemy(float deltatime);
		void UpdatePlayer(float deltatime);
		void UpdatePlayerBullets(float deltatime);
		void SpawnPlayerBullet(const sf::Vector2f& position);
		void DespawnPlayerBullet(unsigned int index);

	private:
		DrawManager* m_draw_manager;

		float m_screen_width;
		float m_screen_height;

		// note(tommi): player
		sf::Texture* m_player_texture;
		sf::Sprite m_player_sprite;
		sf::Vector2f m_player_position;
		sf::Vector2f m_player_velocity;
		sf::Vector2f m_player_direction;

		// note(tommi): player bullets goes here
		enum { MAX_PLAYER_BULLETS = 16 };
		float m_bullet_speed;
		unsigned int m_bullet_count;
		sf::Vector2f m_bullet_positions[MAX_PLAYER_BULLETS];
		sf::Texture* m_bullet_texture;
		sf::Sprite m_bullet_sprite;
		sf::Sound m_sound;

		// note(tommi): layer in the bottom and closer to the viewer
		sf::Texture* m_background01_texture;
		sf::Sprite m_background01_sprite;

		sf::Texture* m_background02_texture;
		sf::VertexArray m_background02_vertex_array;

		sf::Texture* m_background03_texture;
		sf::VertexArray m_background03_vertex_array;

		sf::Texture* m_background04_texture;
		sf::VertexArray m_background04_vertex_array;

		// note(tommi): here be enemy pattern testing
		sf::Texture* m_enemy_texture;
		sf::Sprite m_enemy_sprite;
		float m_enemy_total_time;

		// note(tommi): code for actions will be refactored
		// into a player controller class
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

#endif // TESTSTATE_HPP_INCLUDED
