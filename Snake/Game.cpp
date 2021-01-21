#include "Game.h"

Game::Game() : m_window("Snake", sf::Vector2u(800, 600)),
m_snake(m_world.GetBlockSize()), m_world(m_window.GetWindowSize()),
	m_stateManager(&m_context) {
	m_clock.restart();
	srand(time(NULL));
	//m_elapsed = 0.0f;
	m_textBox.Setup(1, 22, 400, 
		{ m_window.GetWindowSize().x - 400.0f, 0.0f }, "../Source/QuirkyRobot.ttf");
	m_isDone = false;
	
	m_context.m_wnd = &m_window;
	m_context.m_eventManager = m_window.GetEventManager();
	m_stateManager.SwitchTo(StateType::MainMenu);
}

Game::~Game() {}

//void Game::HandleInput() {
	/*if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) &&
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
	}*/
//}

void Game::Update() {
	m_window.Update();
	m_stateManager.Update(m_elapsed);
	/*float timeStep = 1.0f / m_snake.GetSpeed();
	if (m_elapsed >= timeStep) {
		m_snake.Tick();
		m_world.Update(m_snake);
		m_elapsed -= timeStep;
		if (m_snake.HasLost()) {
			if (m_snake.GetLives() > 0) {
				m_snake.Reset();
			}
			else {
				m_isDone = true;
				m_textBox.Clear();
			}
		}	
	}
	*/
	/*m_textBox.Setup(1, 22, 400,
		{ m_window.GetWindowSize().x - 200.0f, m_world.GetBlockSize() * 0.9f }, "../Source/QuirkyRobot.ttf");
	m_textBox.Add(
		"Score: " + std::to_string(m_snake.GetScore()) +
		"     Lives: " + std::to_string(m_snake.GetLives()));*/
}

void Game::Render() {
	m_window.BeginDraw();
	//m_world.Render(*m_window.GetRenderWindow());
	//m_snake.Render(*m_window.GetRenderWindow());
	//m_textBox.Render(*m_window.GetRenderWindow());
	m_stateManager.Draw();
	m_window.EndDraw();
}

//void Game::ShowGameOver() {
	/*m_textBox.Setup(1, 40, 400,
		{ m_window.GetWindowSize().x / 2 - 200.0f , m_window.GetWindowSize().y / 2.0f - 20.0f},
		"../Source/QuirkyRobot.ttf");
	m_textBox.Add("       GAME OVER");
	m_window.BeginDraw();
	m_world.Render(*m_window.GetRenderWindow());
	m_textBox.Render(*m_window.GetRenderWindow());
	m_window.EndDraw();*/
//}

bool Game::IsDone() const { return (m_isDone || m_window.IsDone()); }

Window* Game::GetWindow() {
	return &m_window;
}

sf::Time Game::GetElapsed() { return m_clock.getElapsedTime(); }

void Game::RestartClock() { 
	//m_elapsed += m_clock.restart().asSeconds(); 
	m_elapsed = m_clock.restart();
}

void Game::LateUpdate() { 
	m_stateManager.ProcessRequests(); 
	RestartClock();
}

