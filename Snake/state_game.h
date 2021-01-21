#pragma once
#include "base_state.h"

class State_Game : public BaseState{
private:
	sf::Texture m_texture;
	sf::Sprite m_sprite;
	sf::Vector2f m_increment;
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
