// GUIWindow.hpp
#ifndef GUIWindow_HPP_INCLUDED
#define GUIWindow_HPP_INCLUDED

#include <SFML\Graphics.hpp>

namespace spaceshooter
{
class BS_Player;
class BS_Enemy;
class DrawManager;
class InputManager;
class BattleState;
class TextureManager;
	struct Word:public sf::Transformable
	{
		sf::Vector2f position;
		sf::Text word_text;
		bool isHovered;
		bool isClickable;
		bool isHightlightable;
		std::string GetWordText();
		sf::Text GetSFWordText();
		void SetSFWordText(std::string p_sfWordText);
		void SetWordText(std::string p_WordText);
		void SetHovered(bool trueOrFalse);
		bool GetHovered();
		void Update(float deltatime);
	private:
		
	};
	class GUIWindow :public sf::Drawable, public sf::Transformable
	{
		
	public:
		GUIWindow();
		GUIWindow(BattleState* p_battlestate, BS_Player *m_player, BS_Enemy *m_enemy, std::string windowName, float p_originX, float p_originY, float firstWordX, float firstWordY, float p_wordDistanceWidth, float p_wordDistanceHeight, int p_fontSize, int p_rows, int p_colums);
		~GUIWindow();
		void Update(float deltatime);
		void InitializeFont();
		void draw(sf::RenderTarget &target, sf::RenderStates states) const;
		void CreateWord(std::string p_wordText, bool p_clickable, bool p_hightlightable, float p_posX, float p_posY, int p_fontsize);
		void CreateWindow(std::string p_windowName, float p_originX, float p_originY, float firstWordX, float firstWordY, float p_wordDistanceWidth, float p_wordDistanceHeight, int p_fontSize, int p_rows, int p_colums);
		void SetWindowVisible(bool trueOrFalse);
		bool GetWindowVisible();
		std::string GetWindowName();
		std::vector<Word>GetWordVector();
	private:
		void InitVariables(std::string m_windowName, float windowOriginX, float windowOriginY);
	private:
		DrawManager *m_draw_manager;
		InputManager *m_input_manager;
		sf::Mouse m_mouse;
		sf::Vector2f m_windowOrigin;
		bool m_visible;
		std::string m_windowName;
		std::vector<std::string> m_playerSkills;
		BS_Player *m_player;
		BS_Enemy *m_enemy;
		BattleState *m_battleState;
		std::vector<Word> wordVector;
		sf::Font hudBattleFont;
		sf::Texture m_texture;
		sf::Texture *m_tex_window;
		sf::Sprite m_spr_window;
	};
}// namespace spaceshooter
#endif // GUIWINDOW_HPP_INCLUDED