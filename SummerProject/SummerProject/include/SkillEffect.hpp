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
		SkillEffect(std::string skillName, float p_lifeTime, sf::Vector2f p_pos);
		~SkillEffect();
		void draw(sf::RenderTarget &target, sf::RenderStates states) const;
		void Update(float deltatime);
		void InitAnimation(std::string p_skillName);
	private:
		std::vector<AnimatedSprite*> m_animatedSpritesVector;
		std::map<std::string, Animation*>m_SkillEffectAnimations;
		float m_imageWidth;
		float m_imageHeight;
		int m_colums;
		int m_rows;
		int m_offsetX;
		int m_offsetY;
		int m_screenHeight;
		int m_screenWidth;
		sf::Vector2i m_enemyPos;
		sf::Vector2i m_playerPos;
		float m_lifeTime;
		sf::Texture* m_skillEffectSheet;
		AnimatedSprite* animSprite;
		std::string m_skillName;
		bool m_visible;
	};
} // namespace spaceshooter

#endif // SkillEffect_HPP_INCLUDED
