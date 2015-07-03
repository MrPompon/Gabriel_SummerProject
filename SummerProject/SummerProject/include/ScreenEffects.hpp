// ScreenEffects.hpp

#ifndef ScreenEffects_HPP_INCLUDED
#define ScreenEffects_HPP_INCLUDED

namespace spaceshooter
{
	class TextureManager;
	class AnimatedSprite;
	class Animation;
	class DrawManager;
	class ScreenEffects : public sf::Drawable
	{
	public:
		ScreenEffects(sf::RenderWindow*p_renderWindow, std::string p_effectName, float p_effectDuration);
		~ScreenEffects();
		void draw(sf::RenderTarget &target, sf::RenderStates states) const;
		void Update(float deltatime);
		void SetDay();
		void SetNight();
		void SetBlaze(float duration);
		void ScreenShake(float screenShakeAmount, float duration);
		sf::RectangleShape GetRectangleShape();
	private:
		std::string m_name;
		float m_lifeTime;
		bool m_visible;
		sf::View m_view;
		sf::RenderWindow* m_renderWindow;
		DrawManager*m_drawmanager;
		float m_screen_width;
		float m_screen_height;

		sf::RectangleShape m_screenEffectRect;
		enum ScreenEffect
		{
			EFFECT_SHAKING,
			EFFECT_NIGHT,
			EFFECT_DAY,
			EFFECT_BLAZE,

		};
		ScreenEffect screenEffect;
	};
} // namespace spaceshooter

#endif // ScreenEffects_HPP_INCLUDED
