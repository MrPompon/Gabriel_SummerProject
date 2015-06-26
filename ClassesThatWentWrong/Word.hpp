// Word.hpp

#ifndef WORD_HPP_INCLUDED
#define WORD_HPP_INCLUDED

namespace spaceshooter
{
	class Word
	{
	public:
		Word();
		~Word();
		
		std::string GetWordText();
		sf::Text GetSFWordText();
		void ChangeWordText(std::string p_wordText);
		void SetHovered(bool trueOrFalse);
		bool GetHovered();
		void SetPosition(float x, float y);
		void SetSFWordText(sf::Text);
		void SetWordText(std::string wordText);
		sf::Vector2f GetPosition();
		void InitWord(float fontSize,sf::Font p_font);
	private:
		sf::Vector2f m_position;
		sf::Text m_word_text;
		std::string m_wordTextString;
		bool m_isHovered;
	};
} // namespace spaceshooter

#endif // WORD_HPP_INCLUDED
