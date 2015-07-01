#include "stdafx.h"
#include "SkillEffect.hpp"
#include "AnimatedSprite.hpp"
#include "Animation.hpp"
#include "TextureManager.hpp"
#include "ServiceLocator.hpp"
#include <iostream>
namespace spaceshooter
{
		SkillEffect::SkillEffect(std::string skillName)
		{
			m_skillName = skillName;
			m_visible = true;
			Animation* skillEffectAnimation= new Animation();
			TextureManager* texture_manager = ServiceLocator<TextureManager>::GetService();
			m_skillEffectSheet = texture_manager->CreateTextureFromFile("../assets/Sprites/Animations/SkillEffectSheets/" + skillName + "Sheet.png");
			skillEffectAnimation->setSpriteSheet(*m_skillEffectSheet);
			skillEffectAnimation->addFrame(sf::IntRect(0, 0, 400, 400));
			skillEffectAnimation->addFrame(sf::IntRect(0, 0, 150, 300));

			m_SkillEffectAnimations.insert(std::make_pair(skillName+"_Anim", skillEffectAnimation));
			animSprite = new AnimatedSprite();
			animSprite->setAnimation(*m_SkillEffectAnimations.find(skillName+"_Anim")->second);
			animSprite->setFrameTime(sf::seconds(0.1f));
		}
		SkillEffect::~SkillEffect()
		{

		}
		void SkillEffect::draw(sf::RenderTarget &target, sf::RenderStates states) const
		{
			if (m_visible)
			{
				states.texture = m_skillEffectSheet;
				target.draw(*animSprite, states);
			}
		}
		void SkillEffect::Update(float deltatime)
		{
			animSprite->update(sf::seconds(deltatime));
		}
}; // namespace spaceshooter
