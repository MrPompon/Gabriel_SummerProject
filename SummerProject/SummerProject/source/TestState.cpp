// TestState.cpp

#include "stdafx.h"
#include "ServiceLocator.hpp"
#include "TextureManager.hpp"
#include "InputManager.hpp"
#include "AudioManager.hpp"
#include "DrawManager.hpp"
#include "TestState.hpp"

namespace spaceshooter
{
	TestState::TestState()
	{
		m_screen_width = 1024.0f;
		m_screen_height = 600.0f;

		for (unsigned int index = 0; index < ACTION_COUNT; index++)
		{
			m_actions[index] = false;
		}

		m_bullet_count = 0;
		m_bullet_speed = 400.0f;
		m_bullet_texture = nullptr;
	}

	TestState::~TestState()
	{
	}

	bool TestState::Enter()
	{
		// note(tommi): register to listen for all input actions
		InputManager* input_manager = ServiceLocator<InputManager>::GetService();
		input_manager->RegisterKeyActionListener(Action::LEFT, this, &TestState::OnAction);
		input_manager->RegisterKeyActionListener(Action::RIGHT, this, &TestState::OnAction);
		input_manager->RegisterKeyActionListener(Action::UP, this, &TestState::OnAction);
		input_manager->RegisterKeyActionListener(Action::DOWN, this, &TestState::OnAction);
		input_manager->RegisterKeyActionListener(Action::FIRE, this, &TestState::OnAction);
		input_manager->RegisterKeyActionListener(Action::ALTFIRE, this, &TestState::OnAction);
		input_manager->RegisterKeyActionListener(Action::SELECT1, this, &TestState::OnAction);
		input_manager->RegisterKeyActionListener(Action::SELECT2, this, &TestState::OnAction);
		input_manager->RegisterKeyActionListener(Action::SELECT3, this, &TestState::OnAction);
		input_manager->RegisterKeyActionListener(Action::SELECT4, this, &TestState::OnAction);

		// note(tommi): test sprite for player
		m_player_position = { 300.0f, m_screen_height * 0.5f };
		m_player_velocity = { 0.0f, 0.0f };

		TextureManager* texture_manager = ServiceLocator<TextureManager>::GetService();
		m_player_texture = texture_manager->CreateTextureFromFile("../assets/player.png");
		m_player_texture->setSmooth(false);
		m_player_sprite.setTexture(*m_player_texture);
		m_player_sprite.setPosition(m_player_position);
		m_player_sprite.setOrigin(
			static_cast<float>(m_player_sprite.getTextureRect().width) * 0.5f,
			static_cast<float>(m_player_sprite.getTextureRect().height) * 0.5f);

	
		AudioManager* audio_manager = ServiceLocator<AudioManager>::GetService();
		sf::SoundBuffer* sound_buffer = audio_manager->CreateSoundFromFile("../assets/audio/gunfire.ogg");
		m_sound.setBuffer(*sound_buffer);
		m_sound.setLoop(false);
		m_sound.setVolume(60.0f);


		// note(tommi): better to have a local pointer than to access it through the service locator
		m_draw_manager = ServiceLocator<DrawManager>::GetService();

		return true;
	}

	void TestState::Exit()
	{
		TextureManager* texture_manager = ServiceLocator<TextureManager>::GetService();
		

		// note(tommi): we should destroy audio stuff here
		// todo(tommi): add destroy music and soundbuffer methods to the audio manager
		AudioManager* audio_manager = ServiceLocator<AudioManager>::GetService();
		// ...

		// note(tommi): unregister all actions listeners
		InputManager* input_manager = ServiceLocator<InputManager>::GetService();
		input_manager->UnregisterKeyActionListener(Action::LEFT, this);
		input_manager->UnregisterKeyActionListener(Action::RIGHT, this);
		input_manager->UnregisterKeyActionListener(Action::UP, this);
		input_manager->UnregisterKeyActionListener(Action::DOWN, this);
		input_manager->UnregisterKeyActionListener(Action::FIRE, this);
		input_manager->UnregisterKeyActionListener(Action::ALTFIRE, this);
		input_manager->UnregisterKeyActionListener(Action::SELECT1, this);
		input_manager->UnregisterKeyActionListener(Action::SELECT2, this);
		input_manager->UnregisterKeyActionListener(Action::SELECT3, this);
		input_manager->UnregisterKeyActionListener(Action::SELECT4, this);
	}

	bool TestState::Update(float deltatime)
	{
		UpdatePlayer(deltatime);
		return true;
	}

	void TestState::Draw()
	{

		m_draw_manager->Draw(m_player_sprite, sf::RenderStates::Default);
	}

	std::string TestState::GetNextState()
	{
		return std::string("");
	}

	// private
	void TestState::OnAction(const std::string& action, bool state)
	{
		// note(tommi): map actions to an internal structure 
		if (action.compare(Action::LEFT) == 0)
		{
			m_actions[ACTION_LEFT] = state;
		}
		else if (action.compare(Action::RIGHT) == 0)
		{
			m_actions[ACTION_RIGHT] = state;
		}
		else if (action.compare(Action::UP) == 0)
		{
			m_actions[ACTION_UP] = state;
		}
		else if (action.compare(Action::DOWN) == 0)
		{
			m_actions[ACTION_DOWN] = state;
		}
		else if (action.compare(Action::FIRE) == 0)
		{
			m_actions[ACTION_FIRE] = state;
		}
		else if (action.compare(Action::ALTFIRE) == 0)
		{
			m_actions[ACTION_ALT_FIRE] = state;
		}
		else if (action.compare(Action::SELECT1) == 0)
		{
			m_actions[ACTION_SELECT1] = state;
		}
		else if (action.compare(Action::SELECT2) == 0)
		{
			m_actions[ACTION_SELECT2] = state;
		}
		else if (action.compare(Action::SELECT3) == 0)
		{
			m_actions[ACTION_SELECT3] = state;
		}
		else if (action.compare(Action::SELECT4) == 0)
		{
			m_actions[ACTION_SELECT4] = state;
		}
	}


	void TestState::UpdatePlayer(float deltatime)
	{
		// note(tommi): these will not be hardcoded
		const float playerHalfWidth = m_player_texture->getSize().x * 0.5f;
		const float playerHalfHeight = m_player_texture->getSize().y * 0.5f;
		const float screenWidth = m_screen_width - playerHalfWidth;
		const float screenHeight = m_screen_height - playerHalfHeight;
		const float playerSpeed = 400.0f;

		bool playerMove = false;
		sf::Vector2f playerAcceleration = { 0.0f, 0.0f };

		if (m_actions[ACTION_UP])
		{
			playerMove = true;
			if (m_player_position.y > playerHalfHeight)
			{
				playerAcceleration.y = -1.0f;
			}
		}
		if (m_actions[ACTION_DOWN])
		{
			playerMove = true;
			if (m_player_position.y < screenHeight)
			{
				playerAcceleration.y = 1.0f;
			}
		}
		if (m_actions[ACTION_LEFT])
		{
			playerMove = true;
			if (m_player_position.x > playerHalfWidth)
			{
				playerAcceleration.x = -1.0f;
			}
		}
		if (m_actions[ACTION_RIGHT])
		{
			playerMove = true;
			if (m_player_position.x < screenWidth)
			{
				playerAcceleration.x = 1.0f;
			}
		}
		m_player_sprite.setPosition(m_player_position);
	}

} // namespace spaceshooter
