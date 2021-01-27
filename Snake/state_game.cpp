#include "state_game.h"
#include "state_manager.h"

State_Game::State_Game(StateManager *stateManager)
	: BaseState(stateManager),
	m_window(stateManager->GetContext()->m_wnd),
	m_world(m_window->GetWindowSize()),
	m_snake(m_world.GetBlockSize())
{
	m_textBox.Setup(1, 22, 400,
		{ m_window->GetWindowSize().x - 400.0f, 0.0f }, "../Source/QuirkyRobot.ttf");
	m_isDone = false;
	m_elapsed = 0.0f;
}

State_Game::~State_Game() {}

void State_Game::OnCreate() {
	EventManager* eventManager = m_stateManager->GetContext()->m_eventManager;
	eventManager->AddCallback(
		StateType::Game, "Key_Escape", &State_Game::MainMenu, this);
	eventManager->AddCallback(
		StateType::Game, "Key_P", &State_Game::Pause, this);
	eventManager->AddCallback(
		StateType::Game, "Key_L", &State_Game::ProcessInput, this);
	eventManager->AddCallback(
		StateType::Game, "Key_R", &State_Game::ProcessInput, this);
	eventManager->AddCallback(
		StateType::Game, "Key_U", &State_Game::ProcessInput, this);
	eventManager->AddCallback(
		StateType::Game, "Key_D", &State_Game::ProcessInput, this);
}

void State_Game::OnDestroy() {
	EventManager *eventManager = m_stateManager->GetContext()->m_eventManager;
	eventManager->RemoveCallback(StateType::Game, "Key_Escape");
	eventManager->RemoveCallback(StateType::Game, "Key_P");
	eventManager->RemoveCallback(StateType::Game, "Key_L");
	eventManager->RemoveCallback(StateType::Game, "Key_R");
	eventManager->RemoveCallback(StateType::Game, "Key_U");
	eventManager->RemoveCallback(StateType::Game, "Key_D");
}

void State_Game::Update(const sf::Time &time) {
	float timeStep = 1.0f / m_snake.GetSpeed();
	m_elapsed += time.asSeconds();
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
	if (m_snake.GetLives() <= 0) {
		m_stateManager->SwitchTo(StateType::GameOver);
	}
	m_textBox.Setup(1, 22, 400,
		{ m_window->GetWindowSize().x - 200.0f, m_world.GetBlockSize() * 0.9f }, "../Source/QuirkyRobot.ttf");
	m_textBox.Add(
		"Score: " + std::to_string(m_snake.GetScore()) +
		"     Lives: " + std::to_string(m_snake.GetLives()));
}

void State_Game::Draw() {
	m_world.Render(*m_window->GetRenderWindow());
	m_snake.Render(*m_window->GetRenderWindow());
	m_textBox.Render(*m_window->GetRenderWindow());
}

void State_Game::MainMenu(EventDetails *details) {
	//don't remove state game to have an opportunity 
	//resume the game without losing a progress
	m_stateManager->SwitchTo(StateType::MainMenu);
}

void State_Game::Pause(EventDetails *details) {
	m_stateManager->SwitchTo(StateType::Paused);
}

void State_Game::ProcessInput(EventDetails* details) {
	if (details->m_keyCode == 71 &&
		m_snake.GetPhisicalDirection() != Direction::RIGHT) {
		m_snake.SetDirection(Direction::LEFT);
	}
	else if (details->m_keyCode == 72 &&
		m_snake.GetPhisicalDirection() != Direction::LEFT) {
		m_snake.SetDirection(Direction::RIGHT);
	}
	else if (details->m_keyCode == 73 &&
		m_snake.GetPhisicalDirection() != Direction::DOWN) {
		m_snake.SetDirection(Direction::UP);
	}
	else if (details->m_keyCode == 74 &&
		m_snake.GetPhisicalDirection() != Direction::UP) {
		m_snake.SetDirection(Direction::DOWN);
	}
}