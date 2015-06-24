// DrawManager.cpp

#include "stdafx.h"
#include "DrawManager.hpp"

namespace spaceshooter
{
	DrawManager::DrawManager(sf::RenderWindow* window)
	{
		m_window = window;
	}

	DrawManager::~DrawManager()
	{
	}

	bool DrawManager::Initialize()
	{
		return true;
	}

	void DrawManager::Shutdown()
	{
		m_window = nullptr;
	}

	void DrawManager::Draw(const sf::Drawable& drawable, const sf::RenderStates& states)
	{
		m_window->draw(drawable, states);
	}
} // namespace spaceshooter
