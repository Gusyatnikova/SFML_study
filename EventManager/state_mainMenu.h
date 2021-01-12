#pragma once
#include "base_state.h"

class State_MainMenu : public BaseState {
private:
	sf::Text m_text;
	sf::Font m_font;
	sf::Vector2f m_buttonSize;
	sf::Vector2f m_buttonPos;
	unsigned int m_buttonPadding;

	sf::RectangleShape m_rects[3];
	sf::Text m_labels[3];
public:
	State_MainMenu(StateManager* manager);
	~State_MainMenu();
	void OnCreate();
	void OnDestroy();
	void Activate();
	void Deactivate() {}
	void Update(const sf::Time &time) {}
	void Draw();
	void MouseClick(EventDetails* details);
};
