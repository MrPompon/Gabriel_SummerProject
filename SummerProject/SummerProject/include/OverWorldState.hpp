// OverWorldState.hpp

#ifndef OverWorldState_HPP_INCLUDED
#define OverWorldState_HPP_INCLUDED

#include "AbstractState.hpp"

namespace spaceshooter
{
	//roguelike tilebased mousemovement, event nodes etc.
	class OVArea;
	class OVPlayer;
	class DrawManager;
	class InputManager;
	class StateManager;
	class BattleState;
	class PlayerStatusManager;
	class GUIWindow;
	class OverWorldState : public AbstractState
	{
	public:
		virtual bool Enter();
		virtual void Exit();
		virtual bool Update(float deltatime);
		virtual void Draw();
		virtual std::string GetNextState();
		void SetExitState(std::string encounterName, std::string musicName, std::string timeOfDay);
		void InitAudio();
		void ChangeArea(std::string p_fileareaName);
	private:
		
		PlayerStatusManager* m_player_status_manager;
		sf::Music* OV_Music;
		StateManager*m_stateManager;
		std::string m_encounterName;
		DrawManager* m_draw_manager;
		InputManager* m_input_manager;
		OVArea* m_OVArea;
		OVPlayer* m_OVPlayer;
		sf::Mouse m_mouse;
		//mousefunctions
		sf::Vector2f mousePosition;
		void UpdateMouse(float deltatime);
		bool m_exitState;
	};
}
// namespace spaceshooter

#endif // OverWorldState_HPP_INCLUDED