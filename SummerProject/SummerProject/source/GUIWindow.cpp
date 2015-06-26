//GUIWindow.cpp

#include "stdafx.h"
#include "GUIWindow.hpp"
#include "BS_Player.hpp"
#include "BS_Enemy.hpp"
#include <iostream>
namespace spaceshooter
{
	GUIWindow::GUIWindow(BS_Player *m_player, BS_Enemy *m_enemy,std::string p_windowName, float p_originX, float p_originY, float firstWordX, float firstWordY, float p_wordDistanceWidth, float p_wordDistanceHeight, int p_fontSize, int p_rows, int p_colums)
	{
		InitVariables(p_windowName, p_originX, p_originY);
		InitializeFont();
		for (unsigned int r = 0; r < p_rows; r++)
		{
			for (unsigned int c = 0; c < p_colums; c++)
			{
				//need to define what each string should be by getting player skills
				CreateWord("TestText",(p_originX + firstWordX)+(p_wordDistanceWidth*r), (p_originY + firstWordY)+(p_wordDistanceHeight*c),p_fontSize);
			}
		}
		//add titletothe"BOX"
		CreateWord(m_windowName,m_windowOrigin.x, m_windowOrigin.y, 15);
		//m_player =p_player;
		//m_enemy = p_enemy;
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
	void GUIWindow::CreateWord(std::string p_wordText,float p_posX,float p_posY, int p_fontsize)
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
		word->word_text.setStyle(sf::Text::Bold | sf::Text::Italic);
		std::cout << "NEW WORD CREATED position is"<<word->position.x<<" "<<word->position.y;
		wordVector.push_back(*word);
	}
	
	void GUIWindow::Update(float deltatime)
	{
		//Should get and update text string so that they are updated(duh)
		for (unsigned int i = 0; i < wordVector.size(); i++)
		{
			if (wordVector[i].GetHovered()==true)
			{
				wordVector[i].GetSFWordText().setColor(sf::Color::Green);
			}
		}
	}

	void GUIWindow::draw(sf::RenderTarget &target, sf::RenderStates states) const
	{
		if (m_visible)
		{
			for (int i = 0; i < wordVector.size(); ++i)
			{
				states.texture = &m_texture;
				target.draw(wordVector[i].word_text, states);
			}
		}
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
}// namespace spaceshooter