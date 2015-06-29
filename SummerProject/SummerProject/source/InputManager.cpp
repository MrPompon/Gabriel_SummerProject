// InputManager.cpp

#include "stdafx.h"
#include "InputManager.hpp"

namespace spaceshooter
{
	InputManager::InputManager()
	{
	}

	InputManager::~InputManager()
	{
	}

	bool InputManager::Initialize()
	{
		// note(tommi): here we set default keys to actions
		MapKeyToAction(sf::Keyboard::A, Action::LEFT);
		MapKeyToAction(sf::Keyboard::D, Action::RIGHT);
		MapKeyToAction(sf::Keyboard::W, Action::UP);
		MapKeyToAction(sf::Keyboard::S, Action::DOWN);
		MapKeyToAction(sf::Keyboard::Space, Action::FIRE);
		MapKeyToAction(sf::Keyboard::E, Action::ALTFIRE);
		MapKeyToAction(sf::Keyboard::Num1, Action::SELECT1);
		MapKeyToAction(sf::Keyboard::Num2, Action::SELECT2);
		MapKeyToAction(sf::Keyboard::Num3, Action::SELECT3);
		MapKeyToAction(sf::Keyboard::Escape, Action::SELECT4);
		

		return true;
	}
	sf::Mouse InputManager::GetMouse()
	{
		return mouse;
	}
	void InputManager::Shutdown()
	{
		m_keymapping.clear();

		auto callbackIterator = m_actioncallbacks.begin();
		while (callbackIterator != m_actioncallbacks.end())
		{
			std::vector<AbstractCallback*>& callbacks = callbackIterator->second;
			auto itr = callbacks.begin();
			while (itr != callbacks.end())
			{
				delete (*itr);
				++itr;
			}
			callbacks.clear();
			++callbackIterator;
		}
		m_actioncallbacks.clear();
	}

	void InputManager::MapKeyToAction(sf::Keyboard::Key key, const std::string& action)
	{
		m_keymapping[key] = action;
	}

	void InputManager::UnregisterKeyActionListener(const std::string& action, void* object)
	{
		auto itr = m_actioncallbacks.find(action);
		while (itr != m_actioncallbacks.end())
		{
			auto itri = itr->second.begin();
			while (itri != itr->second.end())
			{
				if ((*itri)->IsObject(object))
				{
					delete (*itri);
					itr->second.erase(itri);
					break;
				}
			}
			++itr;
		}
	}

	// private
	void InputManager::OnKeyboard(sf::Keyboard::Key key, bool state)
	{
		auto keymapIterator = m_keymapping.find(key);
		if (keymapIterator == m_keymapping.end())
			return;

		const std::string& action = keymapIterator->second;
		auto callbackIterator = m_actioncallbacks.find(action);
		if (callbackIterator == m_actioncallbacks.end())
			return;

		const std::vector<AbstractCallback*>& callbacks = callbackIterator->second;
		auto itr = callbacks.begin();
		while (itr != callbacks.end())
		{
			(*itr)->OnAction(action, state);
			++itr;
		}
	}
} // namespace spaceshooter
