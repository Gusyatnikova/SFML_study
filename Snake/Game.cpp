#include "Game.h"

Game::Game() : m_window("Snake", sf::Vector2u(1000, 750)),
m_snake(m_world.GetBlockSize()), m_world(m_window.GetWindowSize()) 
{
	m_clock.restart();
	srand(time(NULL));
	m_elapsed = 0.0f;
	m_textBox.Setup(5, 22, 400, 
		{ m_window.GetWindowSize().x - 400.0f, 0.0f }, "../Source/QuirkyRobot.ttf");
}

Game::~Game() {}

void Game::HandleInput() {
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) &&
		m_snake.GetPhisicalDirection() != Direction::DOWN) {
		m_snake.SetDirection(Direction::UP);
	} else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down) &&
		m_snake.GetPhisicalDirection() != Direction::UP) {
		m_snake.SetDirection(Direction::DOWN);
	} if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) &&
		m_snake.GetPhisicalDirection() != Direction::RIGHT) {
		m_snake.SetDirection(Direction::LEFT);
	} if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) &&
		m_snake.GetPhisicalDirection() != Direction::LEFT) {
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
			m_textBox.Add("You Lose! Score: " + std::to_string(m_snake.GetScore()));
		}
		if (m_world.AppleEaten()) {
			m_textBox.Add("You ate an apple. Score: " + std::to_string(m_snake.GetScore()));
		}
	}
}

void Game::Render() {
	m_window.BeginDraw();
	m_world.Render(*m_window.GetRenderWindow());
	m_snake.Render(*m_window.GetRenderWindow());
	m_textBox.Render(*m_window.GetRenderWindow());
	m_window.EndDraw();
}

Window* Game::GetWindow() {
	return &m_window;
}

sf::Time Game::GetElapsed() { return m_clock.getElapsedTime(); }
void Game::RestartClock() { m_elapsed += m_clock.restart().asSeconds(); }