#include "stdafx.h"
#include <iostream>
#include "ServiceLocator.hpp"
#include "TextureManager.hpp"
#include "InputManager.hpp"
#include "AudioManager.hpp"
#include "DrawManager.hpp"
#include "OVArea.hpp"
#include "OverWorldState.hpp"
#include "ScreenEffects.hpp"
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

		std::ifstream inputSteam("../assets/map_files/OverWorld/" + p_filename);
		if (!inputSteam.is_open())
		{
			std::cout << "Failed to parse map: Could not open file '" << p_filename << "'" << std::endl;
		}
		//m_screenEffect = new ScreenEffects(m_renderWindow, ("SetNight"), INFINITY, m_drawManager);
		//AllScreenEffects.push_back(*m_screenEffect);
		std::string stringLine;
		std::vector<std::string> parts;
		Layer*currentLayer = nullptr;
		int currentRow = 0;
		while (std::getline(inputSteam, stringLine))
		{
			parts = explodeArea(stringLine, " ");
			if (parts[0] == "name")
			{
				m_areaName = parts[1];
			}
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
				//m_player->SetPosition(m_tileSize / 2, m_tileSize / 2);
				//m_player->SetTargetPos(sf::Vector2f(m_tileSize/2, m_tileSize/2));
				m_view.setCenter(m_player->GetPosition());
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
					Passable passable = PASSABLE_NOTDEFINED;
					int ID = parts[i + 1].c_str()[0]; //nu kan vi hitta rätt tiledefinition för varje tile
					if (ID == '0')
						continue;
					
					TileDefinition* td = getTileDefinition(ID);

					if (td == nullptr)
					{
						std::cout << "Failed to parse map: Unable to find tile definition for ID '" << ID << "'" << std::endl;
					}

					Tile* tile = new Tile();
					tile->isCollider = false;
					if (ID == 'x')
					{
						tile->isCollider = true;
						passable = PASSABLE_NOT;
					}
					tile->passable = passable;
					tile->ID = ID;
					tile->layersName = currentLayer->name;
					tile->tileNumber =(i*currentRow);
					tile->vertices = &currentLayer->vertices[(i + currentRow * m_width) * 4];
					tile->centerPos = sf::Vector2f((((i + 1)* (m_tileSize)) / 2) + i * (m_tileSize/2), (((currentRow + 1)*(m_tileSize)) / 2) + currentRow * (m_tileSize/2));
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
		m_AllTiles.clear();
		AllScreenEffects.clear();
	}
	void OVArea::HandleDoorEvent(char p_tileID)
	{
		if (m_areaName=="OverWorld1_1")
		{
			if (p_tileID == '!')
			{
				m_overWorld->ChangeArea("OverWorldCastle");
			}
		}
		if (m_areaName == "OverWorldCastle")
		{
			if (p_tileID == '!')
			{
				m_overWorld->ChangeArea("OverWorld1_1");
			}
		}
	}
	void OVArea::HandleEncounters(std::string m_areaName)
	{
		int rnd= Random(0, 12);
		if (rnd == 0)
		{
			int rndEnemy = Random(0, 6);
			if (m_areaName == "OverWorld1_1")
			{
				switch (rndEnemy)
				{
				case 0:m_overWorld->SetExitState("LowKeyKnight");
					break;
				case 1:m_overWorld->SetExitState("LowKeyKnight");
					break;
				case 2:m_overWorld->SetExitState("LowKeyKnight");
					break;
				case 3:m_overWorld->SetExitState("Gnoll");
					break;
				case 4:m_overWorld->SetExitState("Gnoll");
					break;
				case 5:m_overWorld->SetExitState("Minotaur");
					break;
				case 6:m_overWorld->SetExitState("Minotaur");
					break;
				}
				
			}
			else if (m_areaName == "OverWorldCastle")
			{
				std::cout << "No enemies in this area";
			}
		}
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
				if (m_mousePosition.x >= point1.x && m_mousePosition.x <= point3.x)//check if the mouse is inside a square 
				{
					if (m_mousePosition.y >= point1.y && m_mousePosition.y <= point3.y)
					{
						if (m_AllTiles[i].layersName == "collision_layer")  //check the collision layer 
						{
							if (!m_AllTiles[i].passable == PASSABLE_NOT)   //if the tile is walkable
							{
								//check so player is standing still in the middle of a square and can only walk to adjacent ones.
								if (m_player->GetPosition().x - m_AllTiles[i].centerPos.x == m_tileSize || m_player->GetPosition().x - m_AllTiles[i].centerPos.x == -m_tileSize || m_player->GetPosition().x - m_AllTiles[i].centerPos.x == 0)
								{
								  if (m_player->GetPosition().y - m_AllTiles[i].centerPos.y == m_tileSize || m_player->GetPosition().y - m_AllTiles[i].centerPos.y == -m_tileSize || m_player->GetPosition().y - m_AllTiles[i].centerPos.y == 0)
									{
										std::cout << m_AllTiles[i].tileNumber<<std::endl;
										HandleDoorEvent(m_AllTiles[i].ID);
										HandleEncounters(m_areaName);
										std::cout << m_AllTiles[i].ID;
										std::cout << m_player->GetPosition().x - m_AllTiles[i].centerPos.x << std::endl;
										m_player->SetTargetPos(m_AllTiles[i].centerPos);
									}
								}
							}
						}
					}
				}
			}
		}
	
	
		UpdateCamera(deltatime);
		for (unsigned int i = 0; i < AllScreenEffects.size(); i++)
		{
			AllScreenEffects[i].Update(deltatime);
		}
		
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
			if (m_layers[i]->name != "collision_layer")
			{
				states.texture = &m_texture;
				target.draw(m_layers[i]->vertices, states);
			}
		}
		for (unsigned int i = 0; i < AllScreenEffects.size(); i++)
		{
			m_drawManager->Draw(AllScreenEffects[i]);
		}
	}
}