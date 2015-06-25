// GUIWindow.hpp
#ifndef GUIWindow_HPP_INCLUDED
#define GUIWindow_HPP_INCLUDED

#include <SFML\Graphics.hpp>
class BS_Player;
class BS_Enemy;
namespace spaceshooter
{
	struct Word
	{
		sf::Vector2f position;
		sf::Text word_text;

	};
	class GUIWindow:public sf::Drawable
	{
		
	public:
		GUIWindow(float p_originX, float p_originY, float firstWordX, float firstWordY, float p_wordDistance, int p_rows, int p_colums);
		~GUIWindow();
		void Update(float deltatime);
		void InitializeWindow();
		void draw(sf::RenderTarget &target, sf::RenderStates states) const;
		void CreateWord(float p_posX, float p_posY);
		std::vector<Word>GetWordVector();
	private:
		bool m_visible;
		std::vector<std::string> m_playerSkills;
		BS_Player *m_player;
		BS_Enemy *m_enemy;
		std::vector<Word> wordVector;
		sf::Font hudBattleFont;
		sf::Texture m_texture;
	};
}// namespace spaceshooter
#endif // GUIWINDOW_HPP_INCLUDED