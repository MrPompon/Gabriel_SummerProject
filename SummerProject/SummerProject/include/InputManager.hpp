// InputManager.hpp

#ifndef INPUTMANAGER_HPP_INCLUDED
#define INPUTMANAGER_HPP_INCLUDED

namespace spaceshooter
{
	class InputManager
	{
		// note(tommi): a private class for the input manager
		// used to bind methods for callbacks
		// this is called a functor, for this to function 
		// we need an object and a method pointer
		class AbstractCallback
		{
		public:
			virtual void OnAction(const std::string& action, bool) = 0;
			virtual bool IsObject(void*) = 0;
		};

		template <class T>
		class Callback : public AbstractCallback
		{
			T* m_object;
			void(T::*m_method)(const std::string&, bool);
		public:
			Callback(T* object, void(T::*method)(const std::string&, bool))
				: m_object(object)
				, m_method(method)
			{
			}

			void OnAction(const std::string& action, bool state)
			{
				// note(tommi): call the method on the specific method
				(*m_object.*m_method)(action, state);
			}

			bool IsObject(void* pointer)
			{
				return m_object == pointer;
			}
		};

		typedef std::vector<AbstractCallback*> CallbackArray;

		// note(tommi): making the copy constructor and 
		// assignment operator private we make the class
		// non-copyable 
		InputManager(const InputManager&);
		InputManager& operator=(const InputManager&);

		friend class Engine;

	public:
		InputManager();
		~InputManager();

		bool Initialize();
		void Shutdown();

		void MapKeyToAction(sf::Keyboard::Key key, const std::string& action);
		void UnregisterKeyActionListener(const std::string& action, void* object);

		template <class T> 
		void RegisterKeyActionListener(const std::string& action, T* object, void(T::*method)(const std::string&, bool))
		{
			m_actioncallbacks[action].push_back(new Callback<T>(object, method));
		}

	private:
		void OnKeyboard(sf::Keyboard::Key key, bool state);

	private:
		std::map<sf::Keyboard::Key, std::string> m_keymapping;
		std::map<std::string, CallbackArray> m_actioncallbacks;
	};
} // namespace spaceshooter

#endif // INPUTMANAGER_HPP_INCLUDED
