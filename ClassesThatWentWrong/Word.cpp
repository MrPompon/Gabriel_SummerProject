// Word.cpp

#include "stdafx.h"
#include "Word.hpp"
#include <iostream>
namespace spaceshooter
{
	Word::Word()
	{

	}

	Word::~Word()
	{
	}
	void Word::SetHovered(bool trueOrFalse)
	{
		m_isHovered = trueOrFalse;
	}
	void Word::ChangeWordText(std::string p_wordText)
	{
		m_wordTextString = p_wordText;
	}
	bool Word::GetHovered()
	{
		return m_isHovered;
	}
	std::string Word::GetWordText()
	{
		return m_word_text.getString();
	}
	sf::Text Word::GetSFWordText()
	{
		return m_word_text;
	}
	void Word::SetPosition(float x, float y)
	{
		m_position.x = x;
		m_position.y = y;
	}
	void Word::SetWordText(std::string wordText)
	{
		m_wordTextString = wordText;
	}
	void Word::InitWord(float fontSize,sf::Font p_font)
	{
		m_word_text.setFont(p_font);
		m_word_text.setCharacterSize(fontSize);
		m_word_text.setPosition(m_position);
		m_word_text.setColor(sf::Color::White);
		m_word_text.setStyle(sf::Text::Bold | sf::Text::Italic);
	}
	void Word::SetSFWordText(sf::Text p_text)
	{
		m_word_text = p_text;
	}
	sf::Vector2f Word::GetPosition()
	{
		return m_position;
	}
} // namespace spaceshooter
