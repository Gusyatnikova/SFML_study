#pragma once
#include "base_state.h"
#include "button.h"

class State_GameOver : public BaseState {
private:
	enum { ButtonsCnt = 2 };
	sf::Text m_text;
	sf::Font m_font;
	sf::Texture m_backgroundTexture;
	sf::Sprite m_backgroundSprite;
	unsigned int m_buttonPadding;
	RectButton m_buttons[ButtonsCnt];
public:
	State_GameOver(StateManager* manager);
	~State_GameOver();
	void OnCreate();
	void OnDestroy();
	void Activate();
	void Deactivate() {}
	void Update(const sf::Time &time) {}
	void Draw();
	void MouseClick(EventDetails* details);
	void MouseMoved(EventDetails *details);
};
