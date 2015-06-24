// CollisionTestState.hpp

#ifndef COLLISIONTESTSTATE_HPP_INCLUDED
#define COLLISIONTESTSTATE_HPP_INCLUDED

#include "AbstractState.hpp"
#include "CollisionShapes.hpp"

namespace	spaceshooter
{
	class DrawManager;

	class CollisionTestState : public AbstractState
	{
	public:
		CollisionTestState();
		~CollisionTestState();

		virtual bool Enter();
		virtual void Exit();
		virtual bool Update(float deltatime);
		virtual void Draw();
		virtual std::string GetNextState();

	private:
		void OnAction(const std::string& action, bool state);

	private:
		DrawManager* m_draw_manager;

		enum
		{
			ACTION_LEFT,
			ACTION_RIGHT,
			ACTION_UP,
			ACTION_DOWN,
			ACTION_FIRE,
			ACTION_COUNT,
		};
		bool m_action[ACTION_COUNT];
		
		float m_screen_width;
		float m_screen_height;

		AxisAlignedBoundingBox m_aabb;
		sf::RectangleShape m_aabb_shape;

		BoundingCircle m_circle;
		sf::CircleShape m_circle_shape;

		ObjectOrientedBoundingBox m_obb;
		sf::VertexArray m_obb_shape;

		sf::VertexArray m_line_circle_aabb;
		sf::VertexArray m_line_circle_obb;
	};
} // namespace spaceshooter

#endif // COLLISIONTESTSTATE_HPP_INCLUDED
