// AudioManager.hpp

#ifndef AUDIOMANAGER_HPP_INCLUDED
#define AUDIOMANAGER_HPP_INCLUDED

namespace spaceshooter
{
	class AudioManager
	{
		// note(tommi): making the copy constructor and 
		// assignment operator private we make the class
		// non-copyable
		AudioManager(const AudioManager&);
		AudioManager& operator=(const AudioManager&);

	public:
		AudioManager();
		~AudioManager();

		bool Initialize();
		void Shutdown();

		sf::SoundBuffer* CreateSoundFromFile(const std::string& filename);
		sf::Music* CreateMusicFromFile(const std::string& filename);

	private:
		std::map<std::string, sf::SoundBuffer*> m_sounds;
		std::map<std::string, sf::Music*> m_musics;
	};
} // namespace spaceshooter

#endif // AUDIOMANAGER_HPP_INCLUDED
