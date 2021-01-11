#pragma once
#include "Window.h"
#include "World.h"
#include"textbox.h"
#include "state_manager.h"

class Game
{
public:
	Game();
	~Game();

	void Update();
	void LateUpdate();
	void Render();
	Window* GetWindow();
	sf::Time GetElapsed();
private:
	SharedContext m_context;
	Window m_window;
	StateManager m_stateManager;
	sf::Clock m_clock;
	sf::Time m_elapsed;
	void RestartClock();
};

