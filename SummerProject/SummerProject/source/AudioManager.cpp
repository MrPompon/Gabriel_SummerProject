// AudioManager.cpp

#include "stdafx.h"
#include "AudioManager.hpp"

namespace spaceshooter
{
	AudioManager::AudioManager()
	{
	}

	AudioManager::~AudioManager()
	{
	}

	bool AudioManager::Initialize()
	{
		return true;
	}

	void AudioManager::Shutdown()
	{
		auto itrs = m_sounds.begin();
		while (itrs != m_sounds.end())
		{
			delete itrs->second;
			++itrs;
		}
		m_sounds.clear();

		auto itrm = m_musics.begin();
		while (itrm != m_musics.end())
		{
			delete itrm->second;
			++itrm;
		}
		m_musics.clear();
	}

	sf::SoundBuffer* AudioManager::CreateSoundFromFile(const std::string& filename)
	{
		auto itr = m_sounds.find(filename);
		if (itr == m_sounds.end())
		{
			sf::SoundBuffer* buffer = new sf::SoundBuffer;
			if (!buffer || !buffer->loadFromFile(filename))
			{
				// note(tommi): something went really wrong, we should find out why before proceeding
				// note(tommi): we also want to log this somehow, probably with Debug class
				// Debug::FatalError("...");
				assert(false);
			}
			m_sounds.insert(std::pair<std::string, sf::SoundBuffer*>(filename, buffer));
			itr = m_sounds.find(filename);
		}
		return itr->second;
	}

	sf::Music* AudioManager::CreateMusicFromFile(const std::string& filename)
	{
		auto itr = m_musics.find(filename);
		if (itr == m_musics.end())
		{
			sf::Music* music = new sf::Music;
			if (!music || !music->openFromFile(filename))
			{
				// note(tommi): something went really wrong, we should find out why before proceeding
				// note(tommi): we also want to log this somehow, probably with Debug class
				// Debug::FatalError("...");
				assert(false);
			}
			m_musics.insert(std::pair<std::string, sf::Music*>(filename, music));
			itr = m_musics.find(filename);
		}
		return itr->second;
	}
} // namespace spaceshooter
