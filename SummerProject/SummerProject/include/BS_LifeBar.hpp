// BS_LifeBar.hpp

#ifndef BS_LIFEBAR_HPP_INCLUDED
#define BS_LIFEBAR_HPP_INCLUDED

#include <SFML\Graphics.hpp>

namespace spaceshooter
{
	class BS_Player;
	class BS_Enemy;
	class BattleState;
	class TextureManager;
	class BS_LifeBar :public sf::Transformable, public sf::Drawable
	{
	public:
		BS_LifeBar(BattleState *p_battleState, BS_Player* p_player, sf::Vector2f p_position);
		BS_LifeBar(BattleState *p_battleState, BS_Enemy* p_enemy, sf::Vector2f p_position);
		void draw(sf::RenderTarget &target, sf::RenderStates states) const;
		~BS_LifeBar();
		void Update(float deltatime);
	private:
		sf::Vector2f m_position;
		void InitLifeBar();
		BS_Player* m_player;
		BS_Enemy* m_enemy;
		BattleState* m_battleState;
		bool enemysLifeBar;
		bool playersLifeBar;
		sf::Sprite m_lifebar;
		sf::Texture *m_lifebarTexture;
		sf::Sprite m_spr_lifebarBackground;
		sf::Texture *m_tex_lifebarBackground;
		float maximumLife;
		float currentLife;
	};
} // namespace spaceshooter

#endif // BS_LIFEBAR_HPP_INCLUDED
