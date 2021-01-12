#pragma once
#include "base_state.h"

class State_Paused : public BaseState {
private:
	sf::Font m_font;
	sf::Text m_text;
	sf::RectangleShape m_rect;
public:
	State_Paused(StateManager *state_manager);
	~State_Paused();
	void OnCreate();
	void OnDestroy();
	void Activate() {}
	void Deactivate() {}
	void Update(const sf::Time &time) {}
	void Draw();

	void Unpause(EventDetails *details);
};

