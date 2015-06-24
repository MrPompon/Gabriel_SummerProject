// CollisionManager.hpp

#ifndef COLLISIONMANAGER_HPP_INCLUDED
#define COLLISIONMANAGER_HPP_INCLUDED

namespace spaceshooter
{
	class AbstractCollider;

	class CollisionManager
	{
		// note(tommi): making the copy constructor and 
		// assignment operator private we make the class
		// non-copyable
		CollisionManager(const CollisionManager&);
		CollisionManager& operator=(const CollisionManager&);

	public:
		CollisionManager();
		~CollisionManager();

		bool Initialize();
		void Shutdown();

	private:

	};
} // namespace spaceshooter

#endif // COLLISIONMANAGER_HPP_INCLUDED
