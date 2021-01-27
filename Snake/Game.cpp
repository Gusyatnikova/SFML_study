#include "Game.h"

Game::Game() : m_window("Snake", sf::Vector2u(800, 600)),
	m_stateManager(&m_context) {
	m_clock.restart();
	srand(time(NULL));
	//m_elapsed = 0.0f;
	m_context.m_wnd = &m_window;
	m_context.m_eventManager = m_window.GetEventManager();
	m_stateManager.SwitchTo(StateType::MainMenu);
}

Game::~Game() {}

void Game::Update() {
	m_window.Update();
	m_stateManager.Update(m_elapsed);
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

bool Game::IsDone() const { return (m_window.IsDone()) || m_stateManager.HasState(StateType::GameOver); }

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

