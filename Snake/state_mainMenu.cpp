#include "state_mainMenu.h"
#include "state_manager.h"


State_MainMenu::State_MainMenu(StateManager* stateManager)
	: BaseState(stateManager) {}

State_MainMenu::~State_MainMenu() {}

void State_MainMenu::OnCreate() {
	m_backgroundTexture.loadFromFile("..\\Source\\background.png");
	m_backgroundSprite.setTexture(m_backgroundTexture);
	m_font.loadFromFile("..\\Source\\LuckiestGuy.ttf");
	m_text.setFont(m_font);
	m_text.setString({ "SNAKE" });
	m_text.setCharacterSize(70);
	m_text.setFillColor(sf::Color(64, 191, 64));
	m_text.setOutlineThickness(2.0f);
	m_text.setOutlineColor(sf::Color::Black);
	m_text.setLetterSpacing(4.5f);

	sf::FloatRect textRect = m_text.getLocalBounds();
	m_text.setOrigin(textRect.left + textRect.width / 2.0f,
		textRect.top + textRect.height / 2.0f);
	m_text.setPosition(400, 80);

	sf::Vector2f buttonSize = sf::Vector2f(300.0f, 50.0f);
	m_buttonPadding = buttonSize.y;
	sf::Vector2f buttonPos = m_text.getPosition() + sf::Vector2f(0, 2.5f * m_buttonPadding);

	std::string str[ButtonsCnt] = {
		"PLAY", "SETTINGS", "ABOUT", "EXIT" };

	for (int i = 0; i < ButtonsCnt; ++i) {
		sf::Vector2f buttonPosition(buttonPos.x,
			buttonPos.y + (i * (buttonSize.y + m_buttonPadding)));
		m_buttons[i].SetSize(buttonSize);
		m_buttons[i].SetOrigin(sf::Vector2f(
			buttonSize.x / 2.0f, buttonSize.y / 2.0f));
		m_buttons[i].SetPosition(buttonPosition);
		m_buttons[i].SetBackgroundColor(sf::Color(0, 0, 0, 0));
		m_buttons[i].SetFont(m_font);
		m_buttons[i].SetText(str[i]);
		m_buttons[i].SetTextColor(sf::Color(64, 191, 64, 255));
		m_buttons[i].SetCharacterSize(50);
		m_buttons[i].SetTextLetterCpacing(3.0f);

		m_buttons[i].CenterText();
		m_buttons[i].SetTextOutlineThickness(2.0);
	}
	EventManager* eventManager = m_stateManager->GetContext()->m_eventManager;
	eventManager->AddCallback(StateType::MainMenu, "Mouse_Pressed",
		&State_MainMenu::MouseClick, this);
	eventManager->AddCallback(StateType::MainMenu, "Mouse_Moved",
		&State_MainMenu::MouseMoved, this);
}

void State_MainMenu::OnDestroy() {
	EventManager *eventManager = m_stateManager->GetContext()->m_eventManager;
	eventManager->RemoveCallback(StateType::MainMenu, "Mouse_Pressed");
	eventManager->AddCallback(StateType::MainMenu, "Mouse_Moved",
		&State_MainMenu::MouseMoved, this);
}

void State_MainMenu::Activate() {
	if (m_stateManager->HasState(StateType::Game)
		&& m_buttons[0].GetText().getString() == "PLAY") {
		m_buttons[0].SetText({ "RESUME" });
		sf::FloatRect rect = m_buttons[0].GetText().getLocalBounds();
		m_buttons[0].SetTextOrigin(sf::Vector2f(rect.left + rect.width / 2.0f,
			rect.top + rect.height / 2.0f));
	}
}

void State_MainMenu::MouseClick(EventDetails *details) {
	sf::Vector2i mousePos = details->m_mouse;
	for (int i = 0; i < ButtonsCnt; ++i) {
		if (m_buttons[i].IsInside(mousePos.x, mousePos.y)) {
			if (i == 0) {
				m_stateManager->SwitchTo(StateType::Game);
			}
			else if (i == 1) {
				//settings
			}
			else if (i == 2) {
				//about
				//?????	
			}
			else if (i == 3) {
				m_stateManager->GetContext()->m_wnd->Close();
			}
		}
	}
}

void State_MainMenu::MouseMoved(EventDetails *details) {
	sf::Vector2i mousePos = details->m_mouse;
	for (int i = 0; i < ButtonsCnt; ++i) {
		if (m_buttons[i].IsInside(mousePos.x, mousePos.y)) {
			m_buttons[i].SetTextStyle(sf::Text::Style::Underlined);
		}
		else {
			m_buttons[i].SetTextStyle(sf::Text::Style::Regular);
		}
	}
}

void State_MainMenu::Draw() {
	sf::RenderWindow *window = m_stateManager->GetContext()->m_wnd->GetRenderWindow();
	window->draw(m_backgroundSprite);
	window->draw(m_text);
	for (int i = 0; i < ButtonsCnt; ++i) {
		m_buttons[i].Render(window);
	}
}