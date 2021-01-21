#pragma once
#include "base_state.h"
#include "button.h"

class State_MainMenu : public BaseState {
private:
	enum {ButtonsCnt = 4};
	sf::Text m_text;
	sf::Font m_font;
	sf::Texture m_backgroundTexture;
	sf::Sprite m_backgroundSprite;
	unsigned int m_buttonPadding;
	RectButton m_buttons[ButtonsCnt];
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
	void MouseMoved(EventDetails *details);
};
