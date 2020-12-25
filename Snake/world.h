#pragma once
#include <SFML/Graphics.hpp>

#include "snake.h"

class World{
public:
	World(sf::Vector2u wnd_size);
	~World();

	int GetBlockSize() const;

	void RespawnApple();

	void Update(Snake& player);
	void Render(sf::RenderWindow& window);

private:
	sf::Vector2u m_wndSize;
	sf::Vector2i m_appleCoord;
	int m_blockSize;
	int m_pic_size;
	//sf::CircleShape m_appleShape;
	sf::Texture m_appleTexture;
	sf::Sprite m_appleSprite;
	sf::RectangleShape m_bounds[4];
	sf::Texture m_grassTexture;
	sf::Sprite m_grassSprite;
	sf::Texture m_treeTexture;
	sf::Sprite m_treeSprite;
};