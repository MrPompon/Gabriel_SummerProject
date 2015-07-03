#include "stdafx.h"
#include "ScreenEffects.hpp"
#include "AnimatedSprite.hpp"
#include "Animation.hpp"
#include "TextureManager.hpp"
#include "ServiceLocator.hpp"
#include <iostream>


namespace spaceshooter
{
	ScreenEffects::ScreenEffects(sf::RenderWindow*p_renderWindow,std::string p_effectName ,float p_effectDuration)
	{
		m_name = p_effectName;
		m_lifeTime = p_effectDuration;
		m_screen_width = 1024.0f;
		m_screen_height = 600.0f;
		m_renderWindow = p_renderWindow;
	
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
	void ScreenEffects::ScreenShake(float screenShakeAmount, float duration)
	{

	}
}; // namespace spaceshooter
