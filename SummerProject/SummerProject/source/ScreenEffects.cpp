#include "stdafx.h"
#include "ScreenEffects.hpp"
#include "AnimatedSprite.hpp"
#include "Animation.hpp"
#include "TextureManager.hpp"
#include "ServiceLocator.hpp"
#include <iostream>
namespace spaceshooter
{
	ScreenEffects::ScreenEffects()
	{
		
	}
	ScreenEffects::~ScreenEffects()
	{

	}

	void ScreenEffects::draw(sf::RenderTarget &target, sf::RenderStates states) const
	{
		/*if (m_visible)
		{
			states.texture = m_ScreenEffectsSheet;
			target.draw(*animSprite, states);
		}*/
	}
	void ScreenEffects::Update(float deltatime)
	{
	
	}
}; // namespace spaceshooter
