#include "stdafx.h"
#include "ScreenEffects.hpp"
#include "AnimatedSprite.hpp"
#include "Animation.hpp"
#include "TextureManager.hpp"
#include "ServiceLocator.hpp"
#include "DrawManager.hpp"
#include <iostream>


namespace spaceshooter
{
	ScreenEffects::ScreenEffects(sf::RenderWindow*p_renderWindow, std::string p_effectName, float p_effectDuration, DrawManager*p_drawManager)
	{
		m_drawmanager = ServiceLocator<DrawManager>::GetService();
		m_renderWindow = m_drawmanager->getWindow();
		m_name = p_effectName;
		m_lifeTime = p_effectDuration;
		m_screen_width = 1024.0f;
		m_screen_height = 600.0f;
		
		
		m_screenEffectRect.setSize(sf::Vector2f(m_screen_width, m_screen_height));
		m_visible = true;
		if (m_name == "SetShake")
		{
			screenEffect = EFFECT_SHAKING;
		}
		else if (m_name == "SetNight")
		{
			screenEffect = EFFECT_NIGHT;
			m_screenEffectRect.setFillColor(sf::Color(25, 0, 51, 120));
		}
		else if (m_name == "SetDay")
		{
			screenEffect = EFFECT_DAY;
			m_screenEffectRect.setFillColor(sf::Color(0, 0, 0, 0));
		}
		else if (m_name == "SetDusk")
		{
			screenEffect = EFFECT_DUSK;
			m_screenEffectRect.setFillColor(sf::Color(153, 0, 76, 40));
		}
		else if (m_name == "SetDawn")
		{
			screenEffect = EFFECT_DAWN;
			m_screenEffectRect.setFillColor(sf::Color(204, 102, 0, 40));
		}
		else if (m_name == "SetBlaze")
		{
			screenEffect = EFFECT_BLAZE;
			m_screenEffectRect.setFillColor(sf::Color(255, 51, 51, 120));
			
		}
		else
		{
			std::cout << "INVALID SCREENEFFECTNAME";
		}
		
	}
	ScreenEffects::~ScreenEffects()
	{

	}

	void ScreenEffects::draw(sf::RenderTarget &target, sf::RenderStates states) const
	{
		if (m_visible)
		{
			states.texture = m_screenEffectRect.getTexture();
			target.draw(m_screenEffectRect, states);
		}
	}
	void ScreenEffects::Update(float deltatime)
	{
		m_lifeTime -= deltatime;
	
		if (m_lifeTime <= 0)
		{
			m_visible = false;
		}
		if (screenEffect == EFFECT_SHAKING)
		{
			if (m_lifeTime > 0)
			{
				ScreenShake(10);
			}
			else
			{
				m_view.setCenter(m_screen_width/2, m_screen_height/2);
			}
		}
		else if (screenEffect == EFFECT_DAY)
		{
		
		}
		else if (screenEffect == EFFECT_NIGHT)
		{
			
		}
		else if (screenEffect == EFFECT_BLAZE)
		{
		
		}
		m_view.setCenter(m_screen_width / 2, m_screen_height / 2);

		//m_screenEffectRect.setPosition(sf::Vector2f(m_drawmanager->getWindow()->getPosition()));
	}
	sf::RectangleShape ScreenEffects::GetRectangleShape()
	{
		return m_screenEffectRect;
	}
	void ScreenEffects::SetDay()
	{

	}
	void ScreenEffects::SetNight()
	{

	}

	void ScreenEffects::SetBlaze(float duration)
	{

	}
	void ScreenEffects::ScreenShake(float screenShakeAmount)
	{
		float randomPosX;
		float randomPosY;
		randomPosX = Random((m_screen_width / 2) - screenShakeAmount, (m_screen_width / 2) + screenShakeAmount);
		randomPosY = Random((m_screen_height / 2) - screenShakeAmount, (m_screen_height / 2) + screenShakeAmount);
		m_view.setCenter(randomPosX, randomPosY);
		m_view.setSize(m_screen_width,m_screen_height);
		m_renderWindow->setView(m_view);
	}
}; // namespace spaceshooter
