// Drawable.hpp

#ifndef DRAWABLE_HPP_INCLUDED
#define DRAWABLE_HPP_INCLUDED

namespace spaceshooter
{
	class Drawable : sf::Drawable
	{
	public:
		virtual ~Drawable();
		virtual void OnDraw(sf::RenderTarget& target, const sf::RenderStates& states) const;
	};
} // namespace spaceshooter

#endif // DRAWABLE_HPP_INCLUDED
