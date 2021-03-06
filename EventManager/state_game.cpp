#include "..\Headers\state_game.h"
#include "..\Headers\state_manager.h"

State_Game::State_Game(StateManager *stateManager)
	: BaseState(stateManager) {}

State_Game::~State_Game() {}

void State_Game::OnCreate() {
	m_texture.loadFromFile("..\\Source\\food.png");
	m_sprite.setTexture(m_texture);
	m_sprite.setPosition(0, 0);
	m_increment = { 400.0f, 400.0f };
	EventManager* eventManager = m_stateManager->GetContext()->m_eventManager;
	eventManager->AddCallback(
		StateType::Game, "Key_Escape", &State_Game::MainMenu, this);
	eventManager->AddCallback(
		StateType::Game, "Key_P", &State_Game::Pause, this);
}

void State_Game::OnDestroy() {
	EventManager *eventManager = m_stateManager->GetContext()->m_eventManager;
	eventManager->RemoveCallback(StateType::Game, "Key_Escape");
	eventManager->RemoveCallback(StateType::Game, "Key_P");
}

void State_Game::Update(const sf::Time &time) {
	sf::Vector2u l_windSize = m_stateManager->GetContext()->m_wnd->GetWindowSize();
	sf::Vector2u l_textSize = m_texture.getSize();

	if ((m_sprite.getPosition().x > l_windSize.x - l_textSize.x && m_increment.x > 0) ||
		(m_sprite.getPosition().x < 0 && m_increment.x < 0))
	{
		m_increment.x = -m_increment.x;
	}

	if ((m_sprite.getPosition().y > l_windSize.y - l_textSize.y && m_increment.y > 0) ||
		(m_sprite.getPosition().y < 0 && m_increment.y < 0))
	{
		m_increment.y = -m_increment.y;
	}

	m_sprite.setPosition(m_sprite.getPosition().x + (m_increment.x * time.asSeconds()),
		m_sprite.getPosition().y + (m_increment.y * time.asSeconds()));
}

void State_Game::Draw() {
	m_stateManager->GetContext()->m_wnd->Draw(m_sprite);
}

void State_Game::MainMenu(EventDetails *details) {
	//don't remove state game to have an opportunity 
	//resume the game without losing a progress
	m_stateManager->SwitchTo(StateType::MainMenu);
}

void State_Game::Pause(EventDetails *details) {
	m_stateManager->SwitchTo(StateType::Paused);
}