#include "..\Headers\state_intro.h"
#include "..\Headers\state_manager.h"

State_Intro::State_Intro(StateManager *stateManager) 
	: BaseState(stateManager) {}

State_Intro::~State_Intro() {}

void State_Intro::OnCreate() {
	m_timePassed = 0.0f;
	sf::Vector2u windowSize = m_stateManager->GetContext()->
		m_wnd->GetRenderWindow()->getSize();
	m_introTexture.loadFromFile("../Source/intro.png");
	m_introSprite.setTexture(m_introTexture);
	m_introSprite.setOrigin(m_introTexture.getSize().x / 2.0f,
		m_introTexture.getSize().y / 2.0f);
	m_introSprite.setPosition(windowSize.x / 2.0f, 0);

	m_font.loadFromFile("../Source/VintageOne.ttf");
	m_text.setFont(m_font);
	m_text.setString({ "Press SPACE to continue" });
	m_text.setCharacterSize(15);
	sf::FloatRect textRect = m_text.getLocalBounds();
	m_text.setOrigin(textRect.left + textRect.width / 2.0f,
		textRect.top + textRect.height / 2.0f);
	m_text.setPosition(windowSize.x / 2.0f, windowSize.y / 2.0f);

	EventManager *eventMngr = m_stateManager->GetContext()->m_eventManager;
	eventMngr->AddCallback(StateType::Intro, "Intro_Continue",
		&State_Intro::Continue, this);
}

void State_Intro::OnDestroy() {
	EventManager *eventMangr = m_stateManager->GetContext()->m_eventManager;
	eventMangr->RemoveCallback(StateType::Intro, "Intro_Continue");
}

void State_Intro::Update(const sf::Time &time) {
	if (m_timePassed < 5.0f) {
		m_timePassed += time.asSeconds();
		m_introSprite.setPosition(m_introSprite.getPosition().x,
			m_introSprite.getPosition().y + (48 * time.asSeconds()));
	}
}

void State_Intro::Draw() {
	sf::RenderWindow *window = m_stateManager->GetContext()->
		m_wnd->GetRenderWindow();
	window->draw(m_introSprite);
	if (m_timePassed >= 5.0f) {
		window->draw(m_text);
	}
}

void State_Intro::Continue(EventDetails*) {
	if (m_timePassed >= 5.0f) {
		m_stateManager->SwitchTo(StateType::MainMenu);
		m_stateManager->Remove(StateType::Intro);
	}
}
