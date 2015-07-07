//OVArea.hpp

#ifndef OVArea_HPP_INCLUDED
#define OVArea_HPP_INCLUDED


namespace spaceshooter
{
	//roguelike tilebased mousemovement, event nodes etc.
	
	class OVArea: public sf::Drawable
	{
	public:
		struct Tile
		{
			char ID;
			sf::Vertex* vertices;
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

		OVArea(std::string p_filename);
		~OVArea();
		void Update(float deltatime);
		void UpdateCamera(float deltatime);
		void draw(sf::RenderTarget &target, sf::RenderStates states) const;
		TileDefinition* getTileDefinition(char ID) const;
	private:
		float m_screenWidth;
		float m_screenHeight;
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
	};
}
// namespace spaceshooter

#endif // OVArea_HPP_INCLUDED