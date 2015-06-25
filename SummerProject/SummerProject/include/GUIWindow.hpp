// GUIWindow.hpp
#ifndef GUIWindow_HPP_INCLUDED
#define GUIWindow_HPP_INCLUDED

#include <SFML\Graphics.hpp>
class BS_Player;
class BS_Enemy;
namespace spaceshooter
{
	struct Word:public sf::Transformable
	{
		sf::Vector2f position;
		sf::Text word_text;
		std::string GetWordText();
		sf::Text GetSFWordText();
		void SetHovered(bool trueOrFalse);
		bool GetHovered();
		bool isHovered;
	private:
		
	};
	class GUIWindow :public sf::Drawable, public sf::Transformable
	{
		
	public:
		GUIWindow();
		GUIWindow(std::string windowName,float p_originX, float p_originY, float firstWordX, float firstWordY, float p_wordDistanceWidth, float p_wordDistanceHeight, int p_fontSize, int p_rows, int p_colums);
		~GUIWindow();
		void Update(float deltatime);
		void InitializeFont();
		void draw(sf::RenderTarget &target, sf::RenderStates states) const;
		void CreateWord(std::string p_wordText, float p_posX, float p_posY, int p_fontsize);
		void SetWindowVisible(bool trueOrFalse);
		bool GetWindowVisible();
		std::string GetWindowName();
		std::vector<Word>GetWordVector();
	private:
		void InitVariables(std::string m_windowName, float windowOriginX, float windowOriginY);
	private:
		sf::Vector2f m_windowOrigin;
		bool m_visible;
		std::string m_windowName;
		std::vector<std::string> m_playerSkills;
		BS_Player *m_player;
		BS_Enemy *m_enemy;
		std::vector<Word> wordVector;
		sf::Font hudBattleFont;
		sf::Texture m_texture;
	};
}// namespace spaceshooter
#endif // GUIWINDOW_HPP_INCLUDED