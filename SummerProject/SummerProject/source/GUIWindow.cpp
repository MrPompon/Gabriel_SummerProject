//GUIWindow.cpp

#include "stdafx.h"
#include "GUIWindow.hpp"
#include "BS_Player.hpp"
#include "BS_Enemy.hpp"
#include <iostream>
namespace spaceshooter
{
	GUIWindow::GUIWindow(float p_originX, float p_originY, float firstWordX, float firstWordY, float p_wordDistance, int p_rows, int p_colums)
	{
		for (unsigned int r = 0; r < p_rows; r++)
		{
			for (unsigned int c = 0; c < p_colums; c++)
			{
				CreateWord((p_originX + firstWordX)+(p_wordDistance*r), (p_originY + firstWordY)+(p_wordDistance*c));
			}
		}
		//m_player =p_player;
		//m_enemy = p_enemy;
		//InitializeWindow();
		
	}
	GUIWindow::~GUIWindow()
	{

	}
	void GUIWindow::InitializeWindow()
	{
		if (!hudBattleFont.loadFromFile("../assets/Fonts/SuperMario256.ttf"))
		{
			std::cout << "Failed to load font" << std::endl;
		}
	}
	void GUIWindow::CreateWord(float p_posX,float p_posY)
	{
		Word*word = new Word;
		word->word_text.setString("testText");
		word->position.x = p_posX;
		word->position.y = p_posY;
		word->word_text.setFont(hudBattleFont);
		word->word_text.setCharacterSize(40);
		word->word_text.setPosition(word->position);
		word->word_text.setColor(sf::Color::White);
		word->word_text.setStyle(sf::Text::Bold | sf::Text::Italic);
		std::cout << "NEW WORD CREATED position is"<<word->position.x<<" "<<word->position.y;
		wordVector.push_back(*word);
	}
	void GUIWindow::Update(float deltatime)
	{
		std::cout <<"IM A WINDOW I EXIST" << std::endl;
	}
	std::vector<Word>GUIWindow::GetWordVector()
	{
		return wordVector;
	}
	void GUIWindow::draw(sf::RenderTarget &target, sf::RenderStates states) const
	{
		for (int i = 0; i < wordVector.size(); ++i)
		{
			states.texture = &m_texture;
			target.draw(wordVector[i].word_text, states);
		}
	}
}// namespace spaceshooter