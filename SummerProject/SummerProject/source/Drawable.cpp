// Drawable.cpp

#include "stdafx.h"
#include "Drawable.hpp"

namespace spaceshooter
{
	Drawable::~Drawable()
	{
	}

	void Drawable::OnDraw(sf::RenderTarget& target, const sf::RenderStates& states) const
	{
		this->draw(target, states);
	}
} // namespace spaceshooter
