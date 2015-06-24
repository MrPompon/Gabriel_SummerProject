// StateManager.hpp

#ifndef STATEMANAGER_HPP_INCLUDED
#define STATEMANAGER_HPP_INCLUDED

namespace spaceshooter
{
	class AbstractState;

	class StateManager
	{
		// note(tommi): making the copy constructor and 
		// assignment operator private we make the class
		// non-copyable
		StateManager(const StateManager&);
		StateManager& operator=(const StateManager&);

	public:
		StateManager();
		~StateManager();

		bool Initialize();
		void Shutdown();
		bool Update(float deltatime);
		void Draw();

		void AttachState(const std::string& name, AbstractState* state);
		void DetachState(const std::string& name);
		bool SetActiveState(const std::string& name);

	private:
		AbstractState* m_active_state;
		std::map<std::string, AbstractState*> m_states;
	};
} // namespace spaceshooter

#endif // STATEMANAGER_HPP_INCLUDED
