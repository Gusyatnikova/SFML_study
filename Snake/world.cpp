#include "world.h"
#include <vector>

World::World(sf::Vector2u wnd_size) {
	m_blockSize = 25;
	m_pic_size = 25;
	m_appleEaten = false;
	m_wndSize = wnd_size;
	RespawnApple();
	m_appleTexture.loadFromFile("../Source/rsz_food_on_grass.png");
	m_appleSprite.setTexture(m_appleTexture);
	m_grassTexture.loadFromFile("../Source/grass.png");
	m_grassSprite.setTexture(m_grassTexture);
	m_grassSprite.setPosition({ 0, 0 });
	m_treeTexture.loadFromFile("../Source/rsz_tree.png");
	m_treeSprite.setTexture(m_treeTexture);
}

World::~World() {}

void World::RespawnApple() {
	int maxX = (m_wndSize.x / m_blockSize) - 1;
	int maxY = (m_wndSize.y / m_blockSize) - 1;
	m_appleCoord = sf::Vector2i(
		rand() % maxX, rand() % maxY);
	while (m_appleCoord.x == 0 || m_appleCoord.y == 0) {
		m_appleCoord = sf::Vector2i(
			rand() % maxX, rand() % maxY);
	}
	m_appleSprite.setPosition(m_appleCoord.x * m_blockSize, m_appleCoord.y * m_blockSize);
}

void World::Update(Snake& player) {
	m_appleEaten = false;
	if (player.GetPosition() == m_appleCoord) {
		m_appleEaten = true;
		player.Extend();
		player.IncreaseScore();
		RespawnApple();
	}
	int gridSize_x = m_wndSize.x / m_blockSize;
	int gridSize_y = m_wndSize.y / m_blockSize;
	if (player.GetPosition().x <= 0 ||
		player.GetPosition().y <= 0 ||
		player.GetPosition().x >= gridSize_x - 1 ||
		player.GetPosition().y >= gridSize_y - 1) {
		player.Lose();
	}
}

void World::Render(sf::RenderWindow& window) {
	window.draw(m_grassSprite);
	DrawBorders(window);
	DrawGrid(window);
	window.draw(m_appleSprite);
}

void World::DrawGrid(sf::RenderWindow& window) {
	std::vector<std::pair<sf::Vertex, sf::Vertex>> lines;
	sf::Color lineColor(38, 115, 38, 40);
	int i;
	for (i = 0; i <= window.getSize().x; i += m_blockSize) {
		lines.emplace_back(sf::Vertex({ i * 1.0f, 0.0f }, lineColor),
			sf::Vertex({ i * 1.0f, window.getSize().y * 1.0f }, lineColor));
	}
	for (int j = 0; j <= window.getSize().y; j += m_blockSize) {
		lines.emplace_back(sf::Vertex({ 0.0f, j * 1.0f }, lineColor), 
			sf::Vertex({ window.getSize().x * 1.0f, j * 1.0f }, lineColor));
	}
	for (int j = 0; j < lines.size(); ++j) {
		sf::Vertex line[2] = { lines[j].first, lines[j].second };
		window.draw(line, 2, sf::Lines);
	}
}

void World::DrawBorders(sf::RenderWindow& window) {
	for (float i = 0; i <= m_wndSize.x - m_pic_size; i += m_pic_size) {
		m_treeSprite.setOrigin({ 0.0f, 0.0f });
		m_treeSprite.setPosition({ i, 0 });
		window.draw(m_treeSprite);
		m_treeSprite.setOrigin(
			{ 0.0f, m_treeSprite.getLocalBounds().height });
		m_treeSprite.setPosition({ i, 1.0f * m_wndSize.y });
		window.draw(m_treeSprite);
	}
	for (float i = 0; i <= m_wndSize.y - m_pic_size; i += m_pic_size) {
		m_treeSprite.setOrigin({ 0.0f, 0.0f });
		m_treeSprite.setPosition({ 0, i });
		window.draw(m_treeSprite);
		m_treeSprite.setOrigin(
			{ m_treeSprite.getLocalBounds().width, 0.0f });
		m_treeSprite.setPosition({ 1.0f * m_wndSize.x, i });
		window.draw(m_treeSprite);
	}
}

int World::GetBlockSize() const { return m_blockSize; }

bool World::AppleEaten() const { return m_appleEaten; }

