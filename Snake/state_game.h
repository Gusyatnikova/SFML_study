#pragma once
#include "base_state.h"
#include "World.h"
#include"textbox.h"

class State_Game : public BaseState{
private:
	Window* m_window;
	World m_world;
	Snake m_snake;
	TextBox m_textBox;
	bool m_isDone;
	void ProcessInput(EventDetails* details);
	float m_elapsed;
	sf::Clock m_clock;
	
public:
	State_Game(StateManager *state_manager);
	~State_Game();
	void OnCreate();
	void OnDestroy();
	void Activate() {}
	void Deactivate() {}
	void Update(const sf::Time &time);
	void Draw();

	void Pause(EventDetails *details);
	void MainMenu(EventDetails *details);
};
