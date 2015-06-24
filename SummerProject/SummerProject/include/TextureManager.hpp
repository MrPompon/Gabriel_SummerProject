// TextureManager.hpp

#ifndef TEXTUREMANAGER_HPP_INCLUDED
#define TEXTUREMANAGER_HPP_INCLUDED

namespace spaceshooter
{
	class TextureManager
	{
		// note(tommi): making the copy constructor and 
		// assignment operator private we make the class
		// non-copyable
		TextureManager(const TextureManager&);
		TextureManager& operator=(const TextureManager&);

	public:
		TextureManager();
		~TextureManager();

		bool Initialize();
		void Shutdown();

		sf::Texture* CreateTextureFromFile(const std::string& filename);
		void DestroyTexture(sf::Texture* texture);

	private:
		std::map<std::string, sf::Texture*> m_textures;
	};
} // namespace spaceshooter

#endif // TEXTUREMANAGER_HPP_INCLUDED
