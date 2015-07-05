#include "stdafx.h"
#include "SkillEffect.hpp"
#include "AnimatedSprite.hpp"
#include "Animation.hpp"
#include "TextureManager.hpp"
#include "ServiceLocator.hpp"
#include "ScreenEffects.hpp"
#include "DrawManager.hpp"
#include <iostream>
namespace spaceshooter
{
	SkillEffect::SkillEffect(std::string skillName, float p_lifeTime, sf::Vector2f p_pos, DrawManager*p_drawManager)
		{
			m_skillName = skillName;
			m_lifeTime = p_lifeTime;
			m_drawManager = p_drawManager;
			InitAnimation(skillName);
			m_view = m_drawManager->getWindow();
			m_screenWidth = 1024;
			m_screenHeight = 600;
			Animation* skillEffectAnimation= new Animation();
			TextureManager* texture_manager = ServiceLocator<TextureManager>::GetService();
			m_skillEffectSheet = texture_manager->CreateTextureFromFile("../assets/Sprites/Animations/SkillEffectSheets/" + skillName + "Sheet.png");
			skillEffectAnimation->setSpriteSheet(*m_skillEffectSheet);
			for (unsigned int r = 0; r < m_rows; r++)
			{
				for (unsigned int c = 0; c < m_colums; c++)
				{
					skillEffectAnimation->addFrame(sf::IntRect(m_offsetX + (r*m_imageWidth), m_offsetY+(c*m_imageHeight), m_imageWidth, m_imageHeight));
				}
			}
			
			//skillEffectAnimation->addFrame(sf::IntRect(0, 0, 150, 300));

			m_SkillEffectAnimations.insert(std::make_pair(skillName+"_Anim", skillEffectAnimation));
			animSprite = new AnimatedSprite();
			animSprite->setAnimation(*m_SkillEffectAnimations.find(skillName+"_Anim")->second);
			animSprite->setFrameTime(sf::seconds(0.1f));
			animSprite->setPosition(p_pos.x, p_pos.y);
			animSprite->setOrigin(animSprite->getGlobalBounds().width*0.5, animSprite->getGlobalBounds().height*0.5);
			animSprite->setScale(2.5,2.5 );
			
		}
		SkillEffect::~SkillEffect()
		{

		}
		void SkillEffect::InitAnimation(std::string p_skillName)
		{
			
			m_visible = true;
			if (p_skillName == "Blaze")
			{
				m_colums = 4;
				m_rows = 4;

				m_imageHeight = 200;
				m_imageWidth = 200;

				m_offsetX = 0;
				m_offsetY = 0;

				ScreenEffects *m_screenEffect = new ScreenEffects(m_view, "SetBlaze", m_lifeTime, m_drawManager);
				AllScreenEffects.push_back(*m_screenEffect);
			}
			else if (p_skillName == "Crunch")
			{
				m_colums = 7;
				m_rows = 2;

				m_imageHeight = 210;
				m_imageWidth = 110;

				m_offsetX = 0;
				m_offsetY = 0;
			}
			else if (p_skillName == "Cleave")
			{
				m_rows = 1;
				m_colums = 8;

				m_imageHeight = 72;
				m_imageWidth = 48;

				m_offsetX = 0;
				m_offsetY = 100;
			}
			else if (p_skillName == "Razor")
			{
				m_rows = 4;
				m_colums = 2; 

				m_imageWidth = 134;
				m_imageHeight = 90;

				m_offsetX = 0;
				m_offsetY = 0;
			}
			else if (p_skillName == "HeadButt")
			{
				m_rows = 1;
				m_colums = 2;

				m_imageWidth = 300;
				m_imageHeight = 120;

				m_offsetX = 0;
				m_offsetY = 42;

				ScreenEffects *m_screenEffect = new ScreenEffects(m_view, "SetShake", m_lifeTime, m_drawManager);
				AllScreenEffects.push_back(*m_screenEffect);
			}
			else if (p_skillName == "Carnage")
			{
				m_rows = 1;
				m_colums = 19;

				m_imageWidth = 113;
				m_imageHeight = 52;

				m_offsetX = 0;
				m_offsetY = 52;
			}
			else if (p_skillName == "Smash")
			{
				m_rows = 1;
				m_colums = 2;

				m_imageWidth = 300;
				m_imageHeight = 120;

				m_offsetX = 0;
				m_offsetY = 42;

				ScreenEffects *m_screenEffect = new ScreenEffects(m_view, "SetShake", m_lifeTime, m_drawManager);
				AllScreenEffects.push_back(*m_screenEffect);
			}
			else if (p_skillName == "ShadowBall")
			{
				m_rows = 11;
				m_colums = 2;

				m_imageWidth = 255;
				m_imageHeight = 140;

				m_offsetX = 0;
				m_offsetY = 0;
			}
		}
		void SkillEffect::draw(sf::RenderTarget &target, sf::RenderStates states) const
		{
			if (m_visible)
			{
				states.texture = m_skillEffectSheet;
				target.draw(*animSprite, states);
			/*	if (m_lifeTime > 0)
				{
					for (unsigned int i = 0; i < AllScreenEffects.size(); i++)
					{

						states.texture = m_skillEffectSheet);
						target.draw(AllScreenEffects[i], states);
					}
				}*/
			}
		}
		void SkillEffect::Update(float deltatime)
		{
			animSprite->update(sf::seconds(deltatime));
			m_lifeTime -= deltatime;
			if (m_lifeTime <= 0)
			{
				m_visible = false;
			}
			for (unsigned int i = 0; i < AllScreenEffects.size(); i++)
			{
				AllScreenEffects[i].Update(deltatime);
			}
		}
}; // namespace spaceshooter
