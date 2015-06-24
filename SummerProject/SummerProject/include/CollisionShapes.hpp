// CollisionShapes.hpp

#ifndef COLLISIONSHAPES_HPP_INCLUDED
#define COLLISIONSHAPES_HPP_INCLUDED

namespace spaceshooter
{
	class AxisAlignedBoundingBox
	{
	public:
		AxisAlignedBoundingBox();
		AxisAlignedBoundingBox(const sf::Vector2f& center, const sf::Vector2f& extent);

		const sf::Vector2f& GetCenter() const;
		void SetCenter(const sf::Vector2f& center);
		const sf::Vector2f& GetExtent() const;
		void SetExtent(const sf::Vector2f& extent);

	private:
		sf::Vector2f m_center;
		sf::Vector2f m_extent;
	};

	class BoundingCircle
	{
	public:
		BoundingCircle();
		BoundingCircle(const sf::Vector2f& center, float radius);

		const sf::Vector2f& GetCenter() const;
		void SetCenter(const sf::Vector2f& center);
		float GetRadius() const;
		void SetRadius(float radius);

	private:
		sf::Vector2f m_center;
		float m_radius;
	};

	class ObjectOrientedBoundingBox
	{
	public:
		ObjectOrientedBoundingBox();
		ObjectOrientedBoundingBox(const sf::Vector2f& center, const sf::Vector2f& extent, float radians);

		const sf::Vector2f& GetCenter() const;
		void SetCenter(const sf::Vector2f& center);
		const sf::Vector2f& GetExtent() const;
		void SetExtent(const sf::Vector2f& extent);
		float GetRadians() const;
		void SetRadians(float radians);

		const sf::Vector2f& GetCorner(unsigned int index) const;

	private:
		void RecalculateCorners();

	private:
		sf::Vector2f m_center;
		sf::Vector2f m_extent;
		float m_radians;
		sf::Vector2f m_corners[4];
	};


	// note(tommi): functions to test if they overlap, and how much
	bool Overlap(const AxisAlignedBoundingBox& lhs, const AxisAlignedBoundingBox& rhs, sf::Vector2f& overlap);
	bool Overlap(const AxisAlignedBoundingBox& lhs, const BoundingCircle& rhs, sf::Vector2f& overlap);
} // namespace spaceshooter

#endif // COLLISIONSHAPES_HPP_INCLUDED
