// CollisionTestState.cpp

#include "stdafx.h"
#include "DrawManager.hpp"
#include "InputManager.hpp"
#include "ServiceLocator.hpp"
#include "CollisionTestState.hpp"

namespace spaceshooter
{
	CollisionTestState::CollisionTestState()
	{
		m_screen_width = 1024.0f;
		m_screen_height = 600.0f;

		m_draw_manager = nullptr;
		for (unsigned int index = 0; index < ACTION_COUNT; index++)
		{
			m_action[index] = false;
		}
	}

	CollisionTestState::~CollisionTestState()
	{
	}

	bool CollisionTestState::Enter()
	{
		printf("WASD to move circle.\n");
		printf("The line between the circle and box is the closest distance.\n");
		printf("If the circle overlaps the box, the line becomes red.\n");

		// note(tommi): register for actions
		InputManager* input_manager = ServiceLocator<InputManager>::GetService();
		input_manager->RegisterKeyActionListener(Action::LEFT, this, &CollisionTestState::OnAction);
		input_manager->RegisterKeyActionListener(Action::RIGHT, this, &CollisionTestState::OnAction);
		input_manager->RegisterKeyActionListener(Action::UP, this, &CollisionTestState::OnAction);
		input_manager->RegisterKeyActionListener(Action::DOWN, this, &CollisionTestState::OnAction);
		input_manager->RegisterKeyActionListener(Action::FIRE, this, &CollisionTestState::OnAction);

		// note(tommi): get draw manager
		m_draw_manager = ServiceLocator<DrawManager>::GetService();

		m_aabb.SetCenter(sf::Vector2f(200.0f, 200.0f));
		m_aabb.SetExtent(sf::Vector2f(100.0f, 50.0f));
		m_aabb_shape.setSize(m_aabb.GetExtent() * 2.0f);
		m_aabb_shape.setOrigin(m_aabb.GetExtent());
		m_aabb_shape.setPosition(m_aabb.GetCenter());
		m_aabb_shape.setFillColor(sf::Color::Transparent);
		m_aabb_shape.setOutlineThickness(1.0f);
		m_aabb_shape.setOutlineColor(sf::Color::Green);

		m_circle.SetCenter(sf::Vector2f(m_screen_width * 0.5f, m_screen_height * 0.25f));
		m_circle.SetRadius(40.0f);
		m_circle_shape.setRadius(m_circle.GetRadius());
		m_circle_shape.setOrigin(m_circle.GetRadius(), m_circle.GetRadius());
		m_circle_shape.setPosition(m_circle.GetCenter());
		m_circle_shape.setFillColor(sf::Color::Transparent);
		m_circle_shape.setOutlineThickness(1.0f);
		m_circle_shape.setOutlineColor(sf::Color::Cyan);

		m_obb.SetCenter(sf::Vector2f(600.0f, 200.0f));
		m_obb.SetExtent(sf::Vector2f(60.0f, 20.0f));
		m_obb.SetRadians(ToRadians(15.0f));
		m_obb_shape.setPrimitiveType(sf::LinesStrip);
		m_obb_shape.resize(5);

		m_line_circle_aabb.setPrimitiveType(sf::Lines);
		m_line_circle_aabb.resize(2);

		m_line_circle_obb.setPrimitiveType(sf::Lines);
		m_line_circle_obb.resize(2);

		return true;
	}

	void CollisionTestState::Exit()
	{
		InputManager* input_manager = ServiceLocator<InputManager>::GetService();
		input_manager->UnregisterKeyActionListener(Action::LEFT, this);
		input_manager->UnregisterKeyActionListener(Action::RIGHT, this);
		input_manager->UnregisterKeyActionListener(Action::UP, this);
		input_manager->UnregisterKeyActionListener(Action::DOWN, this);
		input_manager->UnregisterKeyActionListener(Action::FIRE, this);
	}

