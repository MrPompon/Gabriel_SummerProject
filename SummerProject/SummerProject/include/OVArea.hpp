//OVArea.hpp

#ifndef OVArea_HPP_INCLUDED
#define OVArea_HPP_INCLUDED


namespace spaceshooter
{
	//roguelike tilebased mousemovement, event nodes etc.
	class OverWorldState;
	class OVPlayer;
	class ScreenEffects;
	class PlayerStatusManager;

	class OVArea: public sf::Drawable
	{
	public:
		enum Passable
		{
			PASSABLE_NOTDEFINED,
			PASSABLE_NOT,
			PASSABLE_PASSABLE,

		};
		struct Tile
		{
			int tileNumber;
			std::string layersName;
			char ID;
			sf::Vertex* vertices;
			bool isCollider;
			sf::Vector2f centerPos;
			Passable passable;
		};

		struct TileDefinition
		{
			char ID;
			float u;
			float v;
		};

		struct Layer
		{
			std::string name;
			sf::VertexArray vertices;
		};

		OVArea(std::string p_filename, OverWorldState *p_overworld, OVPlayer *p_player);
		~OVArea();
		void Update(float deltatime);
		void UpdateCamera(float deltatime);
		void draw(sf::RenderTarget &target, sf::RenderStates states) const;
		TileDefinition* getTileDefinition(char ID) const;
		OverWorldState* m_overWorld;
		void HandleDoorEvent(char p_tileID);
		void HandleEncounters(std::string m_areaName);
	private:
		PlayerStatusManager*m_player_status_manager;
		ScreenEffects* m_screenEffect;
		std::vector<ScreenEffects> AllScreenEffects;
	
		float m_screenWidth;
		float m_screenHeight;
		OVPlayer* m_player;
		InputManager* m_inputManager;
		DrawManager* m_drawManager;
		sf::Vector2f m_mousePosition;
		sf::Vector2f m_mousePositionGrid;
		sf::Texture m_texture;
		std::vector<Layer*> m_layers;
		std::vector<TileDefinition*> m_tileDefinitions;
		std::vector<Tile> m_AllTiles;
		sf::RenderWindow *m_renderWindow;
		sf::View m_view;
		sf::Mouse m_mouse;
		int m_width;
		int m_height;
		float m_tileSize;
		std::string m_areaName;
	};
}
// namespace spaceshooter

#endif // OVArea_HPP_INCLUDED