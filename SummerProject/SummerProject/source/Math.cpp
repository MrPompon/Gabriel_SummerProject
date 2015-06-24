// Math.cpp

#include "stdafx.h"
#include <cmath>
#include "Math.hpp"

namespace spaceshooter
{
	static float const PI = 3.141592653f;

	// note(tommi): linear congruential generator
	static unsigned int random()
	{
		static unsigned int seed = (unsigned int)time(0);
		seed = (1103515245 * seed + 12345) % 0xffffffff;
		return seed;
	}

	static float randf()
	{
		return (float)((double)random() / (double)0xffffffff);
	}

	// random function
	float Random(float min, float max)
	{
		return min + ((max - min) * randf());
	}

	// angle helpers
	float ToDegrees(float radians)
	{
		return radians * 180.0f / PI;
	}

	float ToRadians(float degrees)
	{
		return degrees * PI / 180.0f;
	}

	// sf::Vector2f helpers
	float Dot(const sf::Vector2f& vec0, const sf::Vector2f& vec1)
	{
		return vec0.x * vec1.x + vec0.y * vec1.y;
	}

	float Length(sf::Vector2f& vec)
	{
		return sqrtf(vec.x*vec.x + vec.y*vec.y);
	}

	float Normalize(sf::Vector2f& vec)
	{
		float len = Length(vec);
		if (len > 0.0f)
		{
			vec.x /= len;
			vec.y /= len;
		}
		return len;
	}
} // namespace spaceshooter
