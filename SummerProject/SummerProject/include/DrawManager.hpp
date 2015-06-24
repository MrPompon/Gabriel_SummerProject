// DrawManager.hpp

#ifndef DRAWMANAGER_HPP_INCLUDED
#define DRAWMANAGER_HPP_INCLUDED

namespace spaceshooter
{
	class DrawManager
	{
		// note(tommi): making the copy constructor and 
		// assignment operator private we make the class
		// non-copyable
		DrawManager(const DrawManager&);
		DrawManager& operator=(const DrawManager&);

	public:
		DrawManager(sf::RenderWindow* window);
		~DrawManager();

		bool Initialize();
		void Shutdown();

		void Draw(const sf::Drawable& drawable, const sf::RenderStates& states);

	private:
		sf::RenderWindow* m_window;
	};
} // namespace spaceshooter

#endif // DRAWMANAGER_HPP_INCLUDED
