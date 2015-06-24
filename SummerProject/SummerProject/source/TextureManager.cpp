// TextureManager.cpp

#include "stdafx.h"
#include "TextureManager.hpp"

namespace spaceshooter
{
	TextureManager::TextureManager()
	{
	}

	TextureManager::~TextureManager()
	{
	}

	bool TextureManager::Initialize()
	{
		return true;
	}

	void TextureManager::Shutdown()
	{
		auto itr = m_textures.begin();
		while (itr != m_textures.end())
		{
			delete itr->second;
			++itr;
		}
		m_textures.clear();
	}

	sf::Texture* TextureManager::CreateTextureFromFile(const std::string& filename)
	{
		auto itr = m_textures.find(filename);
		if (itr == m_textures.end())
		{
			sf::Texture* texture = new sf::Texture;
			if (!texture || !texture->loadFromFile(filename))
			{
				// note(tommi): something went really wrong, we should find out why before proceeding
				// note(tommi): we also want to log this somehow, probably with Debug class
				// Debug::FatalError("...");
				assert(false);
			}
			m_textures.insert(std::pair<std::string, sf::Texture*>(filename, texture));
			itr = m_textures.find(filename);
		}
		return itr->second;
	}

	void TextureManager::DestroyTexture(sf::Texture* texture)
	{
		assert(texture);
		auto itr = m_textures.begin();
		while (itr != m_textures.end())
		{
			if (itr->second == texture)
			{
				delete itr->second;
				m_textures.erase(itr);
				break;
			}
		}
	}
} // namespace spaceshooter
