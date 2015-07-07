//OVPlayer.hpp

#ifndef OVPlayer_HPP_INCLUDED
#define OVPlayer_HPP_INCLUDED


namespace spaceshooter
{
	class Animation;
	class AnimatedSprite;

	class OVPlayer : public sf::Drawable, sf::Transformable
	{
	public:
		OVPlayer();
		~OVPlayer();
		void Update(float deltatime);
		void SetTargetPos(sf::Vector2f p_targetpos);
		void draw(sf::RenderTarget &target, sf::RenderStates states) const;
	private:
		//Animation
		TextureManager*m_textureManager;
		void InitAnimation(std::string p_animationName);
		void AddAnimationFrame(std::string p_animationName);
		std::vector<AnimatedSprite*> m_animatedSpritesVector;
		std::map<std::string, Animation*>m_playerAnimations;
		sf::Texture *m_playerSheet;
		float m_imageWidth;
		float m_imageHeight;
		int m_colums;
		int m_rows;
		int m_offsetX;
		int m_offsetY;
		int m_screenHeight;
		int m_screenWidth;
		//playeranimations
		Animation* PlayerRightAnimation;
		Animation* PlayerLeftAnimation;
		Animation* PlayerUpAnimation; 
		Animation* PlayerDownAnimation;
		AnimatedSprite* m_playerSprite;
		sf::Vector2f m_currentPos;
		sf::Vector2f m_targetPos;
		void MoveTowards();
	};
}// namespace spaceshooter

#endif // OVPlayer_HPP_INCLUDED