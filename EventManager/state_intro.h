#pragma once
#include "base_state.h"

class State_Intro : public BaseState {
private:
	sf::Texture m_introTexture;
	sf::Sprite m_introSprite;
	sf::Text m_text;
	sf::Font m_font;
	float m_timePassed;
public:
	State_Intro(StateManager *stateManager);
	~State_Intro();
	//transition from Intro to MainMenu state 
	//when time is over and space was pressed
	void Continue(EventDetails*);
	virtual void OnCreate();
	virtual void OnDestroy();
	virtual void Activate() {}
	virtual void Deactivate() {}
	virtual void Update(const sf::Time &time);
	virtual void Draw();
};