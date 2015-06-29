//GUIWindow.cpp

#include "stdafx.h"
#include "GUIWindow.hpp"
#include "BS_Player.hpp"
#include "BS_Enemy.hpp"
#include "BattleState.hpp"
#include "DrawManager.hpp"
#include "InputManager.hpp"
#include "ServiceLocator.hpp"
#include "TextureManager.hpp"
#include <iostream>
namespace spaceshooter
{
	GUIWindow::GUIWindow(BattleState* p_battlestate, BS_Player *p_player, BS_Enemy *p_enemy, std::string p_windowName, float p_originX, float p_originY, float firstWordX, float firstWordY, float p_wordDistanceWidth, float p_wordDistanceHeight, int p_fontSize, int p_rows, int p_colums)
	{
		InputManager* input_manager = ServiceLocator<InputManager>::GetService();
		m_draw_manager = ServiceLocator<DrawManager>::GetService();
		m_mouse = m_input_manager->GetMouse();
		m_player = p_player;
		m_enemy = p_enemy;
		m_battleState = p_battlestate;
		InitVariables(p_windowName, p_originX, p_originY);
		InitializeFont();
		CreateWindow(p_windowName,p_originX,p_originY,firstWordX,firstWordY,p_wordDistanceWidth,p_wordDistanceHeight,p_fontSize,p_rows,p_colums);
		
		
		//InitializeWindow();
		
	}
	GUIWindow::GUIWindow()
	{

	}
	GUIWindow::~GUIWindow()
	{

	}
	std::string GUIWindow::GetWindowName()
	{
		return m_windowName;
	}
	void GUIWindow::InitVariables(std::string p_windowName,float p_windowOriginX,float p_windowOriginY)
	{
		m_visible = true;
		m_windowName = p_windowName;
		m_windowOrigin.x = p_windowOriginX;
		m_windowOrigin.y = p_windowOriginY;
	}
	void GUIWindow::SetWindowVisible(bool p_trueOrFalse)
	{
		m_visible = p_trueOrFalse;
	}
	bool GUIWindow::GetWindowVisible()
	{
		return m_visible;
	}
	void GUIWindow::InitializeFont()
	{
		if (!hudBattleFont.loadFromFile("../assets/Fonts/SuperMario256.ttf"))
		{
			std::cout << "Failed to load font" << std::endl;
		}
	}
	void GUIWindow::CreateWindow(std::string p_windowName, float p_originX, float p_originY, float firstWordX, float firstWordY, float p_wordDistanceWidth, float p_wordDistanceHeight, int p_fontSize, int p_rows, int p_colums)
	{
		//defines which window it is depening on name, made it like this because it gives the possibility to change if text is clickable and not, and where it should link or whatever. 
		if (p_windowName == "SkillMenu")
		{
			m_playerSkills = m_player->GetPlayerSkills();
			for (unsigned int i = 0; i < m_playerSkills.size(); i++)
			{
				std::cout << m_playerSkills[i];
			}
			for (unsigned int r = 0; r < p_rows; r++)
			{
				for (unsigned int c = 0; c < p_colums; c++)
				{
					//need to define what each string should be by getting player skills
					//C+R DOES NOT WORK ATM, NEED TO FIX SOMEHOW
					CreateWord(m_playerSkills[c+r], true, true, (p_originX + firstWordX) + (p_wordDistanceWidth*r), (p_originY + firstWordY) + (p_wordDistanceHeight*c), p_fontSize);
				}
			}
			TextureManager* texture_manager = ServiceLocator<TextureManager>::GetService();
			m_tex_window = texture_manager->CreateTextureFromFile("../assets/Sprites/BS_LifeBar/window_background.png");
			m_spr_window.setTexture(*m_tex_window);
			m_spr_window.setPosition(p_originX, p_originY);
				//add titletothe"BOX"
				CreateWord(m_windowName, false, false, m_windowOrigin.x, m_windowOrigin.y, 15);
		}
		else if (p_windowName == "OptionsMenu")
		{
			for (unsigned int r = 0; r < p_rows; r++)
			{
				for (unsigned int c = 0; c < p_colums; c++)
				{
					//need to define what each string should be by getting player skills
					
					switch (c)
					{
					case 0:CreateWord("Placeholder", true, true, (p_originX + firstWordX) + (p_wordDistanceWidth*r), (p_originY + firstWordY) + (p_wordDistanceHeight*c), p_fontSize);
						break;
					case 1:CreateWord("Another", true, true, (p_originX + firstWordX) + (p_wordDistanceWidth*r), (p_originY + firstWordY) + (p_wordDistanceHeight*c), p_fontSize);
						break;
					case 2:CreateWord("Swag", true, true, (p_originX + firstWordX) + (p_wordDistanceWidth*r), (p_originY + firstWordY) + (p_wordDistanceHeight*c), p_fontSize);
						break;
					case 3:CreateWord("Lars", true, true, (p_originX + firstWordX) + (p_wordDistanceWidth*r), (p_originY + firstWordY) + (p_wordDistanceHeight*c), p_fontSize);
						break;
					case 4:CreateWord("Destroy", true, true, (p_originX + firstWordX) + (p_wordDistanceWidth*r), (p_originY + firstWordY) + (p_wordDistanceHeight*c), p_fontSize);
						break;
					case 5:CreateWord("asdasd", true, true, (p_originX + firstWordX) + (p_wordDistanceWidth*r), (p_originY + firstWordY) + (p_wordDistanceHeight*c), p_fontSize);
						break;
					case 6:CreateWord("Exit Game", true, true, (p_originX + firstWordX) + (p_wordDistanceWidth*r), (p_originY + firstWordY) + (p_wordDistanceHeight*c), p_fontSize);
						break;
					}
				}
			}
			//add titletothe"BOX"
			//CreateWord(m_windowName, false, false, m_windowOrigin.x, m_windowOrigin.y, 20);
			TextureManager* texture_manager = ServiceLocator<TextureManager>::GetService();
			m_tex_window = texture_manager->CreateTextureFromFile("../assets/Sprites/BS_LifeBar/m_options_background.png");
			m_spr_window.setTexture(*m_tex_window);
			m_spr_window.setPosition(p_originX, p_originY);
		}
	}
	void GUIWindow::CreateWord(std::string p_wordText,bool p_clickable,bool p_hightlightable,float p_posX,float p_posY, int p_fontsize)
	{
		Word*word = new Word;
		word->word_text.setString(p_wordText);
		word->position.x = p_posX;
		word->position.y = p_posY;
		word->isHovered = false;
		word->word_text.setFont(hudBattleFont);
		word->word_text.setCharacterSize(p_fontsize);
		word->word_text.setPosition(word->position);
		word->word_text.setColor(sf::Color::White);
		word->word_text.setStyle(sf::Text::Bold | sf::Text::Regular);
		word->isClickable = p_clickable;
		word->isHightlightable = p_hightlightable;
		wordVector.push_back(*word);
	}
	
	void GUIWindow::Update(float deltatime)
	{
		sf::Vector2f mousePosition = m_draw_manager->getWindow()->mapPixelToCoords(m_mouse.getPosition(*m_draw_manager->getWindow()));
			if (m_visible)
			{
				for (unsigned int i = 0; i < wordVector.size(); i++)
				{
					sf::FloatRect Intersection;
					if (wordVector[i].GetSFWordText().getGlobalBounds().contains(mousePosition))
					{
						wordVector[i].SetHovered(true);
						if (m_mouse.isButtonPressed(m_mouse.Left) && wordVector[i].isClickable)
						{
							sf::Text compareText = wordVector[i].word_text;
								for (unsigned int j = 0; j <m_playerSkills.size(); j++)
								{
									if (compareText.getString() == m_playerSkills[j])
									{
										if (m_playerSkills[j] == m_battleState->m_player_skill_1_Name)
										{
											m_battleState->PlayerUseSkill(0);
											m_battleState->ChangeTurn(m_battleState->m_player_skill_1_animTime);
											std::cout << "You are clicking skill number 1";
										}
										else if (m_playerSkills[j] == m_battleState->m_player_skill_2_Name)
										{
											m_battleState->PlayerUseSkill(1);
											m_battleState->ChangeTurn(m_battleState->m_player_skill_2_animTime);
											std::cout << "You are clicking skill number 2";
										}
										else if (m_playerSkills[j] == m_battleState->m_player_skill_3_Name)
										{
											m_battleState->PlayerUseSkill(2);
											m_battleState->ChangeTurn(m_battleState->m_player_skill_3_animTime);
											std::cout << "You are clicking skill number 3";
										}
										else if (m_playerSkills[j] == m_battleState->m_player_skill_4_Name)
										{
											m_battleState->PlayerUseSkill(3);
											m_battleState->ChangeTurn(m_battleState->m_player_skill_4_animTime);
											std::cout << "You are clicking skill number 4";
										}
										//std::cout << "You are clicking skill text";
									}
								}
							
				
						}
					}
					else
					{
						if (wordVector[i].isHovered)
						{
							wordVector[i].SetHovered(false);
						}
					}
					wordVector[i].Update(deltatime);
				}
			}
	}

	void GUIWindow::draw(sf::RenderTarget &target, sf::RenderStates states) const
	{
		if (m_visible)
		{
			if (m_windowName == "SkillMenu" || m_windowName== "OptionsMenu")
			{
				states.texture = m_tex_window;
				target.draw(m_spr_window, states);
			}
			for (int i = 0; i < wordVector.size(); ++i)
			{
				states.texture = &m_texture;
				target.draw(wordVector[i].word_text, states);
			}
			
		}
	}
	void Word::SetSFWordText(std::string p_sfWordText)
	{
		word_text.setString(p_sfWordText);
	}
	void Word::SetWordText(std::string p_WordText)
	{
		
	}
	std::vector<Word>GUIWindow::GetWordVector()
	{
		return wordVector;
	}
	void Word::SetHovered(bool trueOrFalse)
	{
		isHovered = trueOrFalse;
	}
	bool Word::GetHovered()
	{
		return isHovered;
	}
	std::string Word::GetWordText()
	{
		return word_text.getString();
	}
	sf::Text Word::GetSFWordText()
	{
		return word_text;
	}
	void Word::Update(float deltatime)
	{
		if (isHovered && isHightlightable)
		{
			//wordVector[i].GetSFWordText().setColor(sf::Color::Green);
			word_text.setColor(sf::Color::Red);
		}
		else if (!isHovered && isHightlightable)
		{
			if (word_text.getColor() != sf::Color::White)
			{
				word_text.setColor(sf::Color::White);
			}
		}
	
	}
}// namespace spaceshooter