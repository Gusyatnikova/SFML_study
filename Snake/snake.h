#pragma once

#include <vector>

#include <SFML/Graphics.hpp>

enum class Direction {UP, DOWN, LEFT, RIGHT, NONE};

struct SnakeSegment {
	sf::Vector2i position;
	SnakeSegment(int x, int y) : position(x, y) {};
};

using SnakeContainer = std::vector<SnakeSegment>;

class Snake {
public:
	Snake(int blockSize);
	~Snake();

	void SetDirection(Direction dir);
	Direction GetDirection() const;
	Direction GetPhisicalDirection() const;
	int GetSpeed() const;
	sf::Vector2i GetPosition() const;
	int GetLives() const;
	int GetScore() const;
	void IncreaseScore();
	bool HasLost() const;
	bool HasSegment(sf::Vector2i pos) const;

	void Lose();
	void ToggleLost();

	void Extend();
	void Reset();

	void Move();
	void Tick();
	void Cut(int segments_cnt);
	void Render(sf::RenderWindow& window);

private:
	SnakeContainer m_snake_body;
	Direction m_dir;
	//sf::RectangleShape m_bodyRect;
	sf::CircleShape m_bodyCircle;
	int m_size;
	int m_speed;
	int m_lives;
	int m_score;
	bool m_lost;
	void CheckCollsion();
};