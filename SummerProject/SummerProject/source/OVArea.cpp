#include "stdafx.h"
#include <iostream>
#include "ServiceLocator.hpp"
#include "TextureManager.hpp"
#include "InputManager.hpp"
#include "AudioManager.hpp"
#include "DrawManager.hpp"
#include "OVArea.hpp"
#include "ServiceLocator.hpp"
#include "OverWorldState.hpp"
#include "OVPlayer.hpp"
#include <math.h>
namespace spaceshooter
{ 
	std::vector<std::string> explodeArea(const std::string& string, const std::string& delimeter)
	{
		std::vector<std::string> parts;
		std::size_t oldPos = 0;
		while (true)
		{
			std::size_t newPos = string.find(delimeter, oldPos);
			if (newPos == std::string::npos)
			{
				parts.push_back(string.substr(oldPos, newPos - oldPos));
				break;
			}
			parts.push_back(string.substr(oldPos, newPos - oldPos));
			oldPos = newPos + 1;
		}
		return parts;
	}
	OVArea::TileDefinition* OVArea::getTileDefinition(char ID) const
	{
		for (std::size_t i = 0; i < m_tileDefinitions.size(); ++i)
		{
			if (m_tileDefinitions[i]->ID == ID)
			{
				return m_tileDefinitions[i];
			}
		}
		return nullptr;
	}
	OVArea::OVArea(std::string p_filename, OverWorldState *p_overworld, OVPlayer *p_player)
	{
		m_player = p_player;
		m_overWorld = p_overworld;
		m_inputManager = ServiceLocator<InputManager>::GetService();
		m_mouse = m_inputManager->GetMouse();
		m_drawManager = ServiceLocator<DrawManager>::GetService();
		m_renderWindow = m_drawManager->getWindow();
	//init view
		m_screenWidth = 1024;
		m_screenHeight = 600;
		m_view.setSize(m_screenWidth, m_screenHeight);
		
		std::ifstream inputSteam("../assets/map_files/OverWorld/"+p_filename);
		if (!inputSteam.is_open())
		{
			std::cout << "Failed to parse map: Could not open file '" << p_filename << "'" << std::endl;
		}

		std::string stringLine;
		std::vector<std::string> parts;
		Layer*currentLayer = nullptr;
		int currentRow = 0;
		while (std::getline(inputSteam, stringLine))
		{
			parts = explodeArea(stringLine, " ");

			if (parts[0] == "width")
			{
				m_width = std::stoi(parts[1]);
			}
			else if (parts[0] == "height")
			{
				m_height = std::stoi(parts[1]);
			}
			else if (parts[0] == "ts")
			{
				m_tileSize = std::stof(parts[1]); // samma sak men till float
			}
			else if (parts[0] == "texture")
			{
				m_texture.loadFromFile(parts[1]); // samma sak men till float
			}
			else if (parts[0] == "td")
			{
				TileDefinition* td = new TileDefinition();
				td->ID = parts[1].c_str()[0];
				td->u = std::stof(parts[2]);
				td->v = std::stof(parts[3]);

				m_tileDefinitions.push_back(td);
			}
			else if (parts[0] == "l")
			{
				Layer* layer = new Layer();
				layer->name = parts[1];
				layer->vertices.resize(m_width * m_height * 4); // m_width * m_height bestämmer hur många tiles det ska kunna finnas i varje lager. Och * 4 betyder att varje tile har 4 vertices
				layer->vertices.setPrimitiveType(sf::Quads); // Det betyder att vi vill ruta ut vertriserna som fyrkanter, det finns även sf::Points som ritar ut punk för punkt och sf::Triangle
				currentLayer = layer;
				currentRow = 0;
				m_layers.push_back(layer);
			}
			else if (parts[0] == "d") // data
			{
				for (int i = 0; i < parts.size() - 1; ++i)
				{
					Passable passable=PASSABLE_NOTDEFINED;
					int ID = parts[i + 1].c_str()[0]; //nu kan vi hitta rätt tiledefinition för varje tile
					if (ID == '0')
						continue;
					if (ID == 'x')
					{
						passable = PASSABLE_NOT;
					}
					TileDefinition* td = getTileDefinition(ID);
					
					if (td == nullptr)
					{
						std::cout << "Failed to parse map: Unable to find tile definition for ID '" << ID << "'" << std::endl;
					}

					Tile* tile = new Tile();
					tile->passable = passable;
					tile->ID = ID;
					tile->vertices = &currentLayer->vertices[(i + currentRow * m_width) * 4];
					tile->centerPos = sf::Vector2f(((i + 1)* m_tileSize)/2, ((currentRow + 1)*m_tileSize)/2);
					tile->vertices[0].position = sf::Vector2f(i * m_tileSize, currentRow * m_tileSize);
					tile->vertices[1].position = sf::Vector2f((i + 1) * m_tileSize, currentRow * m_tileSize);
					tile->vertices[2].position = sf::Vector2f((i + 1) * m_tileSize, (currentRow + 1) * m_tileSize);
					tile->vertices[3].position = sf::Vector2f(i * m_tileSize, (currentRow + 1) * m_tileSize);

					tile->vertices[0].texCoords = sf::Vector2f(td->u, td->v);
					tile->vertices[1].texCoords = sf::Vector2f(td->u + m_tileSize, td->v);
					tile->vertices[2].texCoords = sf::Vector2f(td->u + m_tileSize, td->v + m_tileSize);
					tile->vertices[3].texCoords = sf::Vector2f(td->u, td->v + m_tileSize);
					m_AllTiles.push_back(*tile);
				}
				++currentRow;
			}
		}
	}
	OVArea::~OVArea()
	{

	}

