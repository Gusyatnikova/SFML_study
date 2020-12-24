#include "Game.h"

Game::Game() : m_window("Snake", sf::Vector2u(800, 600)),
m_snake(m_world.GetBlockSize()), m_world(m_window.GetWindowSize()) 
{
	m_clock.restart();
	srand(time(NULL));
	m_elapsed = 0.0f;
}

Game::~Game() {}

void Game::HandleInput() {
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) &&
		m_snake.GetDirection() != Direction::DOWN) {
		m_snake.SetDirection(Direction::UP);
	} else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down) &&
		m_snake.GetDirection() != Direction::UP) {
		m_snake.SetDirection(Direction::DOWN);
	} if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) &&
		m_snake.GetDirection() != Direction::RIGHT) {
		m_snake.SetDirection(Direction::LEFT);
	} if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) &&
		m_snake.GetDirection() != Direction::LEFT) {
		m_snake.SetDirection(Direction::RIGHT);
	}
}

void Game::Update() {
	m_window.Update();
	float timeStep = 1.0f / m_snake.GetSpeed();
	if (m_elapsed >= timeStep) {
		m_snake.Tick();
		m_world.Update(m_snake);
		m_elapsed -= timeStep;
		if (m_snake.HasLost()) {
			m_snake.Reset();
		}
	}
}

void Game::Render() {
	m_window.BeginDraw();
	m_world.Render(*m_window.GetRenderWindow());
	m_snake.Render(*m_window.GetRenderWindow());
	m_window.EndDraw();
}

Window* Game::GetWindow() {
	return &m_window;
}

sf::Time Game::GetElapsed() { return m_clock.getElapsedTime(); }
void Game::RestartClock() { m_elapsed += m_clock.restart().asSeconds(); }