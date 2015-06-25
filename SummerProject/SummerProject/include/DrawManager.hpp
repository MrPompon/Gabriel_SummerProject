// DrawManager.hpp

#ifndef DRAWMANAGER_HPP_INCLUDED
#define DRAWMANAGER_HPP_INCLUDED

namespace spaceshooter
{
	class DrawManager
	{
		DrawManager(const DrawManager&);
		DrawManager& operator=(const DrawManager&);

	public:
		DrawManager(sf::RenderWindow* window);
		~DrawManager();

		bool Initialize();
		void Shutdown();

		void Draw(const sf::Drawable& drawable, const sf::RenderStates& states = sf::RenderStates::Default);
		sf::RenderWindow* getWindow() const;
	private:
		sf::RenderWindow* m_window;
	};
} // namespace spaceshooter

#endif // DRAWMANAGER_HPP_INCLUDED
