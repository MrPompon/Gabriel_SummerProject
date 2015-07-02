// ScreenEffects.hpp

#ifndef ScreenEffects_HPP_INCLUDED
#define ScreenEffects_HPP_INCLUDED

namespace spaceshooter
{
	class TextureManager;
	class AnimatedSprite;
	class Animation;
	class ScreenEffects : public sf::Drawable
	{
	public:
		ScreenEffects();
		~ScreenEffects();
		void draw(sf::RenderTarget &target, sf::RenderStates states) const;
		void Update(float deltatime);
	private:
	
	};
} // namespace spaceshooter

#endif // ScreenEffects_HPP_INCLUDED