	void OVArea::Update(float deltatime)
	{
		m_renderWindow->setView(m_view);
		m_mousePosition = m_drawManager->getWindow()->mapPixelToCoords(m_mouse.getPosition(*m_drawManager->getWindow()));
		if (m_mouse.isButtonPressed(m_mouse.Left))
		{
			for (unsigned int i = 0; i < m_AllTiles.size(); i++)
			{
				sf::Vector2f point1 = m_AllTiles[i].vertices[0].position;
				sf::Vector2f point3 = m_AllTiles[i].vertices[2].position;
				if (m_mousePosition.x >= point1.x && m_mousePosition.x <= point3.x)
				{
					if (m_mousePosition.y >= point1.y && m_mousePosition.y <= point3.y)
					{
						//std::cout << m_AllTiles[i].ID << std::endl;
						//std::cout << m_AllTiles[i].passable << std::endl;
						std::cout << m_AllTiles[i].centerPos.x << std::endl;
						std::cout << m_AllTiles[i].centerPos.y << std::endl;
					}
				}
			}
		}
		UpdateCamera(deltatime);
		
		
	/*	m_mousePositionGrid = sf::Vector2f(m_mousePosition.x /m_tileSize, m_mousePosition.y / m_tileSize);
		sf::Vector2f m_mousePositionGrounded = sf::Vector2f(floor(m_mousePositionGrid.x), floor(m_mousePositionGrid.y));
		std::cout << m_mousePositionGrounded.x;
		std::cout << m_mousePositionGrounded.y;*/
	}
	void OVArea::UpdateCamera(float deltatime)
	{
		if (m_view.getCenter().x+(m_screenWidth/2.5) < m_mousePosition.x)
		{
			m_view.move(sf::Vector2f(5.0f, 0.f));
		}
		else if (m_view.getCenter().x-(m_screenWidth/2.5) > m_mousePosition.x)
		{
			m_view.move(sf::Vector2f(-5.0f, 0.f));
		}

		if (m_view.getCenter().y+(m_screenHeight/2.5) < m_mousePosition.y)
		{
			m_view.move(sf::Vector2f(0.0f, 5.f));
		}
		else if (m_view.getCenter().y-m_screenHeight/2.5 > m_mousePosition.y)
		{
			m_view.move(sf::Vector2f(0.0f, -5.f));
		}
	}
	void OVArea::draw(sf::RenderTarget &target, sf::RenderStates states) const
	{
		for (int i = 0; i < m_layers.size(); ++i)
		{
			states.texture = &m_texture;
			target.draw(m_layers[i]->vertices, states);
		}
	}
}