#include "stdafx.h"
#include <iostream>
#include "ServiceLocator.hpp"
#include "TextureManager.hpp"
#include "InputManager.hpp"
#include "AudioManager.hpp"
#include "DrawManager.hpp"
#include "OVPlayer.hpp"
#include "Animation.hpp"
#include "AnimatedSprite.hpp"
namespace spaceshooter
{
	OVPlayer::OVPlayer()
	{
		m_drawManager = ServiceLocator<DrawManager>::GetService();
		m_textureManager = ServiceLocator<TextureManager>::GetService();
		m_playerSheet = m_textureManager->CreateTextureFromFile("../assets/Sprites/Animations/PlayerSheets/PlayerSheetClown.png");
		m_playerSprite = new AnimatedSprite();
		m_currentPos = sf::Vector2f(16, 16);
		m_targetPos = m_currentPos;
		m_screenWidth = 1024;
		m_screenHeight = 600;
		PlayerRightAnimation = new Animation();
		PlayerLeftAnimation = new Animation();
		PlayerUpAnimation = new Animation();
		PlayerDownAnimation = new Animation();
		PlayerDownAnimation->setSpriteSheet(*m_playerSheet);
		PlayerUpAnimation->setSpriteSheet(*m_playerSheet);
		PlayerLeftAnimation->setSpriteSheet(*m_playerSheet);
		PlayerRightAnimation->setSpriteSheet(*m_playerSheet);
		InitAnimation("Up");
		AddAnimationFrame("Up");
		InitAnimation("Down");
		AddAnimationFrame("Down");
		InitAnimation("Left");
		AddAnimationFrame("Left");
		InitAnimation("Right");
		AddAnimationFrame("Right");
		
		m_playerSprite->setAnimation(*m_playerAnimations.find("PlayerDown")->second);
		m_playerSprite->setFrameTime(sf::seconds(0.1f));
		m_playerSprite->setPosition(m_currentPos.x, m_currentPos.y);
		m_playerSprite->setOrigin(m_playerSprite->getGlobalBounds().width*0.5, m_playerSprite->getGlobalBounds().height*0.5);
		m_playerSprite->setScale(1, 1);
	}
	OVPlayer::~OVPlayer()
	{

	}
	sf::Vector2f OVPlayer::GetPosition()
	{
		return m_currentPos;
	}
	void OVPlayer::MoveTowards()
	{
		if (m_currentPos.x < m_targetPos.x)
		{
			if (movementDirection != DIRECTION_RIGHT)
			{
				m_playerSprite->setAnimation(*m_playerAnimations.find("PlayerRight")->second);
			}
			m_currentPos.x++;
			movementDirection = DIRECTION_RIGHT;
		}
		else if (m_currentPos.x > m_targetPos.x)
		{
			if (movementDirection != DIRECTION_LEFT)
			{
				m_playerSprite->setAnimation(*m_playerAnimations.find("PlayerLeft")->second);
			}
			m_currentPos.x--;
			movementDirection = DIRECTION_LEFT;
		}
		else if (m_currentPos.y < m_targetPos.y)
		{
			if (movementDirection != DIRECTION_DOWN)
			{
				m_playerSprite->setAnimation(*m_playerAnimations.find("PlayerDown")->second);	
			}
			m_currentPos.y++;
			movementDirection = DIRECTION_DOWN;
		}
		else if (m_currentPos.y > m_targetPos.y)
		{
			if (movementDirection != DIRECTION_UP)
			{
				m_playerSprite->setAnimation(*m_playerAnimations.find("PlayerUp")->second);
			}
			m_currentPos.y--;
			movementDirection = DIRECTION_UP;
		}
	
		m_playerSprite->setPosition(m_currentPos);
	}
	void OVPlayer::InitAnimation(std::string p_animationName)
	{
		if (p_animationName == "Down")
		{
			m_rows = 1;
			m_colums = 3;

			m_offsetX = 0;
			m_offsetY = 0;

			m_imageWidth = 32;
			m_imageHeight = 32;
		}
		else if (p_animationName == "Left")
		{
			m_rows = 1;
			m_colums = 3;

			m_offsetX = 0;
			m_offsetY = 32;

			m_imageWidth = 32;
			m_imageHeight = 32;
		}
		else if (p_animationName == "Right")
		{
			m_rows = 1;
			m_colums = 3;

			m_offsetX = 0;
			m_offsetY = 64;

			m_imageWidth = 32;
			m_imageHeight = 32;
		}
		else if (p_animationName == "Up")
		{
			m_rows = 1;
			m_colums = 3;

			m_offsetX = 0;
			m_offsetY =0;

			m_imageWidth = 32;
			m_imageHeight = 32;
		}
	}
	void OVPlayer::AddAnimationFrame(std::string p_animationName)
	{
	
		if (p_animationName == "Down")
		{
			PlayerDownAnimation->addFrame(sf::IntRect(0, 0, m_imageWidth,m_imageHeight));
			PlayerDownAnimation->addFrame(sf::IntRect(32, 0, m_imageWidth, m_imageHeight));
			PlayerDownAnimation->addFrame(sf::IntRect(64, 0, m_imageWidth, m_imageHeight));
		}
		else if (p_animationName == "Right")
		{
			PlayerRightAnimation->addFrame(sf::IntRect(0, 64,m_imageWidth,m_imageHeight));
			PlayerRightAnimation->addFrame(sf::IntRect(32, 64, m_imageWidth, m_imageHeight));
			PlayerRightAnimation->addFrame(sf::IntRect(64, 64, m_imageWidth, m_imageHeight));
		}
		else if (p_animationName == "Left")
		{
			PlayerLeftAnimation->addFrame(sf::IntRect(0, 32, m_imageWidth,m_imageHeight));
			PlayerLeftAnimation->addFrame(sf::IntRect(32, 32, m_imageWidth, m_imageHeight));
			PlayerLeftAnimation->addFrame(sf::IntRect(64, 32, m_imageWidth, m_imageHeight));
		}
		else if (p_animationName == "Up")
		{
			PlayerUpAnimation->addFrame(sf::IntRect(0, 96,m_imageWidth,m_imageHeight));
			PlayerUpAnimation->addFrame(sf::IntRect(32, 96, m_imageWidth, m_imageHeight));
			PlayerUpAnimation->addFrame(sf::IntRect(32, 96, m_imageWidth, m_imageHeight));
		}
		
		if (p_animationName == "Down")
		{
			m_playerAnimations.insert(std::make_pair("Player"+p_animationName, PlayerDownAnimation));
		}
		else if (p_animationName == "Right")
		{
			m_playerAnimations.insert(std::make_pair("Player" + p_animationName, PlayerRightAnimation));
		}
		else if (p_animationName == "Left")
		{
			m_playerAnimations.insert(std::make_pair("Player" + p_animationName, PlayerLeftAnimation));
		}
		else if (p_animationName == "Up")
		{
			m_playerAnimations.insert(std::make_pair("Player" + p_animationName, PlayerUpAnimation));
		}
	}
	void OVPlayer::draw(sf::RenderTarget &target, sf::RenderStates states) const
	{
		states.texture = m_playerSheet;
		target.draw(*m_playerSprite, states);
	
	}

	void OVPlayer::Update(float deltatime)
	{
		MoveTowards();
		m_playerSprite->update(sf::seconds(deltatime));
	}
	void OVPlayer::SetTargetPos(sf::Vector2f p_targetpos)
	{
		m_targetPos = p_targetpos;
	}
}