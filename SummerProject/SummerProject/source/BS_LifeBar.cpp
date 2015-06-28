
#include "stdafx.h"
#include "BS_LifeBar.hpp"
#include "BS_Enemy.hpp"
#include "BS_Player.hpp"
#include "BattleState.hpp"
#include <iostream>
namespace spaceshooter
{
	BS_LifeBar::BS_LifeBar(BattleState *p_battleState,BS_Enemy*p_enemy, sf::Vector2f p_position)
	{
		m_battleState = p_battleState;
		playersLifeBar = false;
		enemysLifeBar = true;
		m_enemy = p_enemy;
		m_position = p_position;
		maximumLife = m_enemy->GetHealth();
		currentLife = maximumLife;
		InitLifeBar();
	}
	BS_LifeBar::BS_LifeBar(BattleState *p_battleState,BS_Player*p_player,sf::Vector2f p_position)
	{
		m_battleState = p_battleState;
		playersLifeBar = true;
		enemysLifeBar = false;
		m_player = p_player;
		m_position = p_position;
		maximumLife = m_player->GetHealth();
		currentLife = maximumLife;
		InitLifeBar();
	}
	BS_LifeBar::~BS_LifeBar()
	{

	}
	void BS_LifeBar::InitLifeBar()
	{
		if (!m_lifebarTexture.loadFromFile("../assets/Sprites/BS_LifeBar/BS_LifeBar.png"))
		{
			std::cout << "Failed to load lifebarFile" << std::endl;
		}
		m_lifebar.setTexture(m_lifebarTexture);
		if (!m_tex_lifebarBackground.loadFromFile("../assets/Sprites/BS_LifeBar/BS_LifeBarBackground.png"))
		{
			std::cout << "Failed to load lifebarBackgroundFile" << std::endl;
		}
		m_spr_lifebarBackground.setTexture(m_tex_lifebarBackground);
	}
	void BS_LifeBar::Update(float deltatime)
	{
		if (enemysLifeBar == true)
		{
			currentLife = m_battleState->m_enemy_health;
		}
		else if (playersLifeBar == true)
		{
			currentLife = m_battleState->m_player_health;
		}
		m_lifebar.setPosition(m_position);
		m_lifebar.setScale(1*currentLife/maximumLife,0.2);
		m_spr_lifebarBackground.setPosition(m_position);
		m_spr_lifebarBackground.setScale(1, 0.2);
	}
	void BS_LifeBar::draw(sf::RenderTarget &target, sf::RenderStates states) const
	{
			states.texture = &m_tex_lifebarBackground;
			target.draw(m_spr_lifebarBackground, states);
			states.texture = &m_lifebarTexture;
			target.draw(m_lifebar, states);
			
	}
}