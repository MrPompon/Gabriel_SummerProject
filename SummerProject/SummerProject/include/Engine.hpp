// Engine.hpp

#ifndef ENGINE_HPP_INCLUDED
#define ENGINE_HPP_INCLUDED

namespace spaceshooter
{
	/* forward declares */
	class DrawManager;
	class InputManager;
	class StateManager;
	class TextureManager;
	class CollisionManager;
	class AudioManager;
	class PlayerStatusManager;

	class Engine
	{
	public:
		Engine();
		~Engine();

		bool Initialize();
		void Shutdown();
		void Run();

	private:
		void HandleOSEvents();

	private:
		bool m_running;
		sf::RenderWindow m_window;

		DrawManager* m_draw_manager;
		InputManager* m_input_manager;
		TextureManager* m_texture_manager;
		CollisionManager* m_collision_manager;
		AudioManager* m_audio_manager;
		StateManager* m_state_manager;
		PlayerStatusManager* m_player_status_manager;
	};
} // namespace spaceshooter

#endif // ENGINE_HPP_INCLUDED
