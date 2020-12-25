#include "world.h"

World::World(sf::Vector2u wnd_size) {
	//m_blockSize = 16;
	m_blockSize = 31;
	m_pic_size = 30;
	m_wndSize = wnd_size;
	RespawnApple();
	//m_appleShape.setFillColor(sf::Color::Red);
	//m_appleShape.setRadius(m_blockSize / 2);
	//todo: check return value from loadFromFile
	m_appleTexture.loadFromFile("../Source/rsz_food_on_grass.png");
	m_appleSprite.setTexture(m_appleTexture);
	m_grassTexture.loadFromFile("../Source/grass.png");
	m_grassSprite.setTexture(m_grassTexture);
	m_grassSprite.setPosition({ 0, 0 });
	m_treeTexture.loadFromFile("../Source/rsz_tree.png");
	m_treeSprite.setTexture(m_treeTexture);
	//m_appleSprite.setScale({ m_blockSize / 15.0f, m_blockSize / 15.0f });
	/*for (int i = 0; i < 4; ++i) {
		m_bounds[i].setFillColor(sf::Color(150, 0, 0));
		if (!((i + 1) % 2)) {
			m_bounds[i].setSize(sf::Vector2f(m_wndSize.x, m_blockSize));
		} else {
			m_bounds[i].setSize(sf::Vector2f(m_blockSize, m_wndSize.y));
		}
		if (i < 2) {
			m_bounds[i].setPosition(0, 0);
		}
		else {
			m_bounds[i].setOrigin(m_bounds[i].getSize());
			m_bounds[i].setPosition(sf::Vector2f(m_wndSize));
		}
	}*/
}

World::~World() {}

void World::RespawnApple() {
	int maxX = (m_wndSize.x / m_blockSize) - 2;
	int maxY = (m_wndSize.y / m_blockSize) - 2;
	m_appleCoord = sf::Vector2i(
		rand() % maxX + 1, rand() % maxY + 1);
	//m_appleShape.setPosition(
		//m_appleCoord.x * m_blockSize, m_appleCoord.y * m_blockSize);
	m_appleSprite.setPosition(m_appleCoord.x * m_blockSize, m_appleCoord.y * m_blockSize);
}

void World::Update(Snake& player) {
	if (player.GetPosition() == m_appleCoord) {
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
	//window.draw(m_appleShape);
	window.draw(m_grassSprite);
	window.draw(m_appleSprite);
	
	//for (auto& bound : m_bounds) {
	//	window.draw(bound);
	//}

	for (float i = 0; i < m_wndSize.x - m_pic_size; i += m_pic_size) {
		m_treeSprite.setPosition({ i, 0 });
		window.draw(m_treeSprite);
		m_treeSprite.setPosition({ i, 1.0f * m_wndSize.y - 30 });
		window.draw(m_treeSprite);
	}
	for (float i = 0; i < m_wndSize.y - m_pic_size; i += m_pic_size) {
		m_treeSprite.setPosition({ 0, i });
		window.draw(m_treeSprite);
		m_treeSprite.setPosition({ 1.0f * m_wndSize.x - 30, i });
		window.draw(m_treeSprite);
	}
}

int World::GetBlockSize() const { return m_blockSize; }



