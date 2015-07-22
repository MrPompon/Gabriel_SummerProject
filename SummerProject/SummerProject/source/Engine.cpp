// Engine.cpp

#include "stdafx.h"
#include "DrawManager.hpp"
#include "InputManager.hpp"
#include "TextureManager.hpp"
#include "CollisionManager.hpp"
#include "AudioManager.hpp"
#include "StateManager.hpp"
#include "ServiceLocator.hpp"
#include "Engine.hpp"

namespace spaceshooter
{
	Engine::Engine()
	{
		m_running = false;
		m_draw_manager = nullptr;
		m_input_manager = nullptr;
		m_texture_manager = nullptr;
		m_collision_manager = nullptr;
		m_audio_manager = nullptr;
		m_state_manager = nullptr;
	}

	Engine::~Engine()
	{
	}

	bool Engine::Initialize()
	{
		m_window.create(sf::VideoMode(1024, 600), "Architecture");
		if (!m_window.isOpen())
			return false;
		// note(tommi): disable key repeat spam
		// we only want to know when a key was pressed or released
		m_window.setKeyRepeatEnabled(false);

		// note(tommi): wait for vertical sync 60 Hz
		// read more at en.wikipedia.org/wiki/Analog_television#Vertical_synchronization
		m_window.setVerticalSyncEnabled(true);

		m_draw_manager = new DrawManager(&m_window);
		if (!m_draw_manager || !m_draw_manager->Initialize())
			return false;
		ServiceLocator<DrawManager>::SetService(m_draw_manager);

		m_input_manager = new InputManager;
		if (!m_input_manager || !m_input_manager->Initialize())
			return false;
		ServiceLocator<InputManager>::SetService(m_input_manager);

		m_texture_manager = new TextureManager;
		if (!m_texture_manager || !m_texture_manager->Initialize())
			return false;
		ServiceLocator<TextureManager>::SetService(m_texture_manager);

		m_collision_manager = new CollisionManager;
		if (!m_collision_manager || !m_collision_manager->Initialize())
			return false;
		ServiceLocator<CollisionManager>::SetService(m_collision_manager);

		m_audio_manager = new AudioManager;
		if (!m_audio_manager || !m_audio_manager->Initialize())
			return false;
		ServiceLocator<AudioManager>::SetService(m_audio_manager);

		m_state_manager = new StateManager;
		if (!m_state_manager || !m_state_manager->Initialize())
			return false;
		ServiceLocator<StateManager>::SetService(m_state_manager);
		return m_running = true;
	}

	void Engine::Shutdown()
	{
		// note(tommi): here we delete the managers in the reverse order 
		// because of potential dependencies 
		if (m_state_manager)
		{
			m_state_manager->Shutdown();
			delete m_state_manager;
			m_state_manager = nullptr;
		}

		if (m_audio_manager)
		{
			m_audio_manager->Shutdown();
			delete m_audio_manager;
			m_audio_manager = nullptr;
		}

		if (m_collision_manager)
		{
			m_collision_manager->Shutdown();
			delete m_collision_manager;
			m_collision_manager = nullptr;
		}

		if (m_texture_manager)
		{
			m_texture_manager->Shutdown();
			delete m_texture_manager;
			m_texture_manager = nullptr;
		}

		if (m_input_manager)
		{
			m_input_manager->Shutdown();
			delete m_input_manager;
			m_input_manager = nullptr;
		}

		if (m_draw_manager)
		{
			m_draw_manager->Shutdown();
			delete m_draw_manager;
			m_draw_manager = nullptr;
		}
	}

	void Engine::Run()
	{
		sf::Clock clock;
		sf::Time current = clock.getElapsedTime();
		while (m_running)
		{
			HandleOSEvents();

			sf::Time now = clock.getElapsedTime();
			sf::Time deltatime = now - current;
			current = now;

			float dt = deltatime.asSeconds();
			if (dt > 0.1f)
				dt = 0.1f;

			m_state_manager->Update(dt);
			m_window.clear();
			m_state_manager->Draw();
			m_window.display();

			//sf::sleep(sf::milliseconds(10));
		}
		m_window.close();
	}

	// private
	void Engine::HandleOSEvents()
	{
		sf::Event event;
		while (m_window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
			{
				m_running = false;
			}
			else if (event.type == sf::Event::KeyPressed)
			{
				m_input_manager->OnKeyboard(event.key.code, true);
			}
			else if (event.type == sf::Event::KeyReleased)
			{
				m_input_manager->OnKeyboard(event.key.code, false);
			}
		}
	}
} // namespace spaceshooter
