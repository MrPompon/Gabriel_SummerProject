// Math.hpp

#ifndef MATH_HPP_INCLUDED
#define MATH_HPP_INCLUDED

namespace spaceshooter
{
	// note(tommi): math utility and helper functions
	template <class T>
	T Clamp(const T a, const T min, const T max)
	{
		//a < min ? min : a > max ? max : a;
		if (a < min)
			return min;
		else if (a > max)
			return max;
		return a;
	}

	template <class T>
	bool Limit(T& a, const T min, const T max)
	{
		//a = a < min ? min : a > max ? max : a;
		if (a < min)
		{
			a = min;
			return true;
		}
		else if (a > max)
		{
			a = max;
			return true;
		}
		return false;
	}

	// note(tommi): functions to return random numbers
	float Random(float min, float max);

	// note(tommi): converting between radians and degrees
	float ToDegrees(float radians);
	float ToRadians(float degrees);

	// note(tommi): below functions are helpers for handling vector2f
	float Dot(const sf::Vector2f& vec0, const sf::Vector2f& vec1);
	float Length(sf::Vector2f& vec);
	float Normalize(sf::Vector2f& vec);
} // namespace spaceshooter

#endif // MATH_HPP_INCLUDED
