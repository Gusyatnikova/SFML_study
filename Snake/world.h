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

	sf::CircleShape m_appleShape;
	sf::RectangleShape m_bounds[4];
};