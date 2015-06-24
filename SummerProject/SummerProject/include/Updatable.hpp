// Updatable.hpp

#ifndef UPDATABLE_HPP_INCLUDED
#define UPDATABLE_HPP_INCLUDED

namespace spaceshooter
{
	class Updatable
	{
	public:
		virtual ~Updatable();
		virtual void OnUpdate(float deltatime) = 0;
	};
} // namespace spaceshooter

#endif // UPDATABLE_HPP_INCLUDED
