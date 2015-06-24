// CollisionShapes.cpp

#include "stdafx.h"
#include "CollisionShapes.hpp"

namespace spaceshooter
{
	AxisAlignedBoundingBox::AxisAlignedBoundingBox()
	{
	}

	AxisAlignedBoundingBox::AxisAlignedBoundingBox(const sf::Vector2f& center, const sf::Vector2f& extent)
	{
		m_center = center;
		m_extent = extent;
	}

	const sf::Vector2f& AxisAlignedBoundingBox::GetCenter() const
	{
		return m_center;
	}

	void AxisAlignedBoundingBox::SetCenter(const sf::Vector2f& center)
	{
		m_center = center;
	}

	const sf::Vector2f& AxisAlignedBoundingBox::GetExtent() const
	{
		return m_extent;
	}

	void AxisAlignedBoundingBox::SetExtent(const sf::Vector2f& extent)
	{
		m_extent = extent;
	}

	BoundingCircle::BoundingCircle()
	{
	}

	BoundingCircle::BoundingCircle(const sf::Vector2f& center, float radius)
	{
		m_center = center;
		m_radius = radius;
	}

	const sf::Vector2f& BoundingCircle::GetCenter() const
	{
		return m_center;
	}

	void BoundingCircle::SetCenter(const sf::Vector2f& center)
	{
		m_center = center;
	}

	float BoundingCircle::GetRadius() const
	{
		return m_radius;
	}

	void BoundingCircle::SetRadius(float radius)
	{
		m_radius = radius;
	}

	ObjectOrientedBoundingBox::ObjectOrientedBoundingBox()
	{
	}

	ObjectOrientedBoundingBox::ObjectOrientedBoundingBox(const sf::Vector2f& center, const sf::Vector2f& extent, float radians)
	{
		m_center = center;
		m_extent = extent;
		m_radians = radians;
		RecalculateCorners();
	}

	const sf::Vector2f& ObjectOrientedBoundingBox::GetCenter() const
	{
		return m_center;
	}

	void ObjectOrientedBoundingBox::SetCenter(const sf::Vector2f& center)
	{
		m_center = center;
	}

	const sf::Vector2f& ObjectOrientedBoundingBox::GetExtent() const
	{
		return m_extent;
	}

	void ObjectOrientedBoundingBox::SetExtent(const sf::Vector2f& extent)
	{
		m_extent = extent;
		RecalculateCorners();
	}

	float ObjectOrientedBoundingBox::GetRadians() const
	{
		return m_radians;
	}

	void ObjectOrientedBoundingBox::SetRadians(float radians)
	{
		m_radians = radians;
		RecalculateCorners();
	}

	const sf::Vector2f& ObjectOrientedBoundingBox::GetCorner(unsigned int index) const
	{
		assert(index < 4);
		return m_corners[index] + m_center;
	}

	void ObjectOrientedBoundingBox::RecalculateCorners()
	{
		const float fC = cosf(m_radians);
		const float fS = sinf(m_radians);

		m_corners[0].x = -m_extent.x;
		m_corners[0].y = -m_extent.y;
		m_corners[1].x =  m_extent.x;
		m_corners[1].y = -m_extent.y;
		m_corners[2].x =  m_extent.x;
		m_corners[2].y =  m_extent.y;
		m_corners[3].x = -m_extent.x;
		m_corners[3].y =  m_extent.y;

		for (unsigned int index = 0; index < 4; index++)
		{
			m_corners[index].x = m_corners[index].x * fC - m_corners[index].y * fS;
			m_corners[index].y = m_corners[index].x * fS + m_corners[index].y * fC;
		}
	}

	// overlaps
	bool Overlap(const AxisAlignedBoundingBox& lhs, const AxisAlignedBoundingBox& rhs, sf::Vector2f& overlap)
	{
		return false;
	}

	bool Overlap(const AxisAlignedBoundingBox& lhs, const BoundingCircle& rhs, sf::Vector2f& overlap)
	{
		return false;
	}
} // namespace spaceshooter