	bool CollisionTestState::Update(float deltatime)
	{
		sf::Vector2f direction;
		if (m_action[ACTION_LEFT])
			direction.x = -1.0f;
		if (m_action[ACTION_RIGHT])
			direction.x = 1.0f;
		if (m_action[ACTION_UP])
			direction.y = -1.0f;
		if (m_action[ACTION_DOWN])
			direction.y = 1.0f;

		Normalize(direction);
		float length = Length(direction);
		if (length > 0.0f)
		{
			sf::Vector2f center = m_circle.GetCenter();
			center += direction * deltatime * 200.0f;
			m_circle.SetCenter(center);
			m_circle_shape.setPosition(m_circle.GetCenter());
		}

		// note(tommi): closest point on box to circle
		float boxMinX = m_aabb.GetCenter().x - m_aabb.GetExtent().x;
		float boxMaxX = m_aabb.GetCenter().x + m_aabb.GetExtent().x;
		float boxMinY = m_aabb.GetCenter().y - m_aabb.GetExtent().y;
		float boxMaxY = m_aabb.GetCenter().y + m_aabb.GetExtent().y;

		float boxX = Clamp(m_circle.GetCenter().x, boxMinX, boxMaxX);
		float boxY = Clamp(m_circle.GetCenter().y, boxMinY, boxMaxY);

		sf::Vector2f boxClosestPoint(boxX, boxY);
		sf::Vector2f boxCenterToCircleCenter = boxClosestPoint - m_circle.GetCenter();
		float distance = Length(boxCenterToCircleCenter);

		// note(tommi): this is the line between the closest point 
		// on the box and the center of the circle
		sf::Color lineColor = sf::Color::Yellow;
		if (distance <= m_circle.GetRadius())
			lineColor = sf::Color::Red;

		m_line_circle_aabb[0].position = sf::Vector2f(boxX, boxY);
		m_line_circle_aabb[0].color = lineColor;
		m_line_circle_aabb[1].position = m_circle.GetCenter();
		m_line_circle_aabb[1].color = lineColor;

		// note(tommi): obb debug visual construction
		for (unsigned int i = 0; i < 5; i++)
		{
			m_obb_shape[i].position = m_obb.GetCorner(i % 4);
			m_obb_shape[i].color = sf::Color::Green;
		}

		// note(tommi): we wan't to construct a line just like with the circle and aabb
		// but instead with the circle and obb
		distance = Length(m_circle.GetCenter() - m_obb.GetCenter());

		// note(tommi): the actual line between the closest point on the obb and circle
		lineColor = sf::Color::White;
		if (distance <= m_circle.GetRadius())
			lineColor = sf::Color::Blue;

		m_line_circle_obb[0].position = m_obb.GetCenter();
		m_line_circle_obb[0].color = lineColor;
		m_line_circle_obb[1].position = m_circle.GetCenter();
		m_line_circle_obb[1].color = lineColor;

		return true;
	}

	void CollisionTestState::Draw()
	{
		m_draw_manager->Draw(m_aabb_shape, sf::RenderStates::Default);
		m_draw_manager->Draw(m_circle_shape, sf::RenderStates::Default);
		m_draw_manager->Draw(m_obb_shape, sf::RenderStates::Default);
		m_draw_manager->Draw(m_line_circle_aabb, sf::RenderStates::Default);
		m_draw_manager->Draw(m_line_circle_obb, sf::RenderStates::Default);
	}

	std::string CollisionTestState::GetNextState()
	{
		return std::string("");
	}

	// private
	void CollisionTestState::OnAction(const std::string& action, bool state)
	{
		if (Action::LEFT == action)
		{
			m_action[ACTION_LEFT] = state;
		}
		else if (Action::RIGHT == action)
		{
			m_action[ACTION_RIGHT] = state;
		}
		else if (Action::UP == action)
		{
			m_action[ACTION_UP] = state;
		}
		else if (Action::DOWN == action)
		{
			m_action[ACTION_DOWN] = state;
		}
		else if (Action::FIRE == action)
		{
			m_action[ACTION_FIRE] = state;
		}
	}
} // namespace spaceshooter
