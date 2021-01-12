#include "..\Headers\state_paused.h"
#include "..\Headers\state_manager.h"

State_Paused::State_Paused(StateManager *stateManager) 
	: BaseState(stateManager) {}

State_Paused::~State_Paused() {}

void State_Paused::OnCreate() {
	//allowing the state manager to render the state 
	//directly behind this one on the state stack
	SetTransparent(true);
	m_font.loadFromFile("..\\Source\\VintageOne.ttf");
	m_text.setFont(m_font);
	m_text.setString({ "PAUSED" });
	m_text.setCharacterSize(30);
	m_text.setStyle(sf::Text::Style::Bold);
	sf::Vector2u windowSize = m_stateManager->GetContext()->
		m_wnd->GetWindowSize();
	sf::FloatRect textRect = m_text.getLocalBounds();
	m_text.setOrigin(textRect.left + textRect.width / 2.0f,
		textRect.top + textRect.height / 2.0f);
	m_text.setPosition(windowSize.x / 2.0f, windowSize.y / 2.0f);
	m_rect.setSize(sf::Vector2f(windowSize));
	m_rect.setPosition(0, 0);
	m_rect.setFillColor(sf::Color(0, 0, 0, 150));

	EventManager *eventManager = m_stateManager->GetContext()->m_eventManager;
	eventManager->AddCallback(
		StateType::Paused, "Key_P", &State_Paused::Unpause, this);
}

void State_Paused::OnDestroy() {
	EventManager *eventManager = m_stateManager->GetContext()->m_eventManager;
	eventManager->RemoveCallback(StateType::Paused, "Key_P");
}

void State_Paused::Draw() {
	sf::RenderWindow *window = m_stateManager->GetContext()
		->m_wnd->GetRenderWindow();
	window->draw(m_rect);
	window->draw(m_text);
}

void State_Paused::Unpause(EventDetails *details) {
	m_stateManager->SwitchTo(StateType::Game);
}