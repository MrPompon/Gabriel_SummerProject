// SkillEffect.hpp

#ifndef SkillEffect_HPP_INCLUDED
#define SkillEffect_HPP_INCLUDED

namespace spaceshooter
{
	class TextureManager;
	class AnimatedSprite;
	class Animation;
	class SkillEffect : public sf::Drawable
	{
	public:
		SkillEffect(std::string skillName);
		~SkillEffect();
		void draw(sf::RenderTarget &target, sf::RenderStates states) const;
		void Update(float deltatime);
	private:
		std::vector<AnimatedSprite*> m_animatedSpritesVector;
		std::map<std::string, Animation*>m_SkillEffectAnimations;
		
		sf::Texture* m_skillEffectSheet;
		AnimatedSprite* animSprite;
		std::string m_skillName;
		bool m_visible;
	};
} // namespace spaceshooter

#endif // SkillEffect_HPP_INCLUDED
