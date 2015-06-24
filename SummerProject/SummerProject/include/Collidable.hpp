// Collidable.hpp

#ifndef COLLIDABLE_HPP_INCLUDED
#define COLLIDABLE_HPP_INCLUDED

namespace spaceshooter
{
	class Collidable
	{
	public:
		virtual ~Collidable();
		virtual void OnCollision(const Collidable& other) = 0;
	};
} // namespace spaceshooter

#endif // COLLIDABLE_HPP_INCLUDED
